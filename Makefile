

CC = gcc
OBJECTS = main.o fichier.o simulation.o encodage.o affichageConsole.o processus.o
FLAGS = -Wall -ansi -pedantic -std=c99
OUTPUT = programme
F_ECRITURE = fichierSortieBinaire.txt fichierSortieHexa.txt

all: $(OBJECTS)
	$(CC) -o $(OUTPUT) $(OBJECTS)
	
fichier.o: fichier.c fichier.h
	$(CC) -c fichier.c $(FLAGS)

encodage.o: encodage.c encodage.h
	$(CC) -c encodage.c $(FLAGS)

affichageConsole.o: affichageConsole.c affichageConsole.h
	$(CC) -c affichageConsole.c $(FLAGS)

simulation.o: simulation.c simulation.h
	$(CC) -c simulation.c $(FLAGS)

processus.o: processus.c processus.h
	$(CC) -c processus.c $(FLAGS)

main.o: main.c
	$(CC) -c main.c $(FLAGS)