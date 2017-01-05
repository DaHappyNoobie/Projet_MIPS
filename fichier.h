#include "encodage.h"

void consoleLectureCommande();
int fichierLectureCommande();
char ecritUCharTab(FILE * fichier, char type);
char ecritListe(FILE * fichierB, FILE * fichierH, listeCommande *l);
void viderBuffer();