#include <stdio.h>

int Arr[6][1000000];
int count = 0;

int ack(int m, int n) {
	int ans; count++;
	if (Arr[m][n] != -1)
	{
		return Arr[m][n];
	}
	if (m == 0)
	{
		ans = n+1;
	}
	else if (n == 0)
	{
		ans = ack(m-1, 1);
	}
	else
	{
		ans = ack(m-1, ack(m, n-1));
	}
	Arr[m][n] = ans;
	return ans;
}

int main(int argc, char const *argv[])
{
	int i, j;
	for (i = 0; i < 6; ++i)
	{
		for (j = 0; j < 1000000; ++j)
		{
			Arr[i][j] = -1;
		}
	}
	for (i = 0; i < 5; ++i)
	{
		for (j = 0; j < 5; ++j)
		{
			printf("ackermann(%d, %d) : %d\n", i, j, ack(i, j));
		}
	}
	return 0;
}