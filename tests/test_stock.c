#include "gestion_de_stock.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static size_t live_allocations;
static bool fail_next_allocation;
void *__real_malloc(size_t size);
void __real_free(void *ptr);
void *__wrap_malloc(size_t size)
{
    void *ptr;
    if (fail_next_allocation) { fail_next_allocation = false; return NULL; }
    ptr = __real_malloc(size);
    if (ptr) ++live_allocations;
    return ptr;
}
void __wrap_free(void *ptr)
{
    if (ptr) { assert(live_allocations > 0); --live_allocations; }
    __real_free(ptr);
}

static size_t verify_links(const LISTE_P *list)
{
    const NODE_P *node, *previous = NULL;
    size_t forward = 0, backward = 0;
    for (node = list->first; node; node = node->next) {
        assert(node->previous == previous);
        previous = node;
        assert(++forward < 2000);
    }
    assert(previous == list->last);
    previous = NULL;
    for (node = list->last; node; node = node->previous) {
        assert(node->next == previous);
        previous = node;
        assert(++backward < 2000);
    }
    assert(previous == list->first);
    assert(forward == backward);
    return forward;
}

int main(void)
{
    LISTE_P list = {NULL, NULL};
    CATEGORIE category = {"test", &list};
    NODE_P *original_first;
    char too_long[STOCK_NAME_CAPACITY + 1];
    int i;
    assert(!tri_alphabetique(NULL));
    assert(tri_alphabetique(&category));
    assert(tri_prix_decroissant(&category));
    assert(verify_links(&list) == 0);
    print_produits(category);
    fail_next_allocation = true;
    assert(!stock_add(&list, "Orange", 1.25f, 2));
    assert(verify_links(&list) == 0);
    assert(stock_add(&list, "Orange", 1.25f, 2));
    original_first = list.first;
    assert(tri_quantite_dispo(&category));
    assert(verify_links(&list) == 1);
    assert(stock_add(&list, "Banana", 1.10f, 9));
    assert(stock_add(&list, "Apple", 1.20f, 4));
    assert(stock_add(&list, "Apple", 1.20f, 4));
    fail_next_allocation = true;
    assert(!tri_prix_croissant(&category));
    assert(list.first == original_first);
    assert(verify_links(&list) == 4);
    assert(tri_prix_croissant(&category));
    assert(list.first->produit.prix_produit == 1.10f);
    assert(list.last == original_first);
    assert(verify_links(&list) == 4);
    assert(tri_alphabetique(&category));
    assert(strcmp(list.first->produit.nom_produit, "Apple") == 0);
    assert(tri_prix_decroissant(&category));
    assert(list.first == original_first);
    assert(tri_quantite_dispo(&category));
    assert(list.first->produit.quantite_produit == 9);
    assert(verify_links(&list) == 4);
    memset(too_long, 'x', sizeof too_long);
    too_long[sizeof too_long - 1] = '\0';
    assert(!stock_add(&list, too_long, 1, 1));
    assert(!stock_add(&list, "invalid", NAN, 1));
    assert(!stock_add(&list, "invalid", -1, 1));
    assert(!stock_add(&list, "invalid", 1, -1));
    stock_clear(&list);
    assert(verify_links(&list) == 0);
    /* More than the historical fixed 500-pointer buffer. */
    for (i = 0; i < 600; ++i) {
        char name[32];
        snprintf(name, sizeof name, "item-%03d", 599 - i);
        assert(stock_add(&list, name, (float)(599-i)/10, i));
    }
    assert(tri_alphabetique(&category));
    assert(verify_links(&list) == 600);
    assert(tri_prix_croissant(&category));
    for (NODE_P *node = list.first; node->next; node = node->next)
        assert(node->produit.prix_produit <= node->next->produit.prix_produit);
    assert(tri_prix_decroissant(&category));
    assert(tri_quantite_dispo(&category));
    assert(verify_links(&list) == 600);
    stock_clear(&list);
    stock_clear(&list);
    assert(verify_links(&list) == 0);
    assert(live_allocations == 0);
    puts("Inventory sorting, allocation failures, 600-node links and cleanup: PASS");
    return 0;
}
