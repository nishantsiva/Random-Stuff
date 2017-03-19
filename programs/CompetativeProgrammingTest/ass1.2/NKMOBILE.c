#include<stdio.h>
#include<stdlib.h>

int
main (int argc, char *argv[])
{
	int **board,istr,sum;
	int x,y,i,j,l,b,r,t,s,a;
	scanf("%d",&istr);
	while(istr!=3){
		switch(istr){
			case 0:	scanf("%d",&s);
					board = (int**)malloc(sizeof(int*)*s);
					for(i=0;i<s;i++)
						board[i] = (int*)malloc(sizeof(int)*s);
					for(i=0;i<s;i++){
						for(j=0;j<s;j++){
							board[i][j] = 0;
						}
					}
					break;
			case 1: scanf("%d %d %d",&x,&y,&a);
					board[x][y] += a;
					if(board[x][y] < 0)
						board[x][y] = 0;
					break;
			case 2: scanf("%d %d %d %d",&l,&b,&r,&t);
					sum = 0;
					for(i=l;i<=r;i++){
						for(j=b;j<=t;j++){
							sum += board[i][j];
						}
					}
					printf("%d\n",sum);
					break;
			default:break;
		}
		scanf("%d",&istr);
	}
	return 0;
}

