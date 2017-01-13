#include "simulation.h"

void adresseRegistre(int);
void adresseRegistreBinaire(int);
int decodageInstruction();
int verificationEtiquette();
int verificationData();
void encodageInstructionR( char[], char[], char[]);
void encodageInstructionI(char opcode[],  char operandes[]);
void encodageInstructionJ();
void encodageLabels();
void encodageInstructionValeur(int *indice1, int indice2, int taille, int ordre);
void encodageInstructionRegistre(int *indice,int indice2, int ordre);
void encodageValeur(int indice);
void encodageData(int indice);
void encodageImmediat(int indice);
void encodageTarget(int *indice);
int chercherRegistre(int);
int chercherValeur(int indice);
int cherchertype(int indice);
void convertCommande(); //convertit la commande binaire en commande hexa (et stocke dans commandeHexa[] */
