# factorial of 5 and calculation of nCr (just instruction) n = 5 and r = 2
main:
	addi $a0, $zero, 5	# $a0 = 5
	jal fact 			# call fact(5)
	addi $sp, $sp, -1
	sw $v0, 0 ($sp)		# stores fact(5) value
	addi $a1, $zero, 2	# $a1 = 2 for value r
	jal combi			# call combi(5, 2)
	j exit				# exit program
	
fact:
	addi $sp, $sp, -8	# allocate for 3 items
	sw $a0, 0 ($sp)		# store n
	sw $ra, 4 ($sp)		# store return address
	addi $t0, $zero, 1	# $t0 = 1
	slt $t1, $a0, $t0	# checking condition
	bne $t1, $t0, 6		# if a0 >= 1 then goto branch l1
	addi $v0, $zero, 1	# return value 1
	addi $t1, $zero, 1	# $t1 = 1
	sll $t1, $t1, 3		# $t1 = 8
	add $sp, $sp, $t1	# delete memory in stack
	srl $t1, $t1, 4		# $t1 = 0
	jr $ra				# return address

l1:
	addi $a0, $a0, -1	# now put $a0 = n - 1
	jal fact 			# call fact(n-1)
	lw $t0, 0 ($sp) 	# $t0 = n
	lw $ra, 4 ($sp) 	# recover return address of fact(n)
	addi $sp, $sp, 8	# delete memory in stack
	mul $v0, $v0, $t0	# $v0 = fact(n-1) * n
	jr $ra				# return address

combi:
	addi $sp, $sp, -12	# allocate for 4 items
	sw $ra, 0 ($sp)		# store return address
	jal fact 			# call fact(n)
	sw $v0, 4 ($sp) 	# store n! value
	sub $a0, $a0, $a1	# $a0 = n - r 
	jal fact 			# call fact(n-r)
	sw $v0, 8 ($sp) 	# store (n-r)!
	add $a0, $zero, $a1 # $a0 = r
	jal fact 			# call fact(r)
	lw $t0, 8 ($sp) 	# $t0 = (n-r)!
	mult $t0, $v0 		# multiplication
	mflo $t0			# $t0 = (n-r)! * r!
	lw $t1, 4 ($sp) 	# $t1 = n!
	div $t1, $t0 		# division
	mflo $v0			# $v0 = n! / ((n-r)! * r!)
	lw $ra, 0 ($sp) 	# load current address
	addi $sp, $sp, 12 	# deletes stack space
	jr $ra 				# return address

exit:
