A = [2 4 -2; 4 9 -3; -2 -1 7];
B = [2;8;10];
[L,U,P] = lu(A);
Y1 = L\(P*B);
display('Solution to first system of equations:')
X1 = U\Y1
C = [4;8;-6];
Y2 = L\(P*C);
display('Solution to Second system of equations:')
X2 = U\Y2

row = 1;
col = 2;
val = 2;

u = zeros(3,1);
v = zeros(1,3);
u(row,1) = val;
v(1,col) = 1;

z = A\u;
display('Solution using Sherman Morrison Formula')
X1+((v*X1)/(1-v*z))*z