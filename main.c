#include "consoleEtFichier.h"
#include "encodage.h"
#include "affichageConsole.h"


int main() {

	char sortieBoucle = '0';
	char mode = 's';

	FILE * ficOutB = fopen("fichierSortieBinaire.txt", "a");
	FILE * ficOutH = fopen("fichierSortieHexa.txt", "a");
	FILE * ficIn = fopen("fichierEntree.txt", "r");

	do {
		printf("\nChoix du mode :\n\t-entree des commandes dans la console (1)\n\t-lecture d'un fichier de commandes(2)\n\t> ");
		scanf("%c",&mode);
	}while(mode != '0' && mode != '1');

	if(mode == '1') {
		while(sortieBoucle == '0') {
			consoleLectureCommande();
			affichageStringCommande();
			minusculeStringCommande();
			decodageInstruction();
			affichageBinaireCommande();

			do {
				printf("\nContinuer? OUI (0) ou NON (1) > ");
				scanf("%c",&sortieBoucle);
			}while(sortieBoucle != '0' && sortieBoucle != '1');
		}		
	}else {
		while(sortieBoucle == '0') {
			printf("/1");
			fichierLectureCommande(ficIn);
			affichageStringCommande();

			minusculeStringCommande();

			decodageInstruction();
			affichageBinaireCommande();
			convertCommande();

			if(ecritUCharTab(ficOutB, 'b')) printf("\nEcriture B reussie.");
			else printf("\nErreur d'ecriture B.");
			
			convertCommande();
			
			if(ecritUCharTab(ficOutH, 'h')) printf("\nEcriture H reussie.");
			else printf("\nErreur d'ecriture H.");

			do {
				printf("\nContinuer? OUI (0) ou NON (1) > ");
				scanf("%c",&sortieBoucle);
			}while(sortieBoucle != '0' && sortieBoucle != '1');
		}			
	}

	printf("\nAu revoir\n");

	fclose (ficIn);
	fclose (ficOutB);
	fclose (ficOutH);

	return(0);
}