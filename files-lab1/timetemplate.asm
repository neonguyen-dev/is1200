  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
  hexasc:
  	slti	$t0,$a0,0xA	# Checks if $a0 is less than 0xF
  	beq	$t0,$zero,biggerthan # If $a0 is bigger than 0xA then jump to label biggerthan:
  	nop
  	li 	$v0,0x30 	# ASCII code for 0 is 0x30
  	add	$v0,$v0,$a0
  	j	done
  	nop
  biggerthan:
    	#slti	$t0,$a0,0xF	# Checks if $a0 is less than 0xF
      	#beq	$t0,$zero,done	# If $a0 is bigger than 0xF then jump to label done:
  	#nop
	li 	$v0,0x37 	# ASCII code for A is 0x41 and 0x41-0xA = 0x37
  	add	$v0,$v0,$a0
  	j	done
  	nop
  done:
  	jr 	$ra		# return to address
  	nop
  	
  # Delay function
  delay:
  	PUSH	$s0
  	PUSH	$s1
  
  	move 	$s0,$a0
  	li 	$t0,4771
  	nop
  loop:
    	move	$s1,$zero
  	slt	$t1,$zero,$s0
  	beq	$t1,$zero, end
  	addi	$s0,$s0,-1
  	j 	forloop
  	nop
  forloop:
  	slt 	$t2, $s1, $t0
	beq	$t2,$zero, loop
	addi	$s1,$s1,1
	j forloop
	nop
  end:
  	POP	$s1
 	POP	$s0
 	 	 	
  	jr 	$ra
  	nop
  	
  # Time to string
  time2string:
  	#Push values into stack
  	PUSH 	$s0
  	PUSH	$s1
  	PUSH	$ra
  	
  	move 	$s0,$a0
  	move 	$s1,$a1
  	
    	# First digit
  	andi 	$t0,$s1,0xf000	#ta forsta digit
	srl  	$a0,$t0,12 	# shift 12 steg
	jal 	hexasc
	nop
	move 	$t0,$v0
	sb 	$t0,0($s0)	#store it in s0's 0 position
	
	# Second digit
  	andi 	$t0,$s1,0xf00	
	srl  	$a0,$t0,8 	
	jal 	hexasc
	nop
	move 	$t0,$v0
	sb 	$t0,1($s0)
	
	li $t0, 0x3A 		#ASCII code for ':'
	sb $t0, 2($s0)
	
	# Thrird digit
  	andi 	$t0, $s1, 0xf0	
	srl  	$a0, $t0, 4 	
	jal 	hexasc
	nop
	move 	$t0, $v0
	sb 	$t0, 3($s0)	
	
	# Fourth digit
  	andi 	$t0, $s1, 0xf
  	move  	$a0, $t0 	
	jal 	hexasc
	nop
	move 	$t0, $v0
	sb 	$t0, 4($s0)
	  	
	li 	$t0, 0x0	#to specify that the next in string is null
	sb 	$t0, 5($s0)
  	
  	andi	$t0,$s1,0xff
  	beq	$t0,$zero,ding
  	nop
  	j 	quit
  	nop
  	
  ding:
  	# li	$t0,0x44
  	# sb	$t0,0($s0)
  	
	# li	$t0,0x49
  	# sb	$t0,1($s0)
  	
  	# li	$t0,0x4E
  	# sb	$t0,2($s0)  
  	
  	# li	$t0,0x47
  	# sb	$t0,3($s0)
  	
  	li	$t0, 0x58
  	sb	$t0, 5($s0)
  	
  	li	$t0,0x0
  	sb	$t0,6($s0)
  quit:

	# POP
  	POP $ra
  	POP $s1
  	POP $s0
  	
  	jr $ra
  	nop
  	
