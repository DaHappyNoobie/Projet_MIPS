#include "simulation.h"

/* ******************************************************************** */
/* Fonctions de la liste chainé contenant les commandes */

void insererCommande(listeCommande *l,char commandeBinaire[],char commandeHexa[], char commandeString[]) {

	commande *courant, *nouveau;


	courant = *l;

	if(courant != NULL) {
		/* Détermination de la fin de la liste */
		while ( courant->suivant != NULL ){

			courant = courant->suivant;
		}
	}

	/*Insertion*/
	nouveau = commandeNouveau();

	if (courant == NULL) {
		
		*l = nouveau;

		nouveau->adresse[0] = '0';
		nouveau->adresse[1] = '0';
		nouveau->adresse[2] = '4';
		nouveau->adresse[3] = '0';
		nouveau->adresse[4] = '0';
		nouveau->adresse[5] = '0';
		nouveau->adresse[6] = '0';
		nouveau->adresse[7] = '0';

	}else{
		courant->suivant = nouveau;
		creationAdresseInstruction(&courant, &nouveau, 7);
	}

	for(int i=0; i<30; i++) {
		nouveau->codeString[i] = commandeString[i];
	}

	for(int i=0; i<32; i++) {
		nouveau->codeBinaire[i] = commandeBinaire[i];
	}

	for(int i=0; i<8; i++) {
		nouveau->codeHexa[i] = commandeHexa[i];
	}

	nouveau->suivant = NULL;
}

commande* commandeNouveau() {

	commande* com = (commande*) malloc(sizeof(commande));

	/* Initialisation de la nouvelle commande */
	com->suivant = NULL;

	return com;
}

void creationAdresseInstruction(listeCommande *cou, listeCommande *nouv, int indice) {

	commande *courant, *nouveau;

	courant = *cou;
	nouveau = *nouv;


	if(indice == 7) {
		if(courant->adresse[indice] == 'c') {
			nouveau->adresse[indice] = '0';

			creationAdresseInstruction(&courant, &nouveau, indice-1);

			*nouv = nouveau; 

		}else {

			if(courant->adresse[indice] == '0') {
				nouveau->adresse[indice] = '4';

			}else if(courant->adresse[indice] == '4') {
				nouveau->adresse[indice] = '8';
			}else if(courant->adresse[indice] == '8') {
				nouveau->adresse[indice] = 'c';
			}else {
				printf("\nErreur de la fonction <creationAdresseInstruction> : adresse");
			}

			indice--;

			while(indice >= 0) {
				nouveau->adresse[indice] = courant->adresse[indice];
				indice--;			
			}

			*nouv = nouveau; 

		}		
	}else {
		if(courant->adresse[indice] == 'f') {
			nouveau->adresse[indice] = '0';

			creationAdresseInstruction(&courant, &nouveau, indice-1);
      
			*nouv = nouveau; 
		}else {

			if( (courant->adresse[indice] >= 48 && courant->adresse[indice] <= 56) || (courant->adresse[indice] >= 97 && courant->adresse[indice] <= 101)) {
				nouveau->adresse[indice] = courant->adresse[indice] + 1;

			}else if(courant->adresse[indice] == '9') {
				nouveau->adresse[indice] = 'a';
			}else {
				printf("\nErreur de la fonction <creationAdresseInstruction> : adresse");
			}

			indice--;

			while(indice >= 0) {
				nouveau->adresse[indice] = courant->adresse[indice];
				indice--;
			}

			*nouv = nouveau;

		}
	}
}

/* ******************************************************************** */
/* Fonctions de la liste chainé contenant les labels */

void insererLabel(listeLabel *l, listeCommande *ll, char labelNom[]) {
	label *courant, *nouveau;
	commande *courantI;

	courantI = *ll;
	courant = *l;

	/* Détermination de la fin de la liste des instruction (pour l'adresse) */
	while ( courantI != NULL && courantI->suivant != NULL ){
		courantI = courantI->suivant;
	}

	/* Détermination de la fin de la liste des labels */
	while (courant != NULL && courant->suivant != NULL ){
		courant = courant->suivant;
	}
	
	/*Insertion*/
	nouveau = labelNouveau();

	if (courantI == NULL) {
		nouveau->adresse[0] = '0';
		nouveau->adresse[1] = '0';
		nouveau->adresse[2] = '4';
		nouveau->adresse[3] = '0';
		nouveau->adresse[4] = '0';
		nouveau->adresse[5] = '0';
		nouveau->adresse[6] = '0';
		nouveau->adresse[7] = '0';
	}else{
		creationAdresseLabel(&courantI, &nouveau, 7);

	}

	for(int i=0; i<10; i++) {
		nouveau->nom[i] = labelNom[i];
	}

	if(courant == NULL) {
		*l = nouveau;
	}else{
		courant->suivant = nouveau;
	}

	nouveau->suivant = NULL;
}

label* labelNouveau() {

	label* lab = (label*) malloc(sizeof(label));

	/* Initialisation du nouveau label */
	lab->suivant = NULL;

	return lab;
}

void creationAdresseLabel(listeCommande *cou, listeLabel *nouv, int indice) {

	commande *courant;
	label *nouveau;

	courant = *cou;
	nouveau = *nouv;

	if(indice == 7) {

		if(courant->adresse[indice] == 'c') {
			nouveau->adresse[indice] = '0';

			creationAdresseLabel(&courant, &nouveau, indice-1);

			*nouv = nouveau; 


		}else {

			if(courant->adresse[indice] == '0') {
				nouveau->adresse[indice] = '4';
			}else if(courant->adresse[indice] == '4') {
				nouveau->adresse[indice] = '8';
			}else if(courant->adresse[indice] == '8') {
				nouveau->adresse[indice] = 'c';
			}else {
				printf("\nErreur de la fonction <creationAdresseLabel> : adresse");
			}

			indice--;

			while(indice >= 0) {
				nouveau->adresse[indice] = courant->adresse[indice];
				indice--;			
			}

			*nouv = nouveau; 

		}		
	}else {
		if(courant->adresse[indice] == 'f') {
			nouveau->adresse[indice] = '0';

			creationAdresseLabel(&courant, &nouveau, indice-1);

			*nouv = nouveau;
		}else {

			if( (courant->adresse[indice] >= 48 && courant->adresse[indice] <= 56) || (courant->adresse[indice] >= 97 && courant->adresse[indice] <= 101)) {
				nouveau->adresse[indice] = courant->adresse[indice] + 1;

			}else if(courant->adresse[indice] == '9') {
				nouveau->adresse[indice] = 'a';
			}else {
				printf("\nErreur de la fonction <creationAdresseLabel> : adresse");
			}

			indice--;

			while(indice >= 0) {
				nouveau->adresse[indice] = courant->adresse[indice];
				indice--;			
			}

			*nouv = nouveau; 

		}		
	}
}

/* ******************************************************************** */
/* Fonctions de la liste chainé contenant la Data */

void insererData(listeData *l, char dataBinaire[], char dataNom[], int tailleData) {

	data *courant, *nouveau;

	courant = *l;

	/* Détermination de la fin de la liste */
	while ( courant != NULL && courant->suivant != NULL ){
		courant = courant->suivant;
	}
	nouveau = dataNouveau();

	nouveau->taille = tailleData;

	if (courant == NULL) {
		*l = nouveau;

		nouveau->adresse[0] = '1';
		nouveau->adresse[1] = '0';
		nouveau->adresse[2] = '0';
		nouveau->adresse[3] = '1';
		nouveau->adresse[4] = '0';
		nouveau->adresse[5] = '0';
		nouveau->adresse[6] = '0';
		nouveau->adresse[7] = '0';

	}else{
		courant->suivant = nouveau;
		creationAdresseData(&courant, &nouveau, 7);
	}

	if(tailleData == 4 || tailleData==1) {
		for(int i=0; i<tailleData*8; i++) {
			nouveau->dataValeur[i] = dataBinaire[i];
		}		
	}else {
		for (int i = 0; i < tailleData*8; ++i) {
			nouveau->dataValeur[i] = '0';
		}
	}

	for(int i=0; i<10; i++) {
		nouveau->nom[i] = dataNom[i];
	}

	nouveau->suivant = NULL;
}

void creationAdresseData(listeData *cou, listeData *nouv, int indice) {

	data *courant, *nouveau;

	courant = *cou;
	nouveau = *nouv;

	if(nouveau->taille == 4) {
		if(indice == 7) {
			if(courant->adresse[indice] >= 99) {
				nouveau->adresse[indice] = '0';

				creationAdresseData(&courant, &nouveau, indice-1);
				*nouv = nouveau; 

			}else {

				if(courant->adresse[indice] >= 56) {
					nouveau->adresse[indice] = 'c';
				}else if(courant->adresse[indice] >= 52 ) {
					nouveau->adresse[indice] = '8';
				}else if(courant->adresse[indice] >= 48) {
					nouveau->adresse[indice] = '4';
				}else {
					printf("\nErreur de la fonction <creationAdresseData> : adresse");
				}

				indice--;

				while(indice >= 0) {
					nouveau->adresse[indice] = courant->adresse[indice];
					indice--;			
				}

				*nouv = nouveau; 

			}		
		}else {
			if(courant->adresse[indice] == 'f') {
				nouveau->adresse[indice] = '0';

				creationAdresseData(&courant, &nouveau, indice-1);
				*nouv = nouveau; 
			}else {

				if( (courant->adresse[indice] >= 48 && courant->adresse[indice] <= 56) || (courant->adresse[indice] >= 97 && courant->adresse[indice] <= 101)) {
					nouveau->adresse[indice] = courant->adresse[indice] + 1;
				}else if(courant->adresse[indice] == '9') {
					nouveau->adresse[indice] = 'a';
				}else {
					printf("\nErreur de la fonction <creationAdresseData> : adresse");
				}

				indice--;
				while(indice >= 0) {
					nouveau->adresse[indice] = courant->adresse[indice];
					indice--;
				}
				*nouv = nouveau;
			}
		}
	}else if(nouveau->taille == 1) {
		if(indice == 7) {
			if(courant->taille == 4 && courant->adresse[indice] <= 52) {
				nouveau->adresse[indice] = courant->adresse[indice] + 4;
			}else if(courant->taille == 4 && courant->adresse[indice] == '8') {
				nouveau->adresse[indice] = 'c';
			}else if(courant->taille == 4) {
				nouveau->adresse[indice] = '0';
			}else{
				if(courant->adresse[indice] == 'f') {
					nouveau->adresse[indice] = '0';

					creationAdresseData(&courant, &nouveau, indice-1);
					*nouv = nouveau; 

				}else {
					printf(".%d", courant->adresse[indice] );
					if(courant->adresse[indice] == '9') {
						nouveau->adresse[indice] = 'a';
					}else if((courant->adresse[indice] >= 48 && courant->adresse[indice] <= 56) || (courant->adresse[indice] >= 97 && courant->adresse[indice] <= 101)) {
						nouveau->adresse[indice] = courant->adresse[indice] + 1;
					}else {
						printf("\nErreur de la fonction <creationAdresseData> : adresse");
					}	
				}			
			}

				indice--;

				while(indice >= 0) {
					nouveau->adresse[indice] = courant->adresse[indice];
					indice--;			
				}

				*nouv = nouveau; 
		}else {
			if(courant->adresse[indice] == 'f') {
				nouveau->adresse[indice] = '0';

				creationAdresseData(&courant, &nouveau, indice-1);
				*nouv = nouveau; 
			}else {

				if( (courant->adresse[indice] >= 48 && courant->adresse[indice] <= 56) || (courant->adresse[indice] >= 97 && courant->adresse[indice] <= 101)) {
					nouveau->adresse[indice] = courant->adresse[indice] + 1;
				}else if(courant->adresse[indice] == '9') {
					nouveau->adresse[indice] = 'a';
				}else {
					printf("\nErreur de la fonction <creationAdresseData> : adresse");
				}

				indice--;
				while(indice >= 0) {
					nouveau->adresse[indice] = courant->adresse[indice];
					indice--;
				}
				*nouv = nouveau;
			}
		}		
	}
}

data* dataNouveau() {

	data* lab = (data*) malloc(sizeof(data));

	/* Initialisation du nouveau data */
	lab->suivant = NULL;

	return lab;
}

/* ******************************************************************** */
/* Fonctions communes */

void affichageStringCommande(char commandeString[]) {

	int i=0;
	char c;

	printf("\n");

	c = commandeString[i];

	do {
		printf("%c",c);
		i++;
		c = commandeString[i];

	}while(c != '\n' && c!= '\0' && c != EOF);
}