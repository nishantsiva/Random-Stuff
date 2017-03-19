
A=[ 0.16 0.10;
    0.17 0.11;
    2.02 1.29]

SQD_A = A'*A;

B=[0.26;0.28;3.31]

SQD_B=A'*B;
x=SQD_A\SQD_B

%solving for slightly perturbed b vector
pb=[0.27;0.25;3.33]
CT=A'*pb;
y=SQD_A\CT

%reason for instability
cn=cond(A);
sprintf('%s = %d','Condition number is: ',cn)