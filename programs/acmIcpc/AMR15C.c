#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int T, N, K, max, i, j, temp;
	int check[100005];
	int ans[100005];
	scanf("%d", &T);
	while(T--){
		scanf("%d %d", &N, &K);
		if (K>(N/2))
		{
			printf("-1\n");
			continue;
		}
		for (i = 1; i <= N; ++i)
		{
			check[i] = 0;
		}
		for (i = 1; i <= K; ++i)
		{
			ans[i] = i+K;
			check[i+K] = 1;			
		}
		max = N;
		for (i = N; i > K ; --i)
		{
			temp = max;
			if (i+K > max)
			{
				temp = i - K;
			}
			for (j = temp; j >= 1; j--)
			{
				if (check[j] == 0)
				{
					ans[i] = j;
					check[j] = 1;
					while(check[max] == 1)
					{
						max--;
					}
					break;
				}

			}
		}
		for (i = 1; i < N; ++i)
		{
			printf("%d ", ans[i]);
		}
		printf("%d\n", ans[N]);
	}
	return 0;
}