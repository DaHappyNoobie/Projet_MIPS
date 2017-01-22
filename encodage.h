#include "processus.h"

void adresseRegistre(int indice, char commandeString[], char registreBinaire[]);
void adresseRegistreBinaire(int, char registreBinaire[]);
int decodageInstruction( listeCommande *listeCommandes, listeData *listeDatas, char commandeHexa[], char commandeString[], char dataBinaire[], int *tailleData, char dataNom[], char labelNom[], char commandeBinaire[]);
int verificationEtiquette(char commandeString[]);
int verificationData(char commandeString[]);
void encodageInstructionR(char opcode[], char function[],  char operandes[], char commandeBinaire[], char commandeString[]);
void encodageInstructionI( listeData *listeDatas, char opcode[], char operandes[], char commandeBinaire[], char commandeString[]);
void encodageInstructionJ(char opcode[], char commandeBinaire[]);
void encodageLabels(char commandeString[], char labelNom[]);
void encodageInstructionValeur(int *indice1, int indice2, int taille, int ordre, char commandeBinaire[], char commandeString[]);
void encodageInstructionRegistre(int *indice,int indice2, int ordre, char commandeBinaire[], char commandeString[]);
void encodageValeur(int indice, char commandeString[], char valeurBinaire[]);
void encodageData(int indice, char commandeString[], char dataBinaire[], char dataNom[], int tailleData);
void encodageImmediat(int indice, char commandeString[], char immediatBinaire[]);
void encodageTarget(int *indice);
int chercherRegistre(int, char commandeString[]);
int chercherValeur(int indice, char commandeString[]);
int cherchertype(int indice, char commandeString[]);
void convertCommande(char commandeBinaire[], char commandeHexa[]); //convertit la commande binaire en commande hexa (et stocke dans commandeHexa[] */
