#include "processus.h"

void processusSimulation(listeCommande *listeCommandes, listeData *listeDatas, listeLabel *listeLabels, listeCommande *programCounter, int registres[], int action) {
/* Fonction qui permet de gerer le processus de Simulation */
/* action = 1 : étape suivante */
/* action = 2 : lecture totale */

	commande *pc;
	pc = *programCounter;

	if(action == 1) {
		if(pc != NULL) {
			instructionDecode(programCounter, registres);
			pc = pc->suivant;
		}
	}

	*programCounter = pc;		
}

void affichageSimulation(listeCommande *listeCommandes, int registres[], listeCommande *pc) {
	commande *courant;
	courant = *listeCommandes;
	int i = 0;

	while(courant != NULL || i<36) {

		printf("\n");

		affichageRegistre( registres, i);

		if(i<32) {
			if(registres[i]>=1000)
				printf(" \t||");
			else if(registres[i]>=100)
				printf("  \t||");
			else if(registres[i]>=10)	
				printf("   \t||");
			else
				printf("    \t||");				
		}else {
			if(registres[i-1]>=1000)
				printf(" \t||");
			else if(registres[i-1]>=100)
				printf("  \t||");
			else if(registres[i-1]>=10)	
				printf("   \t||");
			else
				printf("    \t||");			
		}



		i++;
		if(courant != NULL) {

			if(courant == *pc) {
				printf("  >   ");
			}else {
				printf("\t");
			}

			for(int j=0; j<30; j++) {
				if( courant->codeString[j] == '\n') {
					printf(" ");
				}else {
				printf("%c", courant->codeString[j]);					
				}
			}

			courant = courant->suivant;
		}
	}
}     

void affichageRegistre(int registres[], int i) {

	if(i == 0) {
		printf("r0 = ");
	}else if(i == 1) {
		printf("at = ");		
	}else if(i == 2 || i == 3) {
		printf("v%d = ",i-2);		
	}else if(i >= 4 && i <=7) {
		printf("a%d = ",i-4);		
	}else if(i >= 8 && i <=15) {
		printf("t%d = ",i-8);		
	}else if(i >= 16 && i <=23) {
		printf("s%d = ",i-16);		
	}else if(i >= 24 && i <=25) {
		printf("t%d = ",i-16);		
	}else if(i >= 26 && i <=27) {
		printf("k%d = ",i-26);		
	}else if(i == 28) {
		printf("gp = ");		
	}else if(i == 29) {
		printf("sp = ");		
	}else if(i == 30) {
		printf("s8 = ");		
	}else if(i == 31) {
		printf("ra = ");		
	}else if(i == 32) {
		printf("     ");
	}else if(i == 33) {
		printf("pc = ");
	}else if(i == 34) {
		printf("hi = ");
	}else if(i == 35) {
		printf("lo = ");
	}

	if(i<32) {
		printf("%d", registres[i]);
	}else if(i>=33 && i<=35) {
		printf("%d", registres[i-1]);
	}
}

void instructionDecode(listeCommande *programCounter, int registres[]) {
	
	int type = 1; 
	/* 1 : type R */
	/* 2 : type I */
	/* 3 : type J */

	int i = 31;

	commande *pc;
	pc = *programCounter;

	/* on determine si c'est le type R */
	do{
		if(pc->codeBinaire[i] != '0')
			type = 0;
		i--;
	}while(i>25 && type==1);

	if(type == 1) {
		instructionDecodeR(programCounter, registres);
	}else { /* de type I ou J */
		if(pc->codeBinaire[31] == '1' || pc->codeBinaire[28] == '1' || pc->codeBinaire[29] == '1') {
			if(pc->codeBinaire[31] == '1') { /* LW ou SW */
			}else if(pc->codeBinaire[29] == '1') { /* ADDI ou LUI */
				if(pc->codeBinaire[28] == '1') { /* LUI */
				}else { /* ADDI */
					printf("Commande ADDI");
					instructionADDI( programCounter, registres);
				}
			}else if(pc->codeBinaire[27] == '1') { /* BLEZ ou BGTZ */
				if(pc->codeBinaire[26] == '1') { /* BGTZ */
				}else { /* BLEZ */
				}
			}else { /* BEQ ou BNE */
				if(pc->codeBinaire[26] == '1') { /* BNE */
				}else { /* BEQ */
				}
			}
		}
	}
}

void instructionDecodeR(listeCommande *programCounter, int registres[]) {
	/* On cherche à déterminer qu'elle instruction R est concernée */
	commande *pc;
	pc = *programCounter;

	printf("\nType R : ");

	if(pc->codeBinaire[5] == '1') { /* ADD, AND, OR, SLT, SUB et XOR */
		if(pc->codeBinaire[3] == '1') { /* SLT */
			printf("Commande SLT");
			instructionSLT( programCounter, registres);
		}else if(pc->codeBinaire[2] == '1') { /* AND, OR or XOR */
			if(pc->codeBinaire[1] == '1') { /* XOR */
				printf("Commande XOR");
				instructionXOR( programCounter, registres);
			}else if(pc->codeBinaire[0] == '1') { /* OR */
				printf("Commande OR");
				instructionOR( programCounter, registres);
			}else { /* AND */
				printf("Commande AND");
				instructionAND( programCounter, registres);
			}
		}else { /* ADD ou SUB */
			if(pc->codeBinaire[1] == '1') { /* SUB */
				printf("Commande SUB");
				instructionSUB( programCounter, registres);
			}else { /* ADD */
				printf("Commande ADD");
				instructionADD( programCounter, registres);	
			}
		}
	}else { /* DIV, JR, MFHI, MFLO, MULT, ROTR, SLL ou SYSCALL */
		if(pc->codeBinaire[4] == '1') { /* DIV, MFHI, MFLO, MULT */
			if(pc->codeBinaire[3] == '1') { /* DIV ou MULT*/
				if(pc->codeBinaire[1] == '1') { /* DIV */
					printf("Commande DIV");
					instructionDIV( programCounter, registres);
				}else { /* MULT */
					printf("Commande MULT");
					instructionMULT( programCounter, registres);
				}
			}else { /* MFHI ou MFLO */
				if(pc->codeBinaire[1] == '1') { /* MFLO */
					printf("Commande MFLO");
					instructionMFLO( programCounter, registres);
				}else { /* MFHI */
					printf("Commande MFHI");
					instructionMFHI( programCounter, registres);
				}
			}
		}else { /* JR, ROTR, SLL, SRC ou SYSCALL */
			if(pc->codeBinaire[3] == '1') { /* JR, SYSCALL */
				if(pc->codeBinaire[2] == '1') { /* SYSCALL */
				}else { /* JR */
				}
			}else { /* ROTR, SLL ou SRC */
				if(pc->codeBinaire[1] == '1') { /* ROTR ou SRC */
					if(pc->codeBinaire[21] = '1') { /* ROTR */
					}else { /* SRL */
					}
				}else { /* SLL */
				}
			}			
		}
	}
}

int convBin2Dec(char commande[], int indice1, int taille) {
		int i = indice1;
		int resultat = 0;
		int tamp = 2;

		while(i > indice1-taille) {
			tamp = 1;
			if(commande[i] == '1') {
				for(int j=i; j > indice1-taille+1; j--) {
					tamp = tamp * 2;
				}				
				resultat = resultat + tamp;
			}
			i--;
		}

		return resultat;
}

void instructionADD(listeCommande *programCounter, int registres[]) {

	commande *pc;
	pc = *programCounter;

	registres[convBin2Dec(pc->codeBinaire, 15, 5)] = registres[convBin2Dec(pc->codeBinaire, 25, 5)] + registres[convBin2Dec(pc->codeBinaire, 20, 5)];
}

void instructionDIV(listeCommande *programCounter, int registres[]) {

	int valeur = 0;
	commande *pc;
	pc = *programCounter;	

	valeur = registres[convBin2Dec(pc->codeBinaire, 25, 5)] / registres[convBin2Dec(pc->codeBinaire, 20, 5)];
	registres[34] = valeur;
	registres[33] = registres[convBin2Dec(pc->codeBinaire, 25, 5)] - valeur * registres[convBin2Dec(pc->codeBinaire, 20, 5)];
}

void instructionAND(listeCommande *programCounter, int registres[]) {

	commande *pc;
	pc = *programCounter;

	unsigned int valeur = 0;
	int reste = -1;

	char registres1[32], registres2[32], registres3[32];

	valeur = registres[convBin2Dec(pc->codeBinaire, 25, 5)];

	for(int i=0; i<32; i++) {
		reste = valeur%2;
		if( reste == 0 ){
			registres1[i] = '0';
		}else {
			registres1[i] = '1';
			valeur = valeur-1;			
		}
		valeur = valeur/2;
	}

	valeur = registres[convBin2Dec(pc->codeBinaire, 20, 5)];

	for(int i=0; i<32; i++) {
		reste = valeur%2;
		if( reste == 0 ){
			registres2[i] = '0';
		}else {
			registres2[i] = '1';
			valeur = valeur-1;			
		}
		valeur = valeur/2;
	}

	for(int i=0; i<32; i++) {
		if(registres1[i] == '1' && registres2[i] == '1') {
			registres3[i] = '1';
		}else {
			registres3[i] = '0';
		}
	}

	printf("\n%d", convBin2Dec(registres3, 31, 32));
	registres[convBin2Dec(pc->codeBinaire, 15, 5)] = convBin2Dec(registres3, 31, 32);
}

void instructionMFHI(listeCommande *programCounter, int registres[]) {

	commande *pc;
	pc = *programCounter;

	registres[convBin2Dec(pc->codeBinaire, 15, 5)] = registres[33];
}

void instructionMFLO(listeCommande *programCounter, int registres[]) {

	commande *pc;
	pc = *programCounter;

	registres[convBin2Dec(pc->codeBinaire, 15, 5)] = registres[34];
}

void instructionMULT(listeCommande *programCounter, int registres[]) {

	int valeur = 0;
	commande *pc;
	pc = *programCounter;	

	valeur = registres[convBin2Dec(pc->codeBinaire, 25, 5)] * registres[convBin2Dec(pc->codeBinaire, 20, 5)];
	registres[34] = valeur;
}

void instructionOR(listeCommande *programCounter, int registres[]) {

	commande *pc;
	pc = *programCounter;

	unsigned int valeur = 0;
	int reste = -1;

	char registres1[32], registres2[32], registres3[32];

	valeur = registres[convBin2Dec(pc->codeBinaire, 25, 5)];

	for(int i=0; i<32; i++) {
		reste = valeur%2;
		if( reste == 0 ){
			registres1[i] = '0';
		}else {
			registres1[i] = '1';
			valeur = valeur-1;			
		}
		valeur = valeur/2;
	}

	valeur = registres[convBin2Dec(pc->codeBinaire, 20, 5)];

	for(int i=0; i<32; i++) {
		reste = valeur%2;
		if( reste == 0 ){
			registres2[i] = '0';
		}else {
			registres2[i] = '1';
			valeur = valeur-1;			
		}
		valeur = valeur/2;
	}

	for(int i=0; i<32; i++) {
		if(registres1[i] == '1' || registres2[i] == '1') {
			registres3[i] = '1';
		}else {
			registres3[i] = '0';
		}
	}

	printf("\n%d", convBin2Dec(registres3, 31, 32));
	registres[convBin2Dec(pc->codeBinaire, 15, 5)] = convBin2Dec(registres3, 31, 32);
}

void instructionSLT(listeCommande *programCounter, int registres[]) {

	commande *pc;
	pc = *programCounter;

	if(	registres[convBin2Dec(pc->codeBinaire, 25, 5)] < registres[convBin2Dec(pc->codeBinaire, 20, 5)]) {
		registres[convBin2Dec(pc->codeBinaire, 15, 5)] = 1;
	}else {
		registres[convBin2Dec(pc->codeBinaire, 15, 5)] = 0;		
	}
}

void instructionSUB(listeCommande *programCounter, int registres[]) {

	commande *pc;
	pc = *programCounter;

	registres[convBin2Dec(pc->codeBinaire, 15, 5)] = registres[convBin2Dec(pc->codeBinaire, 25, 5)] - registres[convBin2Dec(pc->codeBinaire, 20, 5)];
}

void instructionXOR(listeCommande *programCounter, int registres[]) {

	commande *pc;
	pc = *programCounter;

	unsigned int valeur = 0;
	int reste = -1;

	char registres1[32], registres2[32], registres3[32];

	valeur = registres[convBin2Dec(pc->codeBinaire, 25, 5)];

	for(int i=0; i<32; i++) {
		reste = valeur%2;
		if( reste == 0 ){
			registres1[i] = '0';
		}else {
			registres1[i] = '1';
			valeur = valeur-1;			
		}
		valeur = valeur/2;
	}

	valeur = registres[convBin2Dec(pc->codeBinaire, 20, 5)];

	for(int i=0; i<32; i++) {
		reste = valeur%2;
		if( reste == 0 ){
			registres2[i] = '0';
		}else {
			registres2[i] = '1';
			valeur = valeur-1;			
		}
		valeur = valeur/2;
	}

	for(int i=0; i<32; i++) {
		if((registres1[i] == '1' || registres2[i] == '1') && (registres1[i] != registres2[i])) {
			registres3[i] = '1';
		}else {
			registres3[i] = '0';
		}
	}

	printf("\n%d", convBin2Dec(registres3, 31, 32));
	registres[convBin2Dec(pc->codeBinaire, 15, 5)] = convBin2Dec(registres3, 31, 32);
}

void instructionADDI(listeCommande *programCounter, int registres[]) {

	commande *pc;
	pc = *programCounter;

	registres[convBin2Dec(pc->codeBinaire, 20, 5)] = registres[convBin2Dec(pc->codeBinaire, 25, 5)] + convBin2Dec(pc->codeBinaire, 15, 16);
}