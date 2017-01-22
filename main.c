#include "affichageConsole.h"

char choixMode();
char choixInstruction1();
char choixInstruction2();
char choixInstruction5();

int main() {

	listeCommande listeCommandes =NULL;
	listeLabel listeLabels = NULL;
	listeData listeDatas = NULL;

	listeCommande programCounter = NULL;

	char commandeString[30];
	char commandeBinaire[32];
	char commandeHexa[8];
	char labelNom[10];
	char dataBinaire[32];
	char dataNom[10];
	int tailleData;

	int registres[35]; /* 0->31 registres generaux, 32->34 registres spéciaux (PC, HI, LO) */

	char sortieBoucle = '1';
	char mode = 's';
	int etat = -1;

	data *plop;

	/* on efface les fichiers de sorties */
	remove("fichierSortieBinaire.txt");
	remove("fichierSortieHexa.txt");

	/* creation des FILE */
	FILE * ficOutB = fopen("fichierSortieBinaire.txt", "a");
	FILE * ficOutH = fopen("fichierSortieHexa.txt", "a");
	FILE * ficIn = fopen("fichierEntree.txt", "r");

	/* Initialisation des registres */
	for(int i=0; i<35; i++) {
		registres[i] = 0;
	}

	/* menu principal, celui avec le choix des modes */
	do {

		mode = choixMode();

		if(mode == '1') {
		/* mode 1 : commande par commande */

			sortieBoucle = '1';
			while(sortieBoucle != 'q' && sortieBoucle != 'Q') {

				if(sortieBoucle == '1') {
				/* instruction 1 : entrer une commandes */

					/* traitement de la commande en entree */
					consoleLectureCommande(commandeString);
					minusculeStringCommande(commandeString);
					/* décodage */
					etat = decodageInstruction(&listeCommandes, &listeDatas, commandeHexa, commandeString, dataBinaire, &(tailleData), dataNom, labelNom, commandeBinaire);

					switch(etat) {
						case 1 : /* seulement une instruction */
							/* convertion en hexadecimal */
							convertCommande( commandeBinaire, commandeHexa);

							/* affichages */ 
							affichageBinaireCommande(commandeBinaire);
							affichageHexaCommande(commandeHexa); 

							/* mise a jour de la liste de commandes */
							insererCommande(&listeCommandes, commandeBinaire, commandeHexa, commandeString);
						break;
						case 2 : /* un label et une instruction */
							etat = decodageInstruction(&listeCommandes, &listeDatas, commandeHexa, commandeString, dataBinaire, &tailleData, dataNom, labelNom, commandeBinaire);

							/* convertion en hexadecimal */
							convertCommande( commandeBinaire, commandeHexa);

							/* affichages */ 
							affichageLabel(labelNom);
							affichageBinaireCommande(commandeBinaire);
							affichageHexaCommande(commandeHexa); 

							/* mise a jour de la liste de labels */
							insererLabel(&listeLabels, &listeCommandes, labelNom);
							
							/* mise a jour de la liste de commandes */
							insererCommande(&listeCommandes, commandeBinaire, commandeHexa, commandeString);
						break;
						case 3 : /* seulement un label */

							/* affichages */ 
							affichageLabel(labelNom);

							/* mise a jour de la liste de commandes */
							insererLabel(&listeLabels, &listeCommandes, labelNom);
						break;
						case 5 : /* seulement un data a enregistrer */
							printf("\n%d", tailleData);
							/* affichages */
							affichageData(dataBinaire, dataNom, tailleData);
							insererData(&listeDatas, dataBinaire, dataNom, tailleData);
							plop = listeDatas;
							printf("\n%d",(plop->taille));
						break;
					}

					viderBuffer();
					sortieBoucle = choixInstruction1();	

				}else if(sortieBoucle == '2') { 
				/* instruction 2 : récapitulatif des commandes */

					/* affichage de la liste des commandes */
					affichageListeCommande(&listeCommandes);
					
					viderBuffer();
					sortieBoucle = choixInstruction1();	
				}else if(sortieBoucle == '3') { 
				/* instruction 3 : récapitulatif des labels */

					/* affichage de la liste des labels */
					affichageListeLabel(&listeLabels);
					
					viderBuffer();
					sortieBoucle = choixInstruction1();	

				}else if(sortieBoucle == '4') {
				/* instruction 3 : enregistrer cette commande */

					/* écriture dans les fichiers */
					printf("\nEcriture dans le fichier : %c", ecritUCharTab(ficOutB, 'b', commandeBinaire, commandeHexa));
					printf("\nEcriture dans le fichier : %c", ecritUCharTab(ficOutH, 'h', commandeBinaire, commandeHexa));
				
					viderBuffer();
					sortieBoucle = choixInstruction1();	
				}else if(sortieBoucle == '5') {
				/* instruction 3 : enregistrer cette commande */

					/* écriture dans les fichiers */
					printf("\nEcriture dans les fichiers : %c", ecritListe(ficOutB, ficOutH, &listeCommandes, commandeBinaire, commandeHexa));

					viderBuffer();
					sortieBoucle = choixInstruction1();	
				}
			}

			viderBuffer();
		}else if(mode == '2') {

			viderBuffer();
			sortieBoucle = choixInstruction2();
			viderBuffer();

			while(sortieBoucle != 'q' && sortieBoucle != 'Q') {

				if(sortieBoucle == '1') {
				/* instruction 1 : étape par étape */

					if(fichierLectureCommande(ficIn, commandeString)){

						affichageStringCommande(commandeString);
						minusculeStringCommande(commandeString);

						etat = decodageInstruction(&listeCommandes, &listeDatas, commandeHexa, commandeString, dataBinaire, &(tailleData), dataNom, labelNom, commandeBinaire);

					switch(etat) {
						case 1 : /* seulement une instruction */
							/* convertion en hexadecimal */
							convertCommande( commandeBinaire, commandeHexa);

							/* affichages */ 
							affichageBinaireCommande(commandeBinaire);
							affichageHexaCommande(commandeHexa); 

							/* mise a jour de la liste de commandes */
							insererCommande(&listeCommandes, commandeBinaire, commandeHexa, commandeString);
						break;
						case 2 : /* un label et une instruction */
							etat = decodageInstruction(&listeCommandes, &listeDatas, commandeHexa, commandeString, dataBinaire, &tailleData, dataNom, labelNom, commandeBinaire);

							/* convertion en hexadecimal */
							convertCommande( commandeBinaire, commandeHexa);

							/* affichages */ 
							affichageLabel(labelNom);
							affichageBinaireCommande(commandeBinaire);
							affichageHexaCommande(commandeHexa); 

							/* mise a jour de la liste de labels */
							insererLabel(&listeLabels, &listeCommandes, labelNom);
							
							/* mise a jour de la liste de commandes */
							insererCommande(&listeCommandes, commandeBinaire, commandeHexa, commandeString);
						break;
						case 3 : /* seulement un label */

							/* affichages */ 
							affichageLabel(labelNom);

							/* mise a jour de la liste de commandes */
							insererLabel(&listeLabels, &listeCommandes, labelNom);
						break;
						case 5 : /* seulement un data a enregistrer */
							printf("\n%d", tailleData);
							/* affichages */
							affichageData(dataBinaire, dataNom, tailleData);
							insererData(&listeDatas, dataBinaire, dataNom, tailleData);
							plop = listeDatas;
							printf("\n%d",(plop->taille));
						break;
					}

						//viderBuffer();
						printf("\nAppuyez sur Entree pour continuer, ou Q pour quitter > ");
						scanf("%c",&sortieBoucle);
						if(sortieBoucle==10) sortieBoucle='1';
						else if(sortieBoucle=='Q' || sortieBoucle=='q') viderBuffer();


					}
					else sortieBoucle='Q';

				}
				else if(sortieBoucle == '2') {

					if(fichierLectureCommande(ficIn, commandeString)){

						affichageStringCommande( commandeString);
						minusculeStringCommande(commandeString);

						etat = decodageInstruction(&listeCommandes, &listeDatas, commandeHexa, commandeString, dataBinaire, &tailleData, dataNom, labelNom, commandeBinaire);

						etat = decodageInstruction(&listeCommandes, &listeDatas, commandeHexa, commandeString, dataBinaire, &(tailleData), dataNom, labelNom, commandeBinaire);

					switch(etat) {
						case 1 : /* seulement une instruction */
							/* convertion en hexadecimal */
							convertCommande( commandeBinaire, commandeHexa);

							/* affichages */ 
							affichageBinaireCommande(commandeBinaire);
							affichageHexaCommande(commandeHexa); 

							/* mise a jour de la liste de commandes */
							insererCommande(&listeCommandes, commandeBinaire, commandeHexa, commandeString);
						break;
						case 2 : /* un label et une instruction */
							etat = decodageInstruction(&listeCommandes, &listeDatas, commandeHexa, commandeString, dataBinaire, &tailleData, dataNom, labelNom, commandeBinaire);

							/* convertion en hexadecimal */
							convertCommande( commandeBinaire, commandeHexa);

							/* affichages */ 
							affichageLabel(labelNom);
							affichageBinaireCommande(commandeBinaire);
							affichageHexaCommande(commandeHexa); 

							/* mise a jour de la liste de labels */
							insererLabel(&listeLabels, &listeCommandes, labelNom);
							
							/* mise a jour de la liste de commandes */
							insererCommande(&listeCommandes, commandeBinaire, commandeHexa, commandeString);
						break;
						case 3 : /* seulement un label */

							/* affichages */ 
							affichageLabel(labelNom);

							/* mise a jour de la liste de commandes */
							insererLabel(&listeLabels, &listeCommandes, labelNom);
						break;
						case 5 : /* seulement un data a enregistrer */
							printf("\n%d", tailleData);
							/* affichages */
							affichageData(dataBinaire, dataNom, tailleData);
							insererData(&listeDatas, dataBinaire, dataNom, tailleData);
							plop = listeDatas;
							printf("\n%d",(plop->taille));
						break;
					}

						sortieBoucle='2';

					}
					else sortieBoucle='Q';

				}else if(sortieBoucle == '4') {
				/* instruction 3 : récapitulatif des commandes */

					/* affichage de la liste des commandes */
					affichageListeCommande(&listeCommandes);

					viderBuffer();
					sortieBoucle = choixInstruction2();
				}else if(sortieBoucle == '4') {
				/* instruction 4 : récapitulatif des labels */

					/* affichage de la liste des labels */
					affichageListeLabel(&listeLabels);

					viderBuffer();
					sortieBoucle = choixInstruction2();

				}
			}	
		}else if(mode == '3') {
			affichageListeData(&listeDatas);

			viderBuffer();
		}else if(mode == '4') {
			affichageMemoire(&listeCommandes, &listeDatas);

			viderBuffer();			
		}else if(mode == '5') {
			sortieBoucle = '0';

			do{
				if((programCounter == NULL) && listeCommandes != NULL) {
					/* on place le pc */
					printf("\nPC remis au debut");
					programCounter = listeCommandes;
				}

				switch(sortieBoucle) {
					case '0' :
					break;
					case '1' :
						processusSimulation( &listeCommandes, &listeDatas, &listeLabels, &programCounter, registres, 1);
					break;
					case '2' :
						processusSimulation( &listeCommandes, &listeDatas, &listeLabels, &programCounter, registres, 2);			
					break;
					default : 
						printf("\nErreur mode simulation (Processus)");
					break;
				}

				if((programCounter == NULL) && listeCommandes != NULL) {
					/* on place le pc */
					printf("\nPC remis au debut");
					programCounter = listeCommandes;
				}

				affichageSimulation( &listeCommandes, registres, &programCounter);

				viderBuffer();
				sortieBoucle = choixInstruction5();

			}while(sortieBoucle != 'q' && sortieBoucle != 'Q');
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
		printf("\n*\t- recapitulatif des variables            (3)           *");
		printf("\n*\t- affichage de la memoire                (4)           *");				
		printf("\n*\t- simulation                             (5)           *");
		printf("\n*\t- quitter                                (Q)           *");
		printf("\n*\t> ");

		scanf("%c",&c);
	}while(c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != 'q' && c != 'Q');

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

char choixInstruction5() {

	char c;

	do {
		printf("\n****************************************************************");
		printf("\n*  Choix :                                                     *");
		printf("\n*\t- etape suivante                      (1)              *");
		printf("\n*\t- lecture complete                    (2)              *");
		printf("\n*\t- quitter (retour au menu principal)  (Q)              *");
		printf("\n*\t> ");

		scanf("%c",&c);
	}while(c != '1' && c != '2' && c != 'q' && c != 'Q');

	return c;
}