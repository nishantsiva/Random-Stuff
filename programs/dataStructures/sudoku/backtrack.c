#include<stdio.h>

#define TRUE 	1
#define FALSE	0
#define INPUT	3

int size = INPUT * INPUT;

int check(int a[size][size],int val,int row,int col){
	int i,j;
	for(i=0;i<size;i++){
		if(a[i][col] == val)
			return FALSE;
	}
	for(i=0;i<size;i++){
		if(a[row][i] == val)
			return FALSE;
	}
	for(i=(row/INPUT)*INPUT;i<(row/INPUT)*INPUT+INPUT;i++){
		for(j=(col/INPUT)*INPUT;j<(col/INPUT)*INPUT+INPUT;j++){
			if(a[i][j]==val)
				return FALSE;
		}
	}
	return TRUE;
}

int solve(int a[size][size],int row,int col){
	int i,nrow,ncol;
	if(row > size-1)
		return TRUE;
	ncol = col + 1;
	nrow = row;
	if(ncol > size-1){
		ncol = 0;
		nrow ++;
	}
	if(a[row][col]!=0)
		return solve(a,nrow,ncol);
	for(i=1;i<=size;i++){
		if(check(a,i,row,col)){
			a[row][col] = i;
			if(solve(a,nrow,ncol))
				return TRUE;
			a[row][col] = 0;
		}
	}//printf("NISH %d %d\n",row,col);
	return FALSE;
}	
/*
print(int a[size][size]){
	int i,j;
	for(i=0;i<size;i++){
		if(i==0)
			printf("\n+------+-------+-------+\n");
		for(j=0;j<size;j++){
			if(j==0)
				printf("|");
			if(a[i][j]>0)
				printf("%d",a[i][j]);
			else
				printf(" ");
			if(j%INPUT == 2)
				printf(" |");
			printf(" ");
		}
		if(i%INPUT == 2)
			printf("\n+------+-------+-------+");
		printf("\n");
	}
}
*/

print(int a[size][size]){
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			//if(a[i][j]>0)
				printf("%2d",a[i][j]);
			//else
				//printf("  ");
			printf(" ");
		}
		printf("\n");
	}
}

main(){
	int i,j;
	int a[size][size];
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			scanf("%d",&a[i][j]);
		}
	}
	printf("\nINPUT :\n");
	print(a);
	if(solve(a,0,0)){
		printf("\nOUTPUT :\n");
		print(a);
	}
	else
		printf("Cant Solve.\n");
}
