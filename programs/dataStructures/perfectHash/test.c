#include<stdio.h>

main(){
	int r;
	srand(time(NULL));
	r = ( rand() % 6 ) + 1;
	for(r=0;r<10;r++)
	printf("%d\n",( rand() % 6 ) + 1);
}
