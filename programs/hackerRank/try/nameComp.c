#include <stdio.h>

int count = 0;

void fill(int *Arr, int *used, int N, int pos)
{
	int i;
	if(2*N == pos){
		for(i = 0; i < 2*N; i++){
			printf("%c", (char)(Arr[i]+'a'-1));
		}
		printf("\n");
		count++;
		return;
	}
	if(Arr[pos] == 0)
	{
		for (i = 1; i <= N; ++i)
		{
			if((used[i] == -1) && (Arr[pos+i+1] == 0))
			{
				used[i] = 1;
				Arr[pos] = Arr[pos+i+1] = i;
				fill(Arr, used, N, pos+1);
				Arr[pos] = Arr[pos+i+1] = 0;
				used[i] = -1;
			}
			if(count == 101){
				return;
			}
		}
	}
	else{
		fill(Arr, used, N, pos+1);
	}
}

int main(int argc, char const *argv[])
{
	int Arr[30], used[15];
	int N, i;
	scanf("%d", &N);
	for (i = 0; i <= 15; ++i)
	{
		used[i] = -1;
		Arr[2*i] = Arr[2*i+1] = 0;
	}
	fill(Arr, used, N, 0);
	if(count == 0)
	{
		printf("Crazy Compound\n");
	}printf("%d\n",count);
	return 0;
}