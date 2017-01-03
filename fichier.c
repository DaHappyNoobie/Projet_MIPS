#include "fichier.h"

void consoleLectureCommande() {

	viderBuffer();

	printf("\nEntrer la ligne de commande : ");
	/*scanf("%[^\n]",&commande);*/
	fgets(commandeString, 30, stdin);
}

int fichierLectureCommande(FILE * fichier) {

	if (!feof(fichier)) {
		for(int i=0; i<30;i++){
			commandeString[i] = ' ';
		}

		if (fgets(commandeString,30,fichier)!=NULL) {

			//puts(commandeString);
		}
		return 1;
	}
	else {
		printf("\nFin du fichier.\n");
		return 0;
	}

}

char ecritUCharTab(FILE * fichier, char type) {

	if (type == 'b') {

		for (int i=0;i<32;i++) {

		fprintf(fichier,"%c", commandeBinaire[i]);

		}

	}
	else if (type == 'h') {

		for (int i=0;i<8;i++) {

		fprintf(fichier,"%c", commandeHexa[i]);

		}

	}
	else printf("\nMauvais type.\n");
	return '1';
}

char ecritListe(FILE * fichierB, FILE * fichierH, listeCommande *l) {

	commande *courant;
	courant = *l;

	while ( courant != NULL ) {

		for (int i=0;i<32;i++) {
			fprintf(fichierB,"%c", courant->codeBinaire[i]);
		}

		for (int i=0;i<8;i++) {
			fprintf(fichierH,"%c", courant->codeHexa[i]);
		}

		courant = courant->suivant;
	}

	return '1';
}

void viderBuffer() { /* Cette fonction nous permet d'etre sur que le buffer est vide. */

   	char c;

    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
