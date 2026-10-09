/* Original coursework: Sarah Dahmoun and Tedj El Moulk Sinacer. */
#include "gestion_de_stock.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    LISTE_P products = {NULL, NULL};
    CATEGORIE fruits = {"fruits", &products};
    int result = EXIT_FAILURE;
    if (!stock_add(&products, "Banana", 1.25f, 200) ||
        !stock_add(&products, "Orange", 1.10f, 900)) goto cleanup;

    puts("Alphabetical order:");
    if (!tri_alphabetique(&fruits)) goto cleanup;
    print_produits(fruits);
    puts("Price ascending:");
    if (!tri_prix_croissant(&fruits)) goto cleanup;
    print_produits(fruits);
    puts("Price descending:");
    if (!tri_prix_decroissant(&fruits)) goto cleanup;
    print_produits(fruits);
    puts("Quantity descending:");
    if (!tri_quantite_dispo(&fruits)) goto cleanup;
    print_produits(fruits);
    result = EXIT_SUCCESS;
cleanup:
    stock_clear(&products);
    if (result != EXIT_SUCCESS) fputs("Inventory operation failed.\n", stderr);
    return result;
}
