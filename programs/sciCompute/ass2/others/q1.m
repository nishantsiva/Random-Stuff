A=[ 1 0 0 0;
    0 1 0 0;
    0 0 1 0;
    0 0 0 1;
    1 -1 0 0;
    1 0 -1 0;
    1 0 0 -1;
    0 1 -1 0;
    0 1 0 -1;
    0 0 1 -1];

B=[2.95;1.74;-1.45;1.32;1.23;4.45;1.61;3.21;0.45;-2.75];

SQD_A = A'*A;
SQD_B =A'*B;
x=SQD_A\SQD_B