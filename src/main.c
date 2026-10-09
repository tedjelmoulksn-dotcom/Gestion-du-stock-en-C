/* Dahmoun sarah     Sinacer Tedj el moulk             INSTRU 1*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "projet.h"


int main(int argc, char* argv[])
{

	setlocale(LC_ALL, ""); /*Permet d'utiliser strcoll configurer en Français */

	LISTE_C* stock = (LISTE_C*)malloc(sizeof(LISTE_C));
	stock->first = NULL;
	stock->last = NULL;
	
	chargerStock(stock, argv[1]);
	gestion_stock(stock);
	saveStock(stock, argv[1]);


	return EXIT_SUCCESS;
}



