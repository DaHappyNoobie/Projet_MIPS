#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ******************************************************************** */
/* structure de la liste chainee des commandes */

typedef struct commandeStructure commande;
struct commandeStructure {

	unsigned char codeString[30];
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
/* structure de la liste chainee de la data */

typedef struct dataStructure data;
struct dataStructure {

	unsigned char adresse[8];
	unsigned char nom[10];
	int taille; /* taille en octet */
	unsigned char dataValeur[32]; /* data au format binaire */

	struct dataStructure* suivant; /* adresse du successeur */
};

typedef data *listeData;

/* ******************************************************************** */
/* Fonctions de la liste chainé contenant les commandes */

void insererCommande(listeCommande *l,char commandeBinaire[],char commandeHexa[], char commandeString[]);
commande* commandeNouveau();
void creationAdresseInstruction(listeCommande *cou, listeCommande *nouv, int indice);

/* ******************************************************************** */
/* Fonctions de la liste chainé contenant les labels */

void insererLabel(listeLabel *l, listeCommande *ll, char labelNom[]);
label* labelNouveau();
void creationAdresseLabel(listeCommande *cou, listeLabel *nouv, int indice);

/* ******************************************************************** */
/* Fonctions de la liste chainé contenant la Data */

void insererData(listeData *l, char dataBinaire[], char dataNom[], int tailleData);
void creationAdresseData(listeData *cou, listeData *nouv, int indice);
data* dataNouveau();

/* ******************************************************************** */
/* Fonctions communes */

void affichageStringCommande(char commandeString[]);