#include <stdio.h>

int main (int argc, char const* argv[])
{
	int cases;
	long long int sum, N, l;
	scanf("%d", &cases);
	while (cases--)
	{
		scanf("%lld", &N);
		sum = 1;
		if (N > 1)
		{
			sum = 0; l = 0;
			while (++l <= N/l)
		
			{
				if ((N %l) == 0) 
				{
					sum += l;
					if (l < N/l)
					{
						sum += N/l;
					}
				}
			}
		}
		printf("%lld\n", sum);
	}
	return 0;
}
