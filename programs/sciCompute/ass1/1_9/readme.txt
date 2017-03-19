ASSIGNMENT 1 QUESTION 1.9 PAGE NO 46
====================================


Procedure To Run
================
	$ make
	$ ./exp1
	$ ./exp2
	$ ./exp3
	$ make clean

Static inputs : 1,-1,5,-5,10,-10,15,-15,20,-20

Codes will generate value for exponential function of given inputs using the infinite series expansion of e^x.

exp1: No optimization.
exp2: For negative x calculates e^x as 1/e^|x|.
exp3: Accumulates positive and negative terms seperately and combines them afterwards.   


Stopping Criterion
==================
	It is not possible to calculate factorial of a number greater than 20, as factorial of 21 is 51090942171709440000 which cannot be stored even in “long long” data type in c(maximum value that can be stored in long long is 18446744073709551615). Hence the program stops after evaluating 20th term in the infinite series expantion of e^x.


Observations
============
	1. It was found all the codes gives huge error in calculating e^x for x greater than 10.
	2. exp2 generates most accurate solution for negative values of x.
	3. exp3 gives more accurate values than exp1.
	
	
The codes generated the following outputs:
	
	exp1.c output

		1 
			Calculated e^1  	= 2.71828182845904523543 
			exp(1)  		= 2.71828182845904509080 
		-1 
			Calculated e^-1  	= 0.36787944117144232161 
			exp(-1)  		= 0.36787944117144233402 
		5 
			Calculated e^5  	= 148.41314706738181633527 
			exp(5)  		= 148.41315910257659993476 
		-5 
			Calculated e^-5  	= 0.00674554009771037627 
			exp(-5)  		= 0.00673794699908546700 
		10 
			Calculated e^10  	= 21991.48202566506314070693 
			exp(10)  		= 22026.46579480671789497137 
		-10 
			Calculated e^-10  	= 13.39686599569604120996 
			exp(-10)  		= 0.00004539992976248485 
		15 
			Calculated e^15  	= 2997784.02616944660280751123 
			exp(15)  		= 3269017.37247211067005991936 
		-15 
			Calculated e^-15  	= 57612.83325879868031904607 
			exp(-15)  		= 0.00000030590232050183 
		20 
			Calculated e^20  	= 271252262.88075552397640421987 
			exp(20)  		= 485165195.40979027748107910156 
		-20 
			Calculated e^-20  	= 21277210.34254429914653883316 
			exp(-20)  		= 0.00000000206115362244
			
	
	exp2.c output
	
		1 
			Calculated e^1  	= 2.71828182845904523543 
			exp(1)  		= 2.71828182845904509080 
		-1 
			Calculated e^-1  	= 0.36787944117144232158 
			exp(-1)  		= 0.36787944117144233402 
		5 
			Calculated e^5  	= 148.41314706738181633527 
			exp(5)  		= 148.41315910257659993476 
		-5 
			Calculated e^-5  	= 0.00673794754548250942 
			exp(-5)  		= 0.00673794699908546700 
		10 
			Calculated e^10  	= 21991.48202566506314070693 
			exp(10)  		= 22026.46579480671789497137 
		-10 
			Calculated e^-10  	= 0.00004547215139175042 
			exp(-10)  		= 0.00004539992976248485 
		15 
			Calculated e^15  	= 2997784.02616944660280751123 
			exp(15)  		= 3269017.37247211067005991936 
		-15 
			Calculated e^-15  	= 0.00000033357973465413 
			exp(-15)  		= 0.00000030590232050183 
		20 
			Calculated e^20  	= 271252262.88075552397640421987 
			exp(20)  		= 485165195.40979027748107910156 
		-20 
			Calculated e^-20  	= 0.00000000368660518950 
			exp(-20)  		= 0.00000000206115362244
			
	
	exp3.c output
		
		1
			Calculated e^1  	= 2.71828182845904523499
			exp(1)  		= 2.71828182845904509080
		-1
			Calculated e^-1  	= 0.36787944117144232112
			exp(-1)  		= 0.36787944117144233402
		5
			Calculated e^5  	= 148.41310786833832008336
			exp(5)  		= 148.41315910257659993476
		-5
			Calculated e^-5  	= 0.00670634105421412385
			exp(-5)  		= 0.00673794699908546700
		10
			Calculated e^10  	= 21950.37884943194149123258
			exp(10)  		= 22026.46579480671789497137
		-10
			Calculated e^-10  	= -27.70631023742560650192
			exp(-10)  		= 0.00004539992976248485
		15
			Calculated e^15  	= 2861105.41277260889910394326
			exp(15)  		= 3269017.37247211067005991936
		-15
			Calculated e^-15  	= -79065.78013803902319978079
			exp(-15)  		= 0.00000030590232050183
		20
			Calculated e^20  	= 228152458.75893375820305664092
			exp(20)  		= 485165195.40979027748107910156
		-20
			Calculated e^-20  	= -21822593.77927746664499863982
			exp(-20)  		= 0.00000000206115362244
