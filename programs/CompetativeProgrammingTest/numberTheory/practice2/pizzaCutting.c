#include <stdio.h>
#include <stdlib.h>

#define MAX 210000001

int main(int argc, char const *argv[])
{
	long long int N;
	scanf("%lld", &N);
	while (N >= 0) {
		printf("%lld\n", (N*(N+1)/2)+1);
		scanf("%lld", &N);
	}
	return 0;
}