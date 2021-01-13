# or nor operations on two numbers

main:
	addi $s0, $zero, 120	# $s0 = 120
	addi $s1, $zero, 20		# $s1 = 20
	or $t0, $s1, $s0		# $t0 = 20 | 120
	nor $t1, $s1, $s0		# $t1 = ~(20 | 120)
	
