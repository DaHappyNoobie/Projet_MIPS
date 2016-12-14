.data

	var1: .word 0xC71F002A
	result1: .space 4
	result2: .space 4

.text

main:
		lw $t1, var1		#initialisations
		li $t2, 0xC001
		
		sll $t2, $t2, 16
		and $t2, $t1, $t2
		
		#rotr $t4, $t2, 31	#instruction pas implémentée dans le simu
		li $t4, 0x8003		#<- remplacement en dur pour la simulation
		
		mult $t4, $t4
		mflo $t1
		and $t2, $t2, $t1
		sw $t2, result1
		lui $t2, 0xAC42
		sw $t2, result2
	
exit:	li $v0, 10		#on sélectionne le syscall de sortie
		syscall			#on appelle le syscall (sortie)