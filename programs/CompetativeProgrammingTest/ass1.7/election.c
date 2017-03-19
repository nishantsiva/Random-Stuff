#include<stdio.h>
#include<stdlib.h>

char party[24][84];
char member[24][84];
int count[24];
int cases,N,M;
int maxCount,winner;
char temp[84];

int main (int argc, char *argv[]) {
	int i,iter,row,col;
	scanf("%d",&cases);
	while(cases--){
		winner = -1;
		maxCount = 0;
		scanf("%d",&N);
		for (i = 0; i < N; i += 1) {
			count[i] = 0;
			scanf("\n%[^\n]s",member[i]);
			scanf("\n%[^\n]s",party[i]);
		}
		scanf("%d",&M);
		for (i = 0; i < M; i += 1) {
			iter = 0;
			row = 0;
			col = 0;
			scanf("\n%[^\n]s",temp);
			while (temp[iter] != '\0' || member[row][col] != '\0') {
				if(temp[iter] == member[row][col]){
					iter++;
					col++;
				}
				else{
					col = 0;
					iter = 0;
					if(++row == N)
						break;
				}
			}
			if(row < N) {
				if (++(count[row]) > maxCount) {
					maxCount = count[row];
					winner = row;
				}
				else if (count[row] == maxCount) {
					winner = -1;
				}
			}
		}
		if (winner == -1) {
			printf("tie\n");
		}
		else {
			printf("%s\n",party[winner]);
		}
		if(cases > 0) {
			printf("\n");
		}
	}
	return 0;
}
