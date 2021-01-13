# fibonacci series upto 15 terms
# we use offset value in conditional branches
# we use for loop upto 15 and caculate fibonacci terms upto 15 terms
main:
	addi $a0, $zero, 1		# a0 = 1
	addi $s0, $zero, 1		# s0 = 1 acts like counter

loop:	
	slti $t0, $s0, 16
	beq $t0, $zero, 4		# 4 is offset to go to label exit
	jal fibo
	addi $a0, $a0, 1
	addi $s0, $s0, 1
	j loop

exit:

fibo:
	addi $sp, $sp, -8
	sw $a0, 4 ($sp)
	sw $ra, 0 ($sp)
	slti $t0, $a0, 3
	beq $t0, $zero, 3	# 3 is offset for goto label l1
	addi $v0, $zero, 1
	addi $sp, $sp, 8
	jr $ra

l1:
	addi $a0, $a0, -1	# a0 = a0 - 1
	jal fibo 			# procedure call
	addi $sp, $sp, -4	# allocate for 1 item
	sw $v0, 0 ($sp)		# stores value 1 in it
	addi $a0, $a0, -1	# a0 = a0 - 1
	jal fibo 			# procedure call
	lw $t0, 0 ($sp)		# load value 1 from stack
	addi $sp, $sp, 4		# deltes its space
	lw $a0, 4 ($sp)		# load initial argument
	lw $ra, 0 ($sp)		# load return address
	addi $sp, $sp, 8		# deletes stack space
	add $v0, $t0, $v0	# v0 = t0 + v0
	jr $ra 				# function return