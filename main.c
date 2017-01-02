#include "affichageConsole.h"

char choixMode();
char choixInstruction();

int main() {

	char sortieBoucle = '1';
	char mode = 's';
	int etat = -1;

	mode = choixMode();

	/* si l'utilisateur quitte */
	if(mode == 'q' || mode == 'Q') {
		printf("\nAu revoir\n");
		return 0;
	}

	/* on efface les fichiers de sorties */
	remove("fichierSortieBinaire.txt");
	remove("fichierSortieHexa.txt");

	/* creation des FILE */
	FILE * ficOutB = fopen("fichierSortieBinaire.txt", "a");
	FILE * ficOutH = fopen("fichierSortieHexa.txt", "a");
	FILE * ficIn = fopen("fichierEntree.txt", "r");

	if(mode == '1') {
	/* mode 1 : commande par commande */

		while(sortieBoucle != 'q' && sortieBoucle != 'Q') {

			if(sortieBoucle == '1') {
			/* instruction 1 : entrer une commandes */

				/* traitement de la commande en entree */
				consoleLectureCommande();
				minusculeStringCommande();
				printf("\n%c",commandeString[28]);
				/* décodage */
				etat = decodageInstruction();

				switch(etat) {
					case 1 : /* seulement une instruction */
						/* convertion en hexadecimal */
						convertCommande();

						/* affichages */ 
						affichageBinaireCommande();
						affichageHexaCommande(); 

						/* mise a jour de la liste de commandes */
						insererCommande(&listeCommandes);
					break;
					case 2 : /* un label et une instruction */
						etat = decodageInstruction();

						/* convertion en hexadecimal */
						convertCommande();

						/* affichages */ 
						affichageLabel();
						affichageBinaireCommande();
						affichageHexaCommande(); 

						/* mise a jour de la liste de labels */
						insererLabel(&listeLabels, &listeCommandes);
						
						/* mise a jour de la liste de commandes */
						insererCommande(&listeCommandes);
					break;
					case 3 : /* seulement un label */
						/* affichages */ 
						affichageLabel();

						/* mise a jour de la liste de commandes */
						insererLabel(&listeLabels, &listeCommandes);
					break;
				}

				sortieBoucle = choixInstruction();	

			}else if(sortieBoucle == '2') { 
			/* instruction 2 : récapitulatif des commandes */

				/* affichage de la liste des commandes */
				affichageListeCommande();
				
				viderBuffer();
				sortieBoucle = choixInstruction();	
			}else if(sortieBoucle == '3') { 
			/* instruction 3 : récapitulatif des labels */

				/* affichage de la liste des labels */
				affichageListeLabel();
				
				viderBuffer();
				sortieBoucle = choixInstruction();	

			}else if(sortieBoucle == '4') {
			/* instruction 3 : enregistrer cette commande */

				/* écriture dans les fichiers */
				printf("\nEcriture dans le fichier : %c", ecritUCharTab(ficOutB, 'b'));
				printf("\nEcriture dans le fichier : %c", ecritUCharTab(ficOutH, 'h'));
			
				viderBuffer();
				sortieBoucle = choixInstruction();	
			}else if(sortieBoucle == '5') {
			/* instruction 3 : enregistrer cette commande */

				/* écriture dans les fichiers */
				printf("\nEcriture dans les fichiers : %c", ecritListe(ficOutB, ficOutH, &listeCommandes));

				viderBuffer();
				sortieBoucle = choixInstruction();	
			}
		}		
	}else if(mode == '2') {
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

char choixMode() {
	
	char c;

	do {
		printf("\n****************************************************************");
		printf("\n*  Choix du mode :                                             *");
		printf("\n*\t- entree des commandes dans la console   (1)           *");
		printf("\n*\t- lecture d'un fichier de commandes      (2)           *");
		printf("\n*  Attention les fichiers de sortie seront effaces             *");
		printf("\n*\t- quitter                                (Q)           *");
		printf("\n*\t> ");

		scanf("%c",&c);
	}while(c != '0' && c != '1' && c != 'q' && c != 'Q');

	return c;
}

char choixInstruction() {
	
	char c;

	do {
		printf("\n****************************************************************");
		printf("\n*  Choix :                                                     *");
		printf("\n*\t- entrer une commande                 (1)              *");
		printf("\n*\t- recapitulatif des commandes         (2)              *");
		printf("\n*\t- recapitulatif des labels            (3)              *");
		printf("\n*\t- enregistrer cette commande          (4)              *");
		printf("\n*\t- enregistrer toutes les commandes    (5)              *");
		printf("\n*\t- quitter                             (Q)              *");
		printf("\n*\t> ");

		scanf("%c",&c);
	}while(c != '1' && c != '2' && c != '3' && c != '4' && c != 'q' && c != 'Q');

	return c;
}