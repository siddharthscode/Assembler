# swap a[20] and a[10] and assume base address of array is at $s0
main:
	lw $t0, 80 ($s0)
	lw $t1, 40 ($s0)
	sw $t1, 80 ($s0)
	sw $t0, 40 ($s0)