#include <stdio.h>

int getCoinInputs(long long int *coins){
	int count, i;
	scanf("%d", &count);
	coins[0] = 0;
	for (i = 1; i <= count; ++i)
	{
		scanf("%lld", &coins[i]);
	}
	return count;
}

void output(long long int result, int nCase){
	printf("Case %d: %lld\n", nCase, result);
}

long long int findGreater(long long int a, long long b){
	if (a > b)
	{
		return a;
	}
	return b;
}

long long int getMaxCoins(long long int *coins, int nMonsters){
	long long int nextSum, prevSum, curSum;
	int i;
	curSum = 0;
	prevSum = 0;
	for (i = 1; i <= nMonsters; i++){
		nextSum = findGreater(curSum, prevSum + coins[i]);
		prevSum = curSum;
		curSum = nextSum;
	}
	return curSum;
}

int main(int argc, char const *argv[])
{
	int T, tCase, nMonsters;
	long long int coins[10005]; 
	scanf("%d", &T);
	for (tCase = 1; tCase <= T; ++tCase)
	{
		nMonsters = getCoinInputs(coins);
		output(getMaxCoins(coins, nMonsters), tCase);
	}
	return 0;
}