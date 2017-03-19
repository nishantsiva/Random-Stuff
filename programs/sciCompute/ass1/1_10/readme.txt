ASSIGNMENT 1 QUESTION 1.10 PAGE NO 46
=====================================


Procedure To Run
================
	$ make
	$ ./quad
	$ make clean
	

Features implemented
====================

	1. The code finds real and imaginary roots of quadriatic equation using coeficients as input.
	2. Avoids cancelation error by using alternate formula for finding the second root.
	3. Guards from underflow and overflow errors.
	4. Handles special cases like a=0 or b=0 or both.
	

Observations
============
	1. The code runs perfectly for most of the cases.
		
		a = 0 	b = 1 	c = 0
		Output : 0.000000
		
		a = 0 	b = 1 	c = 0
		Output : -1.000000
		
		a = 1 	b = -1e+5	c = 1
		Output : 0.000010 99999.966146
		
		a = 1 	b =- 4 	c = 3.999999
		Output : 1.999000 2.001000
		
		a = 6 	b = 5 	c = -4
		Output : -1.333333 0.500000
		
		a = 6e+154	b = 5e+154 c = -4e+154
		Output : -1.333333 0.500000
		
	2. It fails when coeficients are having values near to underflow and overflow values together. For example:
		
		a = e-155 	b = -e+155 	c = e+155 
		Output : -0.000000 -inf
