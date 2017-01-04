#include "encodage.h"

void adresseRegistre(int indice) {

	int adresse;

	switch(commandeString[indice]) {
		case 'a' : /* registres arguments de sous-routine */
			if(commandeString[indice+1] == 't') {
				adresse = 1;
			}else {
				adresse = commandeString[indice+1] - '0';
				adresse = adresse + 4;
			}
		break;
		case 'f' : /* Frame pointer */
			adresse = 30;
		break;
		case 'g' : /* Global pointer */
			adresse = 28;
		break;
		case 'k' : /* Kernel */
			adresse = commandeString[indice+1] - '0';
			adresse = adresse + 26;
		break;
		case 'r' : /* Return address */
			adresse = 31;
		break;
		case 's' : /* Registre temporaires, sous-routine */
			adresse = commandeString[indice+1] - '0';
			adresse = adresse + 16;
		break;
		case 't' : /* Registre temporaires */
			if(commandeString[indice+1] < 56) {
				adresse = commandeString[indice+1] - '0';
				adresse = adresse + 8;
			}else {
				adresse = commandeString[indice+1] - '0';
				adresse = adresse + 16;
			}
		break;
		case 'v' : /* Valeur retournees, sous-routine */
			adresse = commandeString[indice+1] - '0';
			adresse = adresse + 2;
		break;
		case 'z' : /* Registre toujours nul */
			adresse = 0;
		break;
		default :
			printf("\nRegistre inconnu");
		break;
	}

	adresseRegistreBinaire(adresse);
}

void adresseRegistreBinaire(int registre) {
	int nbr;

	for(int i=4; i>-1; i--) {
		nbr = registre >> i;
		if( nbr & 1 ){
			registreBinaire[i] = '1';
		}else {
			registreBinaire[i] = '0';			
		}
	}
}

int decodageInstruction() {
/* Cette procedure va nous permettre de déterminer le type d'instruction (R,I,J) */
/* return : */
/* 1 : instruction reconnue */
/* 2 : etiquette detecte avec instruction */
/* 3 : etiquette detecte sans instruction */
/* 4 : pas d'instruction */

	int i = 0;

	if(verificationEtiquette()) { /* Cas où il y a une étiquette */
		
		printf("\nDetection d'une etiquette");

		/* encodage */
		encodageLabels();

		/* on detecte la presence d'une instruction sur la même ligne */
		while((commandeString[i] < 36 || commandeString[i] > 122) && i<30 ) {
			i++;
		}

		/* si il y a une instruction */
		if(i != 30){
			return 2;
		}

		return 3;

	}else { /* Cas où il n'y a pas d'étiquette */
	switch(commandeString[i]) {
			case 'a' : /* ADD, ADDI ou AND */

				if(commandeString[i+3] == 'i') { /* ADDI */
					encodageInstructionI("001000","111");
				} else { /* ADD ou AND */
					if(commandeString[i+1] == 'd') { /* ADD */
						encodageInstructionR("000000","100000","1110");				
					} else { /* AND */
						encodageInstructionR("000000","100100","1110");					
					}
				}

			break;
			case 'b' : /* BEQ, BNE, BGTZ ou BLEZ */

				switch(commandeString[i+1]) {
					case 'e' : /* BEQ */
						encodageInstructionI("000100","111");
					break;
					case 'n' : /* BNE */
						encodageInstructionI("000100","111");
					break;
					case 'g' : /* BGTZ */
						encodageInstructionI("000111","101");
					break;
					case 'l' : /* BLEZ */
						encodageInstructionI("000110","101");
					break;
				}

			break;
			case 'd' : /* DIV */

				encodageInstructionR("000000","011010","1100");

			break;
			case 'j' : /* J, JAL ou JR */

				if(commandeString[i+1] == 'r') { /* JR */
					encodageInstructionR("000000","001000","1000");
				} else { /* JAL ou J */
					if(commandeString[i+1] == 'a') { /* JAL */
						encodageInstructionJ("000011");				
					} else { /* J */
						encodageInstructionJ("000010");					
					}
				}

			break;
			case 'l' : /* LUI ou LW */
				if(commandeString[i+1] == 'u') { /* LUI */
					encodageInstructionI("001111","011");				
				} else { /* LW */
					encodageInstructionI("100011","111");					
				}

			break;
			case 'm' : /* MULT, MFHIS ou MFLO  */
				if(commandeString[i+1] == 'u') { /* MULT */
					encodageInstructionR("000000","011000","1100");				
				}else { /*  MFHIS ou MFLO */
					if(commandeString[i+2] == 'h') { /* MFHIS */
						encodageInstructionR("000000","010000","0010");				
					}else { /* MFLO */
						encodageInstructionR("000000","010010","0010");
					}				
				}

			break;
			case 'n' : /* NOP */

				encodageInstructionR("000000","000000","0000");

			break;
			case 'o' : /* OR */

				encodageInstructionR("000000","100101","1110");

			break;
			case 'r' : /* ROTR */

				encodageInstructionR("000000","000010","2111");

			break;
			case 's' : /* SUB, SLL, SRL, SLT ou SW */

				if(commandeString[i+1] == 'w') { /* SW */
					encodageInstructionI("101011","211");
				} else if(commandeString[i+1] == 'u') { /* SUB */
					encodageInstructionR("000000","100010","1110");				
				}else if(commandeString[i+1] == 'r'){ /*  SRL */
					encodageInstructionR("000000","000010","1110");					
				}else if(commandeString[i+1] == 'y') { /*  SYSCALL */
					encodageInstructionR("000000","001100","0000");	
				}else { /* SLL ou SLT */
					if(commandeString[i+2] == 'l') { /* SLL */
						encodageInstructionR("000000","000000","3111");				
					}else { /* SLT */
						encodageInstructionR("000000","101010","1110");
					}				
				}

			break;
			case 'x' : /* XOR */

				encodageInstructionR("000000","100110","1110");

			break;
			default :

				printf("\nPas d'instruction reconnue");
				return 4;

			break;
		}	

		return 1;	
	}
	
}

int verificationEtiquette() {
	
	for(int i=0; i<30; i++) {
		if(commandeString[i] == ':'){
			return 1;
		}
	}

	return 0;
}

void encodageInstructionR(char opcode[], char function[],  char operandes[]) {
	/* Opcode est l'opcode */
	/* function est la fonction */
	/* operande (4 char) represante rs, rt, rd et sa : */
	/* 1 : si plein */
	/* 0 : si vide */
	/* 2 : cas pour le ROTR (R) */
	/* 3 : cas pour le SLL (R) */
	/* cela permet de différencier les deux instructions */

	int indice = 30;

	/* Opcode */
	for(int i=31; i>25; i--) {
		commandeBinaire[i] = opcode[31-i];
	}

	/* Sa */
	if (operandes[3] == '1') {
		encodageInstructionValeur( &indice, 10, 5, 1);
	} else {
		encodageInstructionValeur( &indice, 10, 5, 0);
	}	

	/* Rt */
	if (operandes[1] == '1') {
		encodageInstructionRegistre(&indice,20,1);
	} else {
		encodageInstructionRegistre(&indice,20,0);
	}

	/* Rs */
	if (operandes[0] == '1') {
		encodageInstructionRegistre(&indice,25,1);
	}else if(operandes[0] == '2') {
		for(int i=25; i>21; i--) {
			commandeBinaire[i] = '0';
		}
		commandeBinaire[21] = '1';
	} else {
		encodageInstructionRegistre(&indice,25,0);
	}

	/* Rd */
	if (operandes[2] == '1') {
		encodageInstructionRegistre(&indice,15,1);
	} else {
		encodageInstructionRegistre(&indice,15,0);
	}		

	/* Function */
	for(int i=5; i>-1; i--) {
		commandeBinaire[i] = function[5-i];
	}	
}

void encodageInstructionI(char opcode[],  char operandes[]) {
	/* Opcode est l'opcode */
	/* operande (4 char) represante rs, rt et immediate : */
	/* 1 : si plein */
	/* 0 : si vide */
	/* 2 : cas du SW */

	int indice = 30;

	for(int i=31; i>25; i--) {
		commandeBinaire[i] = opcode[31-i];
	}

	/* immediate */
	if (operandes[2] == '1') {
		encodageInstructionValeur( &indice, 15, 16, 1);
	} else {
		encodageInstructionValeur( &indice, 15, 16, 0);
	}	

	/* Rs */
	if (operandes[0] == '1') {
		encodageInstructionRegistre(&indice,25,1);
	} else {
		encodageInstructionRegistre(&indice,25,0);
	}

	/* Rt */
	if (operandes[1] == '1') {
		encodageInstructionRegistre(&indice,20,1);
	}else {
		encodageInstructionRegistre(&indice,20,0);
	}
}

void encodageInstructionJ(char opcode[]) {

	int indice = 30;

	/* Opcode */
	for(int i=31; i>25; i--) {
		commandeBinaire[i] = opcode[31-i];
	}

	/* Target */
	encodageTarget(&indice);
}

void encodageLabels() {
/* cette procédure va récuperer le nom du nouveau label */
	int i, decalage;
	i=0;

	while(commandeString[i] == ' ') {
		i++;
	}

	while(commandeString[i] != ':') {
		labelNom[i] = commandeString[i];
		i++;
	}

	labelNom[i] = '\0';

	while(commandeString[i] == ':' || commandeString[i] == ' ') {
		i++;
	}

	decalage = i;
	do{
		commandeString[i-decalage] = commandeString[i];
		i++;
	}while(i<29);
}

void encodageInstructionValeur(int *indice1, int indice2, int taille, int ordre) {
	if(ordre == 1) {
		if(taille == 5) {
			*indice1 = chercherValeur(*indice1);
			encodageValeur(*indice1+1);
			for(int i=indice2; i>indice2-taille; i--) {
				commandeBinaire[i] = valeurBinaire[i-(indice2-4)];
			}			
		}else if(taille == 16) {
			*indice1 = chercherValeur(*indice1);
			encodageImmediat(*indice1+1);
			for(int i=indice2; i>indice2-taille; i--) {
				commandeBinaire[i] = immediatBinaire[i-(indice2-15)];
			}				
		}else {
			printf("\nErreur de la fonction <encodageInstructionValeur> : taille");
		}

	}else if(ordre == 0) {

		for(int i=10; i>5; i--) {
			commandeBinaire[i] = '0';
		}
	}else {

		printf("\nErreur de la fonction <encodageInstructionValeur> : ordre");
	}
}

void encodageInstructionRegistre(int *indice1,int indice2, int ordre) {

	if(ordre == 1) {

		*indice1 = chercherRegistre(*indice1);
		adresseRegistre(*indice1+1);
		for(int i=indice2; i>indice2-5; i--) {
			commandeBinaire[i] = registreBinaire[i-(indice2-4)];
		}
	}else if(ordre == 0) {

		for(int i=indice2; i>indice2-5; i--) {
			commandeBinaire[i] = '0';
		}
	}else {

		printf("\nErreur de la fonction <encodageInstructionRegistre>");
	}		
}

void encodageValeur(int indice) {

	int i = 0;
	unsigned int valeur = 0;
	int nbr;

	do {
		valeur = valeur * 10;
		valeur += commandeString[i+indice] - '0';
		i++;
	}while(commandeString[indice+i] >= 48 && commandeString[indice+i] <= 57);

	for(int i=4; i>-1; i--) {
		nbr = valeur >> i;
		if( nbr & 1 ){
			valeurBinaire[i] = '1';
		}else {
			valeurBinaire[i] = '0';			
		}
	}	
}

void encodageImmediat(int indice) {

	int i = 0;
	unsigned int valeur = 0;
	int nbr;

	do {
		valeur = valeur * 10;
		valeur += commandeString[i+indice] - '0';
		i++;
	}while(commandeString[indice+i] >= 48 && commandeString[indice+i] <= 57);

	for(int i=15; i>-1; i--) {
		nbr = valeur >> i;
		if( nbr & 1 ){
			immediatBinaire[i] = '1';
		}else {
			immediatBinaire[i] = '0';			
		}
	}	
}

void encodageTarget(int *indice) {

	/* Cette procedure ne marche que pour un label par defaut : */
	/* 0000 0000 0100 0000 0000 0000 0100 1000 */

	/*for(int i=25; i>1; i--) {
		commandeBinaire[i-2] = labelAdresse[i]; /* decalage de deux bits */
	/*}*/
	commandeBinaire[25] = '0';
	commandeBinaire[24] = '0';
}

int chercherRegistre(int indice) {
	
	int i = indice;

	do {
		i--;
	}while(commandeString[i] != '$');

	return i;
}

int chercherValeur(int indice) {
	
	int i = indice;
	char trouve = '0';

	do {
		i--;
		if(commandeString[i] >= 48 && commandeString[i] <= 57) {
			trouve = '1';
		}else if(trouve == '1') {
			trouve = '2';
		}
	}while(trouve != '2');
	return i;
}

void convertCommande() {

	unsigned int buff=0;
	char k=0;
	int y=0;
	char symboles[] = "0123456789ABCDEF";
	char tampon;

	for (int i=0;i<32;i++) {	    
		
		buff = buff | ((commandeBinaire[4*y+(k)]-48)<<k);
		k++;
		if (k>=4) {
			commandeHexa[y] = buff;
			k=0;
			buff=0;
			y++;
		}
	}
	for (int h=0;h<8;h++) {

		commandeHexa[h]=symboles[commandeHexa[h]];
	}
	/*for(int i=0; i<4; i++) {
		tampon = commandeHexa[i];
		commandeHexa[i] = commandeHexa[7-i];
		commandeHexa[7-i] = tampon;
	}*/
}