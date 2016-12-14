        .data
msg1:   
		.asciiz "Baptiste le Pompier" # on enregistre la chaine de caractère dans la variable msg1

        .text

        .globl main
        # Main du programme
main:   
		# Affichage d'un mots
		li		$v0, 4
		la		$a0, msg1
		syscall

		li		$v0, 5
		addi 	$t1, $v0, 1
		add 	$t1, $t1, $v0
		move	$t2, $t1
		sub		$t1, $t1, $t1

loop:
		addi 	$t1, $t1, 1
		beq		$t1, $t2, next
		j		loop
		# FIN du petit programme de test
next:	
		li		$v0, 5
		syscall
		move 	$t2, $v0
		# Fin du programme
		li		$v0, 10
		syscall			