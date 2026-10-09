#ifndef GESTION_DE_STOCK_H
#define GESTION_DE_STOCK_H

#include <stdbool.h>

#define STOCK_NAME_CAPACITY 200

typedef struct {
    char nom_produit[STOCK_NAME_CAPACITY];
    float prix_produit;
    int quantite_produit;
} PRODUIT;

typedef struct _NODE_P {
    PRODUIT produit;
    struct _NODE_P *next;
    struct _NODE_P *previous;
} NODE_P;

typedef struct {
    NODE_P *first;
    NODE_P *last;
} LISTE_P;

typedef struct {
    char nom_categorie[STOCK_NAME_CAPACITY];
    LISTE_P *list_produits;
} CATEGORIE;

typedef struct _NODE_C {
    CATEGORIE categorie;
    struct _NODE_C *next;
    struct _NODE_C *previous;
} NODE_C;

typedef struct {
    NODE_C *first;
    NODE_C *last;
} LISTE_C;

/* The caller owns the descriptor; the list owns nodes added by this API. */
bool stock_add(LISTE_P *list, const char *name, float price, int quantity);
void stock_clear(LISTE_P *list);
void print_produits(CATEGORIE categorie);
int comparer_nom(const void *a, const void *b);
int comparer_prix(const void *a, const void *b);
int comparer_quantite(const void *a, const void *b);
/* false: invalid category/list or temporary-allocation failure.
 * Allocation failure leaves the original links unchanged.
 */
bool tri_alphabetique(CATEGORIE *categorie);
bool tri_prix_croissant(CATEGORIE *categorie);
bool tri_prix_decroissant(CATEGORIE *categorie);
bool tri_quantite_dispo(CATEGORIE *categorie);

#endif
