#include "consoleEtFichier.h"

void adresseRegistre(int);
void adresseRegistreBinaire(int);
void decodageInstruction();
void encodageInstructionR( char[], char[], char[]);
void encodageInstructionI(char opcode[],  char operandes[]);
void encodageInstructionJ();
void encodageInstructionRegistre(int *indice, int ordre);
void encodageValeur(int indice);
void encodageImmediat(int indice);
int chercherRegistre(int);
int chercherValeur(int indice);
void convertCommande(); //convertit la commande binaire en commande hexa (et stocke dans commandeHexa[] */
