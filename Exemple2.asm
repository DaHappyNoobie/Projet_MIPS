
.data

	var1: .word 18

.text

main:
	lw $t1, var1		#initialisations
	lw $t5, var1
	li $t2, 0
	li $t4, 0
	
loop:	addi $t2, $t2, 1	#incrémente t2
	addi $t5, $t5, 2	#incrémente t5 de 2
	beq $t1, $t2, suite 	#sort de la boucle si t1 = t2
	j loop			#reboucle sur le label loop

suite:	sub $t5, $t5, $t2	#effectue t5 = t5 - t2
	sub $t5, $t5, $t2	#même chose
	bne $t5, $t1, exit	#evoie au label exit si t5 != t1
	li $t4, 1		#sinon met t4 à 1
	
exit:	li $v0, 10		#on sélectionne le syscall de sortie
	syscall			#on appelle le syscall (sortie)
