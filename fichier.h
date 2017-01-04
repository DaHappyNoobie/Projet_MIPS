#include "encodage.h"

void consoleLectureCommande();
void fichierLectureCommande();
char ecritUCharTab(FILE * fichier, char type);
char ecritListe(FILE * fichierB, FILE * fichierH, listeCommande *l);
void viderBuffer();