#include <stdio.h>

int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b, a%b);
}

void find(long int val) {
	int d, n;
	long int count = 0;
	for(d = 1;;d++){
		for(n = 0; n <= d; n++){
			if(n%2 == 0 && d%2 == 0) continue;
			if(gcd(n,d) == 1){
				if(++count == val){
					printf("%d/%d\n", n, d);
					return;
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	long int count;
	scanf("%ld", &count);
	printf("%ld\n", count);
	find(count);
	return 0;
}