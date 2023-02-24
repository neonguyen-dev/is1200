.text

	addi	$a0, $a0, 3	#parameter value to $a0
	beq	$a0, $0, stop
	add	$v0, $v0, $a0
	addi	$a1,$a1,1
loop1:
	beq	$a0, $a1, stop
	mul	$v0, $v0, $a1
	addi	$a1, $a1, 1
	beq	$0,$0,loop1
stop:
	beq	$0, $0, stop
