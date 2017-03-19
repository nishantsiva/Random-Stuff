#include <stdio.h>
#include <stdlib.h>

long d, s, t;
long r1, r2;

void extEucledianGCD (long a, long b) {
	long _s, _t;
	if (b == 0)
	{
		d = a;
		s = 1;
		t = 0;
	}
	else {
		extEucledianGCD(b, a%b);
		_s = s;
		_t = t;
		s = _t;
		t = _s - (a/b)*_t;
	}
}

int calculate (long n, long c1, long n1, long c2, long n2) {
	long l, h, varCost;
	extEucledianGCD(n1,n2);
	if (n%d != 0)
	{
		return 0;
	}
	s *= n / d;
	t *= n / d;
 	n1 /= d;
 	n2 /= d;
 	l = s >= 0 ? -s / n2 : (-s + n2 - 1) / n2;  
  	h = t >= 0 ? t / n1 : (t - n1 + 1) / n1;
  	if (l > h)
  	{
  		return 0;
  	}
  	varCost = c1 * n2 - c2 * n1;
  	if (varCost >= 0)
  	{
  		r1 = s + n2 * l, r2 = t - n1 * l;
  	}
  	else{
  		r1 = s + n2 * h, r2 = t - n1 * h;
  	}
  	return 1;
}

int main(int argc, char const *argv[])
{
	long n, c1, n1, c2, n2;
	scanf("%ld", &n);
	while(n > 0) {
		scanf("%ld %ld\n%ld %ld", &c1, &n1, &c2, &n2);
		if (calculate(n, c1, n1, c2, n2) == 1)
		{
			printf("%ld %ld\n", r1, r2);
		}
		else {
			printf("failed\n");
		}
		scanf("%ld", &n);
	}
	return 0;
}