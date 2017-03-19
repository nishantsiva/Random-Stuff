#include <iostream>
#include <stdio.h>

using namespace std;

int main (int argc, char const* argv[])
{
	int cases, N, prev, cur;
	scanf("%d", &cases);
	while (cases--)
	{
		bool prevErr = false;
		int count = 0;
		scanf("%d", &N);
		for (unsigned int i = 0; i < N; i += 1)
		{
			scanf("%d", &cur);
			if (i == 0)
			{
				prev = cur;
				continue;
			}
			if (prev == cur)
			{
				prevErr = false;
				continue;
			}
			if (prevErr == false)
			{
				count++;
			}
			count++;
			prevErr = true;
			prev = cur;
		}
		printf("%d\n", count);
	}
	return 0;
}
