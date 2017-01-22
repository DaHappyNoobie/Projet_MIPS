#include "simulation.h"

void processusSimulation(listeCommande *listeCommandes,listeData *listeDatas, listeLabel *listeLabels, listeCommande *pc, int registres[], int action);
void affichageSimulation(listeCommande *listeCommandes, int registres[], listeCommande *programCounter);
void affichageRegistre(int registres[], int i);
void instructionDecode(listeCommande *programCounter, int registres[]);
void instructionDecodeR(listeCommande *programCounter, int registres[]);
int convBin2Dec(char commande[], int indice1, int taille);
void instructionADD(listeCommande *programCounter, int registres[]);
void instructionAND(listeCommande *programCounter, int registres[]);
void instructionMFHI(listeCommande *programCounter, int registres[]);
void instructionADDI(listeCommande *programCounter, int registres[]);