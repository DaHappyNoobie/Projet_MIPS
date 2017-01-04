#include "affichageConsole.h"

void affichageBinaireCommande() {
	
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

void affichageHexaCommande() {
	
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

void affichageLabel() {
	char c;
	int i=0;

	printf("\nNom du label : ");

	do{
		c = labelNom[i];
		printf("%c", c);
		i++;
	}while(labelNom[i]!='\0' && i<10);
}

void minusculeStringCommande(void) {

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

void affichageListeCommande() {
	
	commande *courant;
	courant = listeCommandes;
	char c;

	printf("\nAdresses       hexadecimal\t        Commandes binaire       ");
	printf("\n");

	while ( courant != NULL ) {
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
		courant = courant->suivant;
	}
}

void affichageListeLabel() {
	
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