.data

	var1: .word 0xC71F002A		#allouer une valeur hex
	result1: .space 4		#allouer 32 bits d'espace libre
	result2: .space 4		#pareil

.text

main:
		lw $t1, var1		#initialisations
		li $t2, 0xC001
		
		sll $t2, $t2, 16	#décalage à gauche de 16 bits de t2
		and $t2, $t1, $t2	#t2 = t1 & t2
		
		#rotr $t4, $t2, 16	#instruction pas implémentée dans le simu, on décale à droite de 16 bits mais on récupère ces bits à gauche
		li $t4, 0x0000C001	#<- remplacement en dur pour la simulation
		
		mult $t4, $t4		#multiplication t4 * t4
		mflo $t1		#on récupère LO (ici les 32 bits faibles du résultat de la multiplication)
		and $t2, $t2, $t1	#t2 = t2 & t1
		sw $t2, result1		#on écrit t2 en mémoire
		lui $t2, 0xAC42		#on force les 16 bits forts de t2 à 0xAC42 (donc t2 | 0xAC420000)
		sw $t2, result2		#on écrit le nouveau t2 en mémoire
	
exit:		li $v0, 10		#on sélectionne le syscall de sortie
		syscall			#on appelle le syscall (sortie)
