A = [  9 4.5   3;
	 -56 -28 -18;
	  60  30  19];

fprintf('Eigen value of given matrix:');
E = eigs(A);
E

Amod = A;

Amod(3,3) = 18.95;
fprintf('Eigen value after changing A[3][3] to 18.95:');
E1 = eigs(Amod);
E1
fprintf('Relative change in magnitude of eigen value:');
for i = 1:3
	R(i) = (E1(i) - E(i));
	if E(i) ~= 0
		R(i) = R(i)/E(i);
	end
end
R 

Amod(3,3) = 19.05;
fprintf('Eigen value after changing A[3][3] to 19.05:');
E1 = eigs(Amod);
E1
fprintf('Relative change in magnitude of eigen value:')
for i = 1:3
	R(i) = (E1(i) - E(i));
	if E(i) ~= 0
		R(i) = R(i)/E(i);
	end
end
R

fprintf('Condition number of eigen values of A:');
condeig(A)

