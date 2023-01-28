  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0, 17		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argu §ment register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
  hexasc:
  	slti	$t0,$a0,0xA	# Checks if $a0 is less than 0xA
  	beq	$t0,$zero,else 	# If $a0 is bigger than 0xA then jump to label biggerthan:
  	nop
  	li 	$v0,0x30 	# ASCII code for 0 is 0x30
  	add	$v0,$v0,$a0
  	j	done
  else:
      	#slti	$t0,$a0,0xF	# Checks if $a0 is less than 0xF
      	#beq	$t0,$zero,done	# If $a0 is bigger than 0xF then jump to label done:
  	#nop
	li 	$v0,0x37 	# ASCII code for A is 0x41 and 0x41-0xA = 0x37
  	add	$v0,$v0,$a0	
  	j	done
  done:
  	jr 	$ra		# return to address
  	
