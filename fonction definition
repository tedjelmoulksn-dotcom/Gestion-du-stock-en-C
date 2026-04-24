
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet.h"

#define SIZE 500

void print_produits(CATEGORIE categorie) {
	NODE_P* n = categorie.list_produits->first;
	while (n != categorie.list_produits->last)
	{
		printf("Nom produit : %s ; Prix du produit : %f ; Quantite disponible : %d \n", n->produit.nom_produit, n->produit.prix_produit, 
			n->produit.quantite_produit);
		
		n= n->next;
	}
	printf("Nom produit : %s ; Prix du produit : %f ; Quantite disponible : %d \n", n->produit.nom_produit, n->produit.prix_produit,
		n->produit.quantite_produit);
}
/* Fonction qui compare les noms et renvoi 0,1 ou -1  */
int comparer_nom(const void* a, const void* b) { /* a est un pointeur vers un élement dans le tableau*/
	NODE_P* produitA = *(NODE_P**)a; /*ça va convertir a en un pointeur de pointeur vers NODE_P */
	NODE_P* produitB = *(NODE_P**)b; /*On accède à la valeur vers laquelle b pointe*/
	return strcmp(produitA-> produit.nom_produit, produitB -> produit.nom_produit);
}

	
void tri_alphabetique(CATEGORIE* categorie) {
	int i = 0; /* */
	int compte = 0;
	NODE_P* node = categorie->list_produits->first;
	/* Pour donner le nombre d'éléments */
	while (node != NULL) {
		compte++;
		node = node->next;
	}

	NODE_P* tableau[SIZE] /*tableau de pointeur vers les noeuds des produits*/;
	node = categorie->list_produits->first;

	while (node != NULL) {
		tableau[i++] = node;
		node = node->next;
	}
	/*La fonction de tri*/

	qsort( &tableau, compte, sizeof(NODE_P*), comparer_nom);
	
	

	categorie->list_produits->first = tableau[0];
	categorie->list_produits->last = tableau[compte - 1];

	for (i = 0; i < compte - 1; i++) {
		tableau [i] ->next = tableau[i + 1];
		tableau [i + 1] ->previous = tableau[i];

	}
	tableau [compte - 1] ->next = NULL;
	print_produits(*categorie);
}

int comparer_prix(const void* a, const void* b) { /* a est un pointeur vers un élement dans le tableau*/
	
	NODE_P* produitA = *(NODE_P**)a; /*ça va convertir a en un pointeur de pointeur vers NODE_P */
	NODE_P* produitB = *(NODE_P**)b; /*On accède à la valeur vers laquelle b pointe*/
	
	return produitA->produit.prix_produit - produitB->produit.prix_produit;

}

void tri_prix_croissant(CATEGORIE* categorie) {
	int i = 0; /* */
	int compte = 0;
	NODE_P* node = categorie->list_produits->first;
	/* Pour donner le nombre d'éléments */
	while (node != NULL) {
		compte++;
		node = node->next;
	}

	NODE_P* tableau[SIZE] /*tableau de pointeur vers les noeuds des produits*/;
	node = categorie->list_produits->first;

	while (node != NULL) {
		tableau[i++] = node;
		node = node->next;
	}
	/*La fonction de tri*/

	qsort(&tableau, compte, sizeof(NODE_P*), comparer_prix);



	categorie->list_produits->first = tableau[0];
	categorie->list_produits->last = tableau[compte - 1];

	for (i = 0; i < compte - 1; i++) {
		tableau[i]->next = tableau[i + 1];
		tableau[i + 1]->previous = tableau[i];

	}
	tableau[compte - 1]->next = NULL;
	print_produits(*categorie);
}

void tri_prix_decroissant(CATEGORIE* categorie) {
	int i = 0; /* */
	int compte = 0;
	NODE_P* node = categorie->list_produits->first;
	/* Pour donner le nombre d'éléments */
	while (node != NULL) {
		compte++;
		node = node->next;
	}

	NODE_P* tableau[SIZE] /*tableau de pointeur vers les noeuds des produits*/;
	node = categorie->list_produits->first;

	while (node != NULL) {
		tableau[i++] = node;
		node = node->next;
	}
	/*La fonction de tri*/

	qsort(&tableau, compte, sizeof(NODE_P*), comparer_prix);



	categorie->list_produits->last = tableau[0];
	categorie->list_produits->first = tableau[compte - 1];

	for (i = 0; i < compte - 1; i++) {
		tableau[i]->previous = tableau[i + 1];
		tableau[i + 1]->next = tableau[i];

	}
	tableau[compte - 1]->previous = NULL;
	categorie->list_produits->last->next = NULL;
	print_produits(*categorie);
}

int comparer_quantite(const void* a, const void* b) { /* a est un pointeur vers un élement dans le tableau*/

	NODE_P* produitA = *(NODE_P**)a; /*ça va convertir a en un pointeur de pointeur vers NODE_P */
	NODE_P* produitB = *(NODE_P**)b; /*On accède à la valeur vers laquelle b pointe*/
	
	if (produitA->produit.quantite_produit < produitB->produit.quantite_produit)
		return -1;
	else if (produitA->produit.quantite_produit > produitB->produit.quantite_produit)
		return 1;
	else return 0;

}

void tri_quantite_dispo(CATEGORIE* categorie) {
	int i = 0; /* */
	int compte = 0;
	NODE_P* node = categorie->list_produits->first;
	/* Pour donner le nombre d'éléments */
	while (node != NULL) {
		compte++;
		node = node->next;
	}

	NODE_P* tableau[SIZE] /*tableau de pointeur vers les noeuds des produits*/;
	node = categorie->list_produits->first;

	while (node != NULL) {
		tableau[i++] = node;
		node = node->next;
	}
	/*La fonction de tri*/

	qsort(&tableau, compte, sizeof(NODE_P*), comparer_quantite);



	categorie->list_produits->last = tableau[0];
	categorie->list_produits->first = tableau[compte - 1];

	for (i = 0; i < compte - 1; i++) {
		tableau[i]->previous = tableau[i + 1];
		tableau[i + 1]->next = tableau[i];

	}
	tableau[compte - 1]->previous = NULL;
	categorie->list_produits->last->next = NULL;
	print_produits(*categorie);
}

	

