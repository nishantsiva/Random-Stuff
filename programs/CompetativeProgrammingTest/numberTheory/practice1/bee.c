#include <stdio.h>
#include <stdlib.h>

long int total[60];
long int female[60];

long int find (int n) {
	 if (female[n] != -1)
	 {
	 	return female[n];
	 }
	 if (n == 0)
	 {
	 	female[n] = 1;
	 	total[n] = 1;
	 }
	 else if (n == 1) {
	 	female[n] = 1;
	 	total[n] = 2;
	 }
	 else {
	 	female[n] = find(n-1) + find(n-2);
	 	total[n] = total[n-1] + female[n];
	 }
	 return female[n];
}


int main(int argc, char const *argv[])
{
	int N, i;
	for (i = 0; i < 60; ++i)
	{
		total[i] = -1;
		female[i] = -1;
	}
	scanf("%d", &N);
	while (N != -1) {
		find(N);
		printf("%ld %ld\n", total[N] - female[N], total[N]);
		scanf("%d", &N);
	}
	return 0;
}