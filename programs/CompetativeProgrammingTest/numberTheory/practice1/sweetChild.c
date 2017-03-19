#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000

int Arr[801][400];

void init () {
	int i, j, carry, value;
	Arr[0][0] = 1;
	Arr[0][1] = 0;
	Arr[1][0] = 1;
	Arr[1][1] = 0;
	Arr[2][0] = 1;
	Arr[2][1] = 1;
	for (i = 3; i < 801; ++i)
	{
		carry = 0;
		for (j = 1; j <= Arr[i-1][0]; ++j)
		{
			value = (Arr[i-1][j] + ((Arr[i-2][0]>=j)?Arr[i-2][j]:0)) *(i-1) + carry;
			Arr[i][j] =  value % MOD;
			carry = value / MOD;
		}
		while (carry != 0) {
			Arr[i][j++] = carry % MOD;
			carry = carry / MOD;
		}
		Arr[i][0] = j-1;
	}
}

int main(int argc, char const *argv[])
{
	int N, i, j;
	init();
	scanf("%d", &N);
	while (N != -1) {
		printf("%d", Arr[N][Arr[N][0]]);
		for (i = Arr[N][0]-1; i >= 1; --i)
		{
			printf("%06d", Arr[N][i]);
		}
		printf("\n");
		scanf("%d", &N);
	}
	return 0;
}