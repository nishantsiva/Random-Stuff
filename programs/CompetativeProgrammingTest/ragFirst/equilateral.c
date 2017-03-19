#include<stdio.h>
#include<math.h>

#define MAX(x,y) (((x)>(y))?(x):(y))

int main (int argc, char *argv[]) {
	float t1,t2,l,s;
	float pi = 3.14159265359;
	scanf("%f %f",&t1,&t2);
	l = MAX(t1,t2);
	s = (l==t1)?t2:t1;
	printf("Rectangle Size : %f X %f\n",l*sin(pi/3),MAX(l,l/2+s));
	return 0;
}
