#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char commande[30];
unsigned char commandeBinaire[32];
unsigned char commandeHexa[8];
char registreBinaire[5]; /* variable qui servira a sotcker des addresses de bit */
char valeurBinaire[5];
char immediatBinaire[26];
static char labelAdresse[32] = {'0','0','0','1', '0','0','1','0', '0','0','0','0', '0','0','0','0', '0','0','0','0', '0','0','1','0', '0','0','0','0', '0','0','0','0'};

void consoleLectureCommande();
void affichageStringCommande();
void fichierLectureCommande();
char ecritUCharTab(FILE * fichier, char type);
void viderBuffer();