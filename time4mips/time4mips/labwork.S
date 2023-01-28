  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
  # Code below is written by N Nguyen and P Patranika
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
.global delay
delay:
  	move 	$s0,$a0
  	li 	$t0,4500
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
  	jr 	$ra
  	nop
  	
  # Time to string
.global time2string
time2string:
  	#Push values into stack
  	PUSH 	$s0
  	PUSH	$s1
  	PUSH	$ra
  	
  	move 	$s0,$a0
  	move 	$s1,$a1
  	
    	# First digit
  	andi 	$t0, $s1, 0xf000#ta forsta digit
	srl  	$a0, $t0, 12 	# shift 12 steg
	jal 	hexasc
	nop
	move 	$t0, $v0
	sb 	$t0, 0($s0)	#store it in s0's 0 position
	
	# Second digit
  	andi 	$t0, $s1, 0xf00	
	srl  	$a0, $t0, 8 	
	jal 	hexasc
	nop
	move 	$t0, $v0
	sb 	$t0, 1($s0)	
	
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
  	
  	li $t0, 0
	sb $t0, 5($s0)
	
	# POP
  	POP $ra
  	POP $s1
  	POP $s0
  	
  	jr $ra
  	nop
 
