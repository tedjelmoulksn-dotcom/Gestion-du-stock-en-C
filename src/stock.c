#include "gestion_de_stock.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool stock_add(LISTE_P *list, const char *name, float price, int quantity)
{
    NODE_P *node;
    size_t length;
    if (!list || !name || !isfinite(price) || price < 0 || quantity < 0)
        return false;
    length = strlen(name);
    if (length >= STOCK_NAME_CAPACITY) return false;
    node = malloc(sizeof *node);
    if (!node) return false;
    memcpy(node->produit.nom_produit, name, length + 1);
    node->produit.prix_produit = price;
    node->produit.quantite_produit = quantity;
    node->previous = list->last;
    node->next = NULL;
    if (list->last) list->last->next = node;
    else list->first = node;
    list->last = node;
    return true;
}

void stock_clear(LISTE_P *list)
{
    NODE_P *node;
    if (!list) return;
    node = list->first;
    while (node) {
        NODE_P *next = node->next;
        free(node);
        node = next;
    }
    list->first = list->last = NULL;
}

void print_produits(CATEGORIE categorie)
{
    const NODE_P *node;
    if (!categorie.list_produits) return;
    for (node = categorie.list_produits->first; node; node = node->next)
        printf("Product: %s; price: %.2f; quantity: %d\n",
               node->produit.nom_produit, node->produit.prix_produit,
               node->produit.quantite_produit);
}

int comparer_nom(const void *a, const void *b)
{
    const NODE_P *left = *(NODE_P * const *)a;
    const NODE_P *right = *(NODE_P * const *)b;
    return strcmp(left->produit.nom_produit, right->produit.nom_produit);
}

int comparer_prix(const void *a, const void *b)
{
    const NODE_P *left = *(NODE_P * const *)a;
    const NODE_P *right = *(NODE_P * const *)b;
    float x = left->produit.prix_produit, y = right->produit.prix_produit;
    return (x > y) - (x < y);
}

int comparer_quantite(const void *a, const void *b)
{
    const NODE_P *left = *(NODE_P * const *)a;
    const NODE_P *right = *(NODE_P * const *)b;
    int x = left->produit.quantite_produit, y = right->produit.quantite_produit;
    return (x > y) - (x < y);
}

static bool sort_products(CATEGORIE *category,
                         int (*compare)(const void *, const void *),
                         bool descending)
{
    LISTE_P *list;
    NODE_P *node;
    NODE_P **nodes;
    size_t count = 0, i;
    if (!category || !category->list_produits) return false;
    list = category->list_produits;
    for (node = list->first; node; node = node->next) {
        if (count == SIZE_MAX / sizeof *nodes) return false;
        ++count;
    }
    if (count < 2) return true;
    nodes = malloc(count * sizeof *nodes);
    if (!nodes) return false;
    for (node = list->first, i = 0; node; node = node->next)
        nodes[i++] = node;
    qsort(nodes, count, sizeof *nodes, compare);
    if (descending) {
        for (i = 0; i < count / 2; ++i) {
            NODE_P *swap = nodes[i];
            nodes[i] = nodes[count - 1 - i];
            nodes[count - 1 - i] = swap;
        }
    }
    for (i = 0; i < count; ++i) {
        nodes[i]->previous = i ? nodes[i - 1] : NULL;
        nodes[i]->next = i + 1 < count ? nodes[i + 1] : NULL;
    }
    list->first = nodes[0];
    list->last = nodes[count - 1];
    free(nodes);
    return true;
}

bool tri_alphabetique(CATEGORIE *c) { return sort_products(c, comparer_nom, false); }
bool tri_prix_croissant(CATEGORIE *c) { return sort_products(c, comparer_prix, false); }
bool tri_prix_decroissant(CATEGORIE *c) { return sort_products(c, comparer_prix, true); }
bool tri_quantite_dispo(CATEGORIE *c) { return sort_products(c, comparer_quantite, true); }
