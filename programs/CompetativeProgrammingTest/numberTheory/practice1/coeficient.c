#include <stdio.h>
#include <stdlib.h>

int fact[13];

int factorial (int N) {
	if (fact[N] != -1)
	{
		return fact[N];
	}
	if (N == 0)
	{
		fact[N] = 1;
		return 1;
	}
	fact[N] = N * factorial(N-1);
	return fact[N];
}

int main(int argc, char const *argv[])
{
	int N, K, i, value, n;
	for (i = 0; i < 13; ++i)
	{
		fact[i] = -1;
	}
	while (scanf("%d %d", &N, &K) == 2) {
		value = factorial(N);
		for (i = 0; i < K; ++i)
		{
			scanf("%d", &n);
			value /= factorial(n);
		}
		printf("%d\n", value);
	}
	return 0;
}