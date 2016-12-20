.data

	var1: .word 42		#var1 est un word en mémoire de valeur 42
	var2: .word 4		#var2 est un word en mémoire de valeur 4
	result: .space 4	#result est un 4 octets vides en mémoire

.text

main:
	lw $t0, var1		#on charge var1 dans t0
	lw $t1, var2		#on charge var2 dans t1
	li $t3, 5		#on charge 5 dans t3
	div $t0, $t1		#on divise t0 par t1
	mfhi $t4		#on charge le reste de la division dans t4
	slt $t0, $t4, $t3	#on met t0 à 1 si t4 < t3
	sll $t0, $t0, 2		#on décale de 2 bits à gauche la valeur de t0
	sw $t0, result		#on stocke t0 dans la mémoire à result

	li $v0, 10		#on sélectionne le syscall de sortie
	syscall			#on appelle le syscall (sortie)
