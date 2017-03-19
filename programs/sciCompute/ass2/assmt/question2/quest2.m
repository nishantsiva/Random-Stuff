A = [0.16, 0.10; 0.17, 0.11; 2.02, 1.29]

SQD_A = A'*A;

B = [0.26; 0.28; 3.31]
SQD_B = A'*B;

X1 = SQD_A\SQD_B

B_pert = [0.27; 0.25; 3.33]
SQD_B_pert = A'*B_pert;

X2 = SQD_A\SQD_B_pert

display('Condition Number Of A:')
cond(A)