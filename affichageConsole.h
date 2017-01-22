#include "fichier.h"

void affichageBinaireCommande(char commandeBinaire[]);
void affichageHexaCommande(char commandeHexa[]);
void affichageLabel(char labelNom[]);
void affichageData(char dataBinaire[], char dataNom[], int tailleData);
void minusculeStringCommande(char commandeString[]);
void affichageListeCommande(listeCommande *listeCommandes);
void affichageListeLabel(listeLabel *listeLabels);
void affichageListeData(listeData *listeDatas);
void affichageMemoire(listeCommande *listeCommandes, listeData *listeDatas);