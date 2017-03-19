#include <stdio.h>
#include <math.h>

double areaTriag( double a, double b, double c ) {
	double s;
	s = (a+b+c)/2.0;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

int main (int argc, char *argv[]) {
	int cases;
	double U, V, W, u, v, w;
	double sU, sV, sW, su, sv, sw;
	double xu, xv, xw;
	double vol, sumArea, radius;
	scanf("%d", &cases);
	while (cases--) {
		scanf("%lf %lf %lf %lf %lf %lf", &U, &V, &w, &W, &v, &u);
		sU = U*U; sV = V*V; sW = W*W;
		su = u*u; sv = v*v; sw = w*w;
		xu = sv + sw - sU;
		xv = sw + su - sV;
		xw = su + sv - sW;
		vol = (double)(4*su*sv*sw - su*xu*xu - sv*xv*xv - sw*xw*xw + xu*xv*xw);
		vol = sqrt(vol) / (double)12;

		sumArea = areaTriag(U, V, W);
		sumArea += areaTriag(U, v, w);
		sumArea += areaTriag(u, V, w);
		sumArea += areaTriag(u, v, W);
		
		radius = 3.0*vol/sumArea;
		printf("%.4f\n",radius);
	}
	return 0;
}
