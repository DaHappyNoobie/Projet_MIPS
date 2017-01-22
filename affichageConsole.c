#include "affichageConsole.h"

void affichageBinaireCommande(char commandeBinaire[]) {
	
	char c;

	printf("\nCode binaire de la commande :\n");

	for(int i=31; i>-1; i--) {
		c = commandeBinaire[i];
		printf("%c", c);

		if(i%4 == 0 && i != 31 && i != 0) {
			printf(" ");
		}
 	}
}

void affichageHexaCommande(char commandeHexa[]) {
	
	char c;

	printf("\nCode hexadecimal de la commande :\n");

	for(int i=7; i>-1; i--) {
		c = commandeHexa[i];
		printf("%c", c);

		if(i%4 == 0 && i != 7 && i != 0) {
			printf(" ");
		}
 	}
}

void affichageLabel(char labelNom[]) {
	char c;
	int i=0;

	printf("\nNom du label : ");

	do{
		c = labelNom[i];
		printf("%c", c);
		i++;
	}while(labelNom[i]!='\0' && i<10);
}

void affichageData(char dataBinaire[], char dataNom[], int tailleData) {
	char c;
	int i=0;

	printf("\nNom de la variable : ");

	do{
		c = dataNom[i];
		printf("%c", c);
		i++;
	}while(dataNom[i]!='\0' && i<10);

	if(tailleData == 4) {
		printf("\nTypes : word");
	}else if(tailleData == 1) {
		printf("\nTypes : byte");		
	}else {
		printf("\nTaille : %d", tailleData);
	}

	printf("\nValeur binaire : ");

	i = tailleData*8-1;

	do{
		c = dataBinaire[i];
		printf("%c", c);

		if(i%4 == 0 && i != 31 && i != 0 && i!=tailleData*8) {
			printf(" ");
		}

		i--;
	}while(dataBinaire[i]!='\0' && i>-1);	
}

void minusculeStringCommande(char commandeString[]) {

	int i=0;
	char c;	
	c = commandeString[i];
	
	do {
		if ((commandeString[i]>=0x41) && (commandeString[i]<0x5B)) {

			commandeString[i] = commandeString[i] + 0x20;
		}

		i++;
		c = commandeString[i];

	}while(c != '\n' && c!= '\0' && c != EOF);
}

void affichageListeCommande(listeCommande *listeCommandes) {
	
	commande *courant;
	courant = *listeCommandes;
	char c;

	printf("\nAdresses       hexadecimal\t        Commandes binaire       ");
	printf("\n");

	if( courant == NULL )
		return;

	do {
		printf("\n");

		for(int i=0; i<8; i++) {
			printf("%c", courant->adresse[i]);
		};
		printf("\t");
		for(int i=7; i>-1; i--) {
			c = courant->codeHexa[i];
			printf("%c", c);

			if(i%4 == 0 && i != 31 && i != 0) {
				printf(" ");
			}
	 	}		
		printf("\t");
		for(int i=31; i>-1; i--) {
			c = courant->codeBinaire[i];
			printf("%c", c);

			if(i%4 == 0 && i != 31 && i != 0) {
				printf(" ");
			}
	 	}

	 	if(courant->suivant != NULL)
			courant = courant->suivant;

	}while ( courant->suivant != NULL );
}

void affichageListeLabel(listeLabel *listeLabels) {
	
	label *courant;
	courant = listeLabels;
	char c;

	printf("\nAdresses\tNom");
	printf("\n");

	while ( courant != NULL ) {
		printf("\n");

		for(int i=0; i<8; i++) {
			printf("%c", courant->adresse[i]);
		};
		printf("\t");
		for(int i=0; i<10; i++) {
			c = courant->nom[i];
			printf("%c", c);

	 	}		
		courant = courant->suivant;
	}
}

void affichageListeData(listeData *listeDatas) {
	
	data *courant;
	courant = listeDatas;
	char c;

	printf("\nAdresses\tNom\tTaille\tValeur");
	printf("\n");

	while ( courant != NULL ) {
		printf("\n");

		for(int i=0; i<8; i++) {
			printf("%c", courant->adresse[i]);
		};
		printf("\t");
		for(int i=0; i<10; i++) {
			c = courant->nom[i];
			printf("%c", c);

	 	}
	 	printf("\t%d",courant->taille);
		printf("\t");
		for(int i=8*courant->taille-1; i>-1; i--) {
			c = courant->dataValeur[i];
			printf("%c", c);

	 	}		
		courant = courant->suivant;
	}
}

void affichageMemoire(listeCommande *listeCommandes, listeData *listeDatas) {

	commande *listeCom, *courant;
	listeCom = listeCommandes;
	courant = listeCom;

	data *listeData, *courantData;
	listeData = listeDatas;
	courantData = listeData;

	printf("\nAdresses\tDonnes");
	printf("\n");	

	/* affichage de la memoire OS */
	printf("\n[0x00000000]");
	printf("\tmemoire de l'OS");
	printf("\n    ...     ");
	printf("\tmemoire de l'OS");
	printf("\n[0x003FFFF0]");
	printf("\tmemoire de l'OS");

	printf("\n");

	if(listeCom != NULL) {
	while(listeCom != NULL) {

		printf("\n[0x");

		for(int i=0; i<8; i++) {
			printf("%c", listeCom->adresse[i]);
		};

		printf("]\t");

		for(int i=0; i<32; i++) {
			printf("%c", listeCom->codeBinaire[i]);

			if(i%4 == 0 && i != 31 && i != 0) {
				printf(" ");
			}
	 	}

	 	if(listeCom->suivant == NULL) {
	 		printf("\n[0x");
	 		creationAdresseInstruction(&listeCom, &courant, 7);

			for(int i=0; i<8; i++) {
				printf("%c", courant->adresse[i]);
			}; 		
			printf("]");
	 	}
		listeCom = listeCom->suivant;
	}
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
		printf("\n    ...     ");
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
		printf("\n[0x0FFFFFFF]");
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
	}else {
		printf("\n[0x00400000]"); 	
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
		printf("\n    ...     ");
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
		printf("\n[0x0FFFFFFF]");
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");		
	}

	printf("\n");

	printf("\n[0x10000000]");
	printf("\tmemoire Static");
	printf("\n    ...     ");
	printf("\tmemoire Static");
	printf("\n[0x1000FFFF]");
	printf("\tmemoire Static");	

	printf("\n");

	if(listeData != NULL) {
	while(listeData != NULL) {

		if(listeData->taille == 4) {
			printf("\n[0x");

			for(int i=0; i<8; i++) {
				printf("%c", listeData->adresse[i]);
			}

			printf("]\t");

			for(int i=0; i<32; i++) {
				printf("%c", listeData->dataValeur[i]);

				if((1+i)%4 == 0 && i != 32 && i != 0) {
					printf(" ");
				}
		 	}
		}else if(listeData->taille == 1) {
			if(listeData->adresse[7]=='0' || listeData->adresse[7]=='4' || listeData->adresse[7]=='8' || listeData->adresse[7]=='C') {
				printf("\n[0x");

				for(int i=0; i<8; i++) {
					printf("%c", listeData->adresse[i]);
				}
				printf("]\t");			
			}else {
				printf(" ");
			}	

			for(int i=0; i<8; i++) {
				printf("%c", listeData->dataValeur[i]);

				if(i == 3) {
					printf(" ");
				}
		 	}		
		}else {
			if(listeData->adresse[7]=='0' || listeData->adresse[7]=='4' || listeData->adresse[7]=='8' || listeData->adresse[7]=='C') {
				printf("\n[0x");

				for(int i=0; i<8; i++) {
					printf("%c", listeData->adresse[i]);
				}
				printf("]");			
			}
			
			printf("\t");

			for(int i=listeData->taille*8; i>-1; i--) {
				printf("%c", listeData->dataValeur[i]);

				if(i%4 == 0 && i != 31 && i != 0) {
					printf(" ");
				}
		 	}	
		}
		 	if(listeData->suivant == NULL) {
		 		printf("\n[0x");
		 		creationAdresseData(&listeData, &courantData, 7);

				for(int i=0; i<8; i++) {
					printf("%c", courantData->adresse[i]);
				}; 		
				printf("]");
		 	}

		listeData = listeData->suivant;
	}
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
		printf("\n    ...     ");
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
		printf("\n[0x7FFFFFFC]");
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
	}else {
		printf("\n[0x10010000]");
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
		printf("\n    ...     ");
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
		printf("\n[0x7FFFFFFC]");
		printf("\t0000 0000 0000 0000 0000 0000 0000 0000");
	}
}