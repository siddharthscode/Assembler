# whether number is even or odd
main:
	addi $s0, $zero, 125	# $s0 = 125
	addi $t0, $zero, 1
	and $t0, $s0, $t0		# $t0 = $s0 & 1
	beq $t0, $zero, 0		# goto exit label (0 is offset in this case)
	# print number is odd

exit: 
	# print number is even