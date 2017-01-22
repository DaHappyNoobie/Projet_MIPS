#include "encodage.h"

void consoleLectureCommande(char[]);
int fichierLectureCommande(FILE * fichier,char commandeString[]);
char ecritUCharTab(FILE * fichier, char type, char commandeBinaire[], char commandeHexa[]);
char ecritListe(FILE * fichierB, FILE * fichierH, listeCommande *l, char commandeBinaire[], char commandeHexa[]);
void viderBuffer();