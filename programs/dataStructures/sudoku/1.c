#include<stdio.h>

int
main (int argc, char *argv[])
{
	int i,j,size,val;
	if(argc != 2){
		printf("Ussage: ./a.out {input}\n");
		return;
	}
	val = atoi(argv[1]);
	size = val*val;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%d ",0);
		}
		printf("\n");
	}
	return 0;
}
