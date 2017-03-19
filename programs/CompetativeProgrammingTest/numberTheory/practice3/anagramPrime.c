#include <stdio.h>
#include <stdlib.h>

int Arr[] = {2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, 97, 113, 131, 199, 311, 337, 373, 733, 919, 991};

int digits (int n) {
	int k = 0;
	while (n > 0){
		n /= 10;
		k++;
	}
	return k;
}

int main(int argc, char const *argv[])
{
	long n;
	int i;
	while (scanf("%ld", &n)==1 && n>0){
		if (n > 990)
		{
			printf("0\n");
		}
		else {
			for (i = 0;; ++i)
			{
				if (Arr[i] > n)
				{
					if (digits(n) < digits(Arr[i]))
					{
						printf("0\n");
					}
					else{
						printf("%d\n", Arr[i]);
					}
					break;
				}	
			}
		}
	}
	return 0;
}