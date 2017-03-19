#include <stdio.h>
#include <stdlib.h>

long long int cat[30];
long long int supCat[30];

long long int findSup (int n) {
	if (supCat[n] != -1)
	{
		return supCat[n];
	}
	if (n == 0 || n == 1 || n == 2)
	{
		supCat[n] = 1;
	}
	else {
		supCat[n] = (3*(n*2 - 3)*findSup(n-1) - (n - 3)*findSup(n - 2))/n;
	}
	return supCat[n];
}

long long int findCat (int n) {
	if (cat[n] != -1)
	{
		return cat[n];
	}
	if (n == 0 || n == 1)
	{
		cat[n] = 1;
	}
	else if (n == 2)
	{
		cat[n] = 2;
	}
	else {
		cat[n] = findCat(n - 1) * (2*( n*2 - 1 )) / (n+1);
	}
	return cat[n];
}

long long int find(int cur) {
	if (supCat[cur] == -1)
	{
		return findSup(cur) - findCat(cur-1);
	}
	return supCat[cur] - cat[cur-1];
}

int main(int argc, char const *argv[])
{
	int N, i;
	for (i = 0; i < 30; ++i)
	{
		cat[i] = -1;
		supCat[i] = -1;
	}
	while (scanf("%d", &N) == 1) {
		printf("%lld\n", find(N));
	}
	return 0;
}