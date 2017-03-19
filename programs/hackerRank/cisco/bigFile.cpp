#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct files
{
	int M;
	int Arr[300];
};

files fileArr[300];
int N;

int compare (const void * p1, const void * p2)
{
	return ( *(int*)p1 - *(int*)p2 );
}

int queryAll (int *A, int size) {
	int count = 0, flag;
	for (int i = 0; i < N; ++i)
	{
		int k = 0;
		flag = 1;
		for (int j = 0; j < fileArr[i].M && k < size; ++j)
		{
			if (fileArr[i].Arr[j] > A[k])
			{
				flag = 0;
				break;
			}
			if (fileArr[i].Arr[j] == A[k])
			{
				k++;
			}
		}
		if (flag == 1 && k == size)
		{
			count ++;
		}
	}
	return count;
}

int queryAny (int *A, int size) {
	int count = 0;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if ((int*) bsearch (&A[j], fileArr[i].Arr, fileArr[i].M, sizeof (int), compare) != NULL)
			{
				count++;
				break;
			}
		}
	}
	return count;
}

int querySom (int *A, int size) {
	int count = 0, flagFull, flagAny;
	for (int i = 0; i < N; ++i)
	{
		int k = 0, j = 0;
		flagFull = 1; flagAny = 0;
		while (j < fileArr[i].M && k < size)
		{
			if (fileArr[i].Arr[j] > A[k])
			{
				flagFull = 0;
				k++;
			}
			else if (fileArr[i].Arr[j] == A[k])
			{
				flagAny = 1;
				k++; j++;
			}
			else j++;
		}
		if (k < size)
		{
			flagFull = 0;
		}
		if (flagFull == 0 && flagAny == 1)
		{
			count ++;
		}
	}
	return count;
}

int main()
{
	int Q, K, T;
	int qArr[300];
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &fileArr[i].M);
		for (int j = 0; j < fileArr[i].M; ++j)
		{
			scanf("%d", &fileArr[i].Arr[j]);
		}
		qsort (fileArr[i].Arr, fileArr[i].M, sizeof(int), compare);
	}
	scanf("%d", &Q);
	for (int i = 0; i < Q; ++i)
	{
		scanf("%d %d", &T, &K);
		for (int j = 0; j < K; ++j)
		{
			scanf("%d", &qArr[j]);
		}
		qsort (qArr, K, sizeof(int), compare);
		switch(T) {
			case 1 : printf("%d\n", queryAll(qArr, K)); break;
			case 2 : printf("%d\n", queryAny(qArr, K)); break;
			case 3 : printf("%d\n", querySom(qArr, K)); break;
		}
	}
	return 0;
}