.text
# Kod skriven i C# av Neo Nguyen
#
#            int argument = 8;
#            int factorialValue = 1;
#
#
#            for (int i = 0; i < argument; i++)
#            {
#		 int temp = factorialValue;
#                for (int j = 0; j < temp; j++)
#                {
#                    for (int k = 0; k < i; k++)
#                    {
#                        factorialValue++;
#                    }
#                }
#            }�
#	     foreach i in argument{
#	     factorialvalue = factorialvalue * i;
#	     }

	#a0 = argument
	#a1 = i
	#a2 = j
	#a3 = k
	#v0 = factorialvalue
	#v1 = temp
	
	addi	$a0, $a0, 5	#parameter value to $a0
	addi	$v1, $v1, 0
	beq	$a0, $0, stop
	addi	$v0, $v0, 1
loop1:
	beq	$a0, $a1, stop
	add	$v1, $0, $v0
	addi	$a1, $a1, 1
	add	$a2, $0, $0
loop2:
	beq	$a2, $v1, loop1
	addi	$a2, $a2, 1
	addi	$a3, $0, 1
loop3:
	beq	$a3,$a1,loop2
	add	$v0, $v0, 1
	add	$a3, $a3, 1
	beq	$0, $0, loop3
stop:
	beq	$0, $0, stop
