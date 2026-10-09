
void ajout_produit(CATEGORIE* categorie)
{
	char nouveau_produit[SIZE];
	float nouveau_prix = 0.0;
	int nouvelle_quantite = 0;
	NODE_P* node = (NODE_P*)malloc(sizeof(NODE_P));  /*allocation d'espace mémoire pour un nouveau noeud pour le nouveau produit */
	NODE_P* dernier = categorie->list_produits->last;


	/* Création du nouveau produit */
	PRODUIT nouveau = { "",0.0,0 };
	printf("Entrer le nom du nouveau produit : \n");
	scanf("%s",nouveau_produit);

	printf("Entrer le prix du nouveau produit : \n");
	scanf("%f",&nouveau_prix);

	printf("Entrer la quantite du nouveau produit : \n");
	scanf("%d",&nouvelle_quantite);

	strcpy(nouveau.nom_produit,nouveau_produit); /* Copier le nom du nouveau produit entrée au clavier dans la structure du nouveau produit */
	nouveau.prix_produit = nouveau_prix;
	nouveau.quantite_produit = nouvelle_quantite;

	if (node == NULL)
	{
		printf("ERREUR \n : ");
		return;
	}

	node->produit = nouveau;                     
	node->next = NULL;

	if (dernier != NULL)
	{
		dernier->next = node;
		node->previous = dernier; 
	}
	else 
		/* Si la liste est vide, le nouveau noeud devient le premier noeud */
	{
		categorie->list_produits->first = node;
		node->previous = NULL;
	}

	categorie->list_produits->last = node;

	

	print_produits(*categorie); 
}