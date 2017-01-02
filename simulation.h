#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ******************************************************************** */
/* structure de la liste chainee des commandes */

typedef struct commandeStructure commande;
struct commandeStructure {

	unsigned char adresse[8];
	unsigned char codeBinaire[32]; /* Commande au format binaire */
	unsigned char codeHexa[8];

	struct commandeStructure* suivant; /* adresse du successeur */
};

typedef commande *listeCommande;

/* ******************************************************************** */
/* structure de la liste chainee des labels */

typedef struct labelStructure label;
struct labelStructure {

	unsigned char adresse[8];
	unsigned char nom[10];

	struct labelStructure* suivant; /* adresse du successeur */
};

typedef label *listeLabel;

/* ******************************************************************** */
/* variables d'encodages */ 

char commandeString[30];
unsigned char commandeBinaire[32];
unsigned char commandeHexa[8];
unsigned char labelNom[10];

/* ******************************************************************** */
/* variables de stockages pour l'encodage */ 
/* variable qui servira a stocker des addresses/valeurs en bit */

char registreBinaire[5]; 
char valeurBinaire[5];
char immediatBinaire[26];

/* ******************************************************************** */
/* liste chainee pour la simulation */

listeCommande listeCommandes;
listeLabel listeLabels;

/* ******************************************************************** */
/* Fonctions de la liste chainé contenant les commandes */

void insererCommande(listeCommande *l);
commande* commandeNouveau();
void creationAdresseInstruction(listeCommande *cou, listeCommande *nouv, int indice);

/* ******************************************************************** */
/* Fonctions de la liste chainé contenant les labels */

void insererLabel(listeLabel *l, listeCommande *ll);
label* labelNouveau();
void creationAdresseLabel(listeCommande *cou, listeLabel *nouv, int indice);

/* ******************************************************************** */
/* Fonctions communes */

void affichageStringCommande();