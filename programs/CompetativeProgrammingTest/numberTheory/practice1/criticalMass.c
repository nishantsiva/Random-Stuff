#include <stdio.h>
#include <stdlib.h>

int safeArr[31];

int findSafe (int cur) {
	if (safeArr[cur] != -1)	{
		return safeArr[cur];
	}
	else if (cur == 1) {
		safeArr[cur] = 2;
	}
	else if (cur == 2) {
		safeArr[cur] = 4;
	}
	else if (cur == 3) {
		safeArr[cur] = 7;
	}
	else {
		safeArr[cur] = findSafe(cur-1) + findSafe(cur-2) + findSafe(cur-3);
	}
	return safeArr[cur];
}

int main(int argc, char const *argv[]) {
	int N, i;
	for (i = 0; i < 31; ++i) {
		safeArr[i] = -1;
	}
	scanf("%d", &N);
	while (N != 0) {
		printf("%d\n", (1 << N) - findSafe (N));
		scanf("%d", &N);
	}
	return 0;
}