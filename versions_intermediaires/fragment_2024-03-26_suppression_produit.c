
void suppression_produit(CATEGORIE* categorie) 
{	
	int	i = 0; /* */
	int	compte = 0;
	int compare = 5;
	char produit[SIZE];

	NODE_P* node = categorie->list_produits->first;
	/* Pour donner le nombre d'éléments */
	while (node != NULL) {
		compte++;
		node = node->next;
	}

	NODE_P* tableau[SIZE]; /*tableau de pointeur vers les noeuds des produits*/
	node = categorie->list_produits->first;
	for (i = 0; i <= compte - 1 && node != NULL; i++)
	{
		tableau[i] = node;
		node = node->next;
	}

	//tableau[compte - 1]->next = NULL; //pour fermer le tableau ??

	printf("entrer le NOM du produit\n");
	scanf("%s", produit);  //produit a supprimer 
	for (i = 0; i <= compte - 1 && compare != 0; i++)
	{
		compare = strcmp (produit, tableau[i]->produit.nom_produit) ;
		/*Compare le nom du produit avec les noms de chaque produitdu tableau */
	}
	/* tableau [i-1] est le produit qu'on cherche et qu'on veut donc supprimer */

	if (i-1 == 0) {
		tableau [i - 1]->next = categorie -> list_produits -> first;
		tableau[i]->previous = NULL ; /*prvious(next(tableau[i-1]) = NULL*/
	}
	else if (i-1== compte - 1) 
	{
		tableau[i - 1]->previous = categorie->list_produits->last;
		tableau[i - 2]->next = NULL; /**/
	}
	else
	{
		tableau[i - 2]->next = tableau[i - 1]->next;
		tableau[i]->previous = tableau[i - 1]->previous;
	}

	print_produits(*categorie);
}


