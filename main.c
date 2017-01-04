#include "affichageConsole.h"

char choixMode();
char choixInstruction1();
char choixInstruction2();

int main() {

	char sortieBoucle = '1';
	char mode = 's';
	int etat = -1;

	/* on efface les fichiers de sorties */
	remove("fichierSortieBinaire.txt");
	remove("fichierSortieHexa.txt");

	/* creation des FILE */
	FILE * ficOutB = fopen("fichierSortieBinaire.txt", "a");
	FILE * ficOutH = fopen("fichierSortieHexa.txt", "a");
	FILE * ficIn = fopen("fichierEntree.txt", "r");

	/* menu principal, celui avec le choix des modes */
	do {

		mode = choixMode();

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

					sortieBoucle = choixInstruction1();	

				}else if(sortieBoucle == '2') { 
				/* instruction 2 : récapitulatif des commandes */

					/* affichage de la liste des commandes */
					affichageListeCommande();
					
					viderBuffer();
					sortieBoucle = choixInstruction1();	
				}else if(sortieBoucle == '3') { 
				/* instruction 3 : récapitulatif des labels */

					/* affichage de la liste des labels */
					affichageListeLabel();
					
					viderBuffer();
					sortieBoucle = choixInstruction1();	

				}else if(sortieBoucle == '4') {
				/* instruction 3 : enregistrer cette commande */

					/* écriture dans les fichiers */
					printf("\nEcriture dans le fichier : %c", ecritUCharTab(ficOutB, 'b'));
					printf("\nEcriture dans le fichier : %c", ecritUCharTab(ficOutH, 'h'));
				
					viderBuffer();
					sortieBoucle = choixInstruction1();	
				}else if(sortieBoucle == '5') {
				/* instruction 3 : enregistrer cette commande */

					/* écriture dans les fichiers */
					printf("\nEcriture dans les fichiers : %c", ecritListe(ficOutB, ficOutH, &listeCommandes));

					viderBuffer();
					sortieBoucle = choixInstruction1();	
				}
			}		
		}else if(mode == '2') {

			viderBuffer();
			sortieBoucle = choixInstruction2();
			viderBuffer();

			while(sortieBoucle != 'q' && sortieBoucle != 'Q') {

				if(sortieBoucle == '1') {
				/* instruction 1 : étape par étape */

					if(fichierLectureCommande(ficIn)){

						affichageStringCommande();
						minusculeStringCommande();

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

								if(ecritUCharTab(ficOutB, 'b')) printf("\nEcriture B reussie.");
								else printf("\nErreur d'ecriture B.");

								if(ecritUCharTab(ficOutH, 'h')) printf("\nEcriture H reussie.");
								else printf("\nErreur d'ecriture H.");
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

								if(ecritUCharTab(ficOutB, 'b')) printf("\nEcriture B reussie.");
								else printf("\nErreur d'ecriture B.");

								if(ecritUCharTab(ficOutH, 'h')) printf("\nEcriture H reussie.");
								else printf("\nErreur d'ecriture H.");
							break;
							case 3 : /* seulement un label */
								/* affichages */
								affichageLabel();

								/* mise a jour de la liste de commandes */
								insererLabel(&listeLabels, &listeCommandes);
							break;
							//case 4 : /*Pas d'instruction ni de label*/
						}

						//viderBuffer();
						printf("\nAppuyez sur Entrée pour continuer, ou Q pour quitter > ");
						scanf("%c",&sortieBoucle);
						if(sortieBoucle==10) sortieBoucle='1';
						else if(sortieBoucle=='Q' || sortieBoucle=='q') viderBuffer();


					}
					else sortieBoucle='Q';

				}
				else if(sortieBoucle == '2') {

					if(fichierLectureCommande(ficIn)){

						affichageStringCommande();
						minusculeStringCommande();

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

								if(ecritUCharTab(ficOutB, 'b')) printf("\nEcriture B reussie.");
								else printf("\nErreur d'ecriture B.");

								if(ecritUCharTab(ficOutH, 'h')) printf("\nEcriture H reussie.");
								else printf("\nErreur d'ecriture H.");
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

								if(ecritUCharTab(ficOutB, 'b')) printf("\nEcriture B reussie.");
								else printf("\nErreur d'ecriture B.");

								if(ecritUCharTab(ficOutH, 'h')) printf("\nEcriture H reussie.");
								else printf("\nErreur d'ecriture H.");
							break;
							case 3 : /* seulement un label */
								/* affichages */
								affichageLabel();

								/* mise a jour de la liste de commandes */
								insererLabel(&listeLabels, &listeCommandes);
							break;
							//case 4 : /*Pas d'instruction ni de label*/
						}

						sortieBoucle='2';

					}
					else sortieBoucle='Q';

				}
				else if(sortieBoucle == '3') {
				/* instruction 3 : récapitulatif des commandes */

					/* affichage de la liste des commandes */
					affichageListeCommande();

					viderBuffer();
					sortieBoucle = choixInstruction2();
				}else if(sortieBoucle == '4') {
				/* instruction 4 : récapitulatif des labels */

					/* affichage de la liste des labels */
					affichageListeLabel();

					viderBuffer();
					sortieBoucle = choixInstruction2();

				}
			}
		}

	}while(mode != 'q' && mode != 'Q');

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
	}while(c != '1' && c != '2' && c != 'q' && c != 'Q');

	return c;
}

char choixInstruction1() {

	char c;

	do {
		printf("\n****************************************************************");
		printf("\n*  Choix :                                                     *");
		printf("\n*\t- entrer une commande                 (1)              *");
		printf("\n*\t- recapitulatif des commandes         (2)              *");
		printf("\n*\t- recapitulatif des labels            (3)              *");
		printf("\n*\t- enregistrer cette commande          (4)              *");
		printf("\n*\t- enregistrer toutes les commandes    (5)              *");
		printf("\n*\t- quitter (retour au menu principal)  (Q)              *");
		printf("\n*\t> ");

		scanf("%c",&c);
	}while(c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != 'q' && c != 'Q');

	return c;
}

char choixInstruction2() {

	char c;

	do {
		printf("\n****************************************************************");
		printf("\n*  Choix :                                                     *");
		printf("\n*\t- lecture commandes une par une       (1)              *");
		printf("\n*\t- lecture complete                    (2)              *");
		printf("\n*\t- recapitulatif des commandes         (3)              *");
		printf("\n*\t- recapitulatif des labels            (4)              *");
		printf("\n*\t- quitter (retour au menu principal)  (Q)              *");
		printf("\n*\t> ");

		scanf("%c",&c);
	}while(c != '1' && c != '2' && c != '3' && c != '4'&& c != 'q' && c != 'Q');

	return c;
}