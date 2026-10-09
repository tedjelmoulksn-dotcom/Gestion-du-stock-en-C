void gestion_stock(LISTE_C* liste_categories)
{
	CATEGORIE* categorie = NULL;
	char categorie_amodifier[SIZE];
	int choix_action;
	char nom_categorie[SIZE] = {""};
	NODE_C* current = liste_categories->first;

	/*Demande quelle catégorie  modifier*/
	printf("Entrez le nom de la catégorie a modifier :\n ");
	scanf("%s",categorie_amodifier);

	/* Recherche de cette catégorie dans la liste */
	while (current != NULL)
	{
		if (strcoll(current->categorie.nom_categorie,nom_categorie) == 0)
		{
			return &(current->categorie);
		}
		current = current->next;
	}

	if (categorie == NULL)
	{
		printf("La categorie n'existe pas \n");
		return;
	}
	/* Demander quel type d'action effectuer */
	printf("Quelle action souhaitez-vous effectuer ? : \n");
	printf("1. Ajouter un produit\n");
	printf("2. Supprimer un produit\n");
	printf("3. Trier la categorie dans un ordre alphabetique\n");
	printf("4. Trier la categorie par ordre de prix decroissant\n");
	printf("5. Trier la categorie par ordre de prix croissant\n");
	printf("6. Trier la categorie en fonction des quantites disponnibles \n");
	printf("7. Mettre à jour le prix d'un produit ");
	printf("8. Mettre à jour la quantité d'un produit");
	scanf("%d",&choix_action);
	if (choix_action == 1)
	{
		ajout_produit(&(current->categorie));
	}
	else if (choix_action == 2)
	{
		suppression_produit(&(current->categorie));
	}
	else if (choix_action == 3)
	{
		tri_alphabetique(&(current->categorie));
	}
	else if (choix_action == 4)
	{
		tri_prix_decroissant(&(current->categorie));
	}
	else if (choix_action == 5)
	{
		tri_prix_croissant(&(current->categorie));
	}
	else if (choix_action == 6)
	{
		tri_quantite_dispo(&(current->categorie));
	}
	else if (choix_action == 7)
	{
		maj_produit_prix(&(current->categorie));
	}
	else if (choix_action == 8)
	{
		maj_produit_quantite(&(current->categorie));
	}
	else
	{
		/* Demander quel type d'action effectuer */
		printf("Quelle action souhaitez-vous effectuer ? : \n");
		printf("1. Ajouter un produit\n");
		printf("2. Supprimer un produit\n");
		printf("3. Trier la categorie dans un ordre alphabetique\n");
		printf("4. Trier la categorie par ordre de prix decroissant\n");
		printf("5. Trier la categorie par ordre de prix croissant\n");
		printf("6. Trier la categorie en fonction des quantites disponnibles \n");
		printf("7. Mettre à jour le prix d'un produit ");
		printf("8. Mettre à jour la quantité d'un produit");
		scanf("%d",&choix_action);
	}

}
	