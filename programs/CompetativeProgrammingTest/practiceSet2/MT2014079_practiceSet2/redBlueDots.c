#include <stdio.h>
#include <math.h>

#define MIN(x,y) (((x)<(y))?(x):(y))
#define MAX(x,y) (((x)>(y))?(x):(y))

struct point {
	double x, y;
};

struct point redPoints[500], bluePoints[500];
int N, M;

int compare (const void * p1, const void * p2)
{
	struct point *ptr1 = (struct point*)p1;
	struct point *ptr2 = (struct point*)p2;
	if (ptr1->x < ptr2->x) {
		return -1;
	}
	else if (ptr1->x > ptr2->x) {
		return 1;
	}
	return 0;
}

int findMinBlue (int key, int low, int high) {
	int mid = (high + low) / 2;
	if(bluePoints[low].x > key) return -1;
	if(bluePoints[mid].x < key && mid < M-1 && bluePoints[mid+1].x >= key) {
		return mid+1;
	}
	if (bluePoints[mid].x >= key) {
		return findMinBlue(key, low, mid);
	}
	if (bluePoints[mid].x < key) {
		return findMinBlue(key, mid+1, high);
	}
}

int findMaxBlue (int key, int low, int high) {
	int mid = (high + low) / 2;
	if(bluePoints[high].x < key) return -1;
	if(bluePoints[mid].x > key && mid > 0 && bluePoints[mid-1].x <= key) {
		return mid+1;
	}
	if (bluePoints[mid].x >= key) {
		return findMaxBlue(key, low, mid);
	}
	if (bluePoints[mid].x < key) {
		return findMaxBlue(key, mid+1, high);
	}
}

int isEmptyTriag (int p1, int p2, int p3) {
	int bl, bh, i;
	double alpha, beta, gamma;
	bl = findMinBlue(MIN(MIN(redPoints[p1].x, redPoints[p2].x), redPoints[p3].x), 0, M);
	bh = findMaxBlue(MAX(MAX(redPoints[p1].x, redPoints[p2].x), redPoints[p3].x), 0, M);
	if(bl == -1 || bh == -1) return 1;
	for (i = bl; i < bh; i += 1) {
		alpha = ((redPoints[p2].y - redPoints[p3].y)*(bluePoints[i].x - redPoints[p3].x) + (redPoints[p3].x - redPoints[p2].x)*(bluePoints[i].y - redPoints[p3].y)) / 
			((redPoints[p2].y - redPoints[p3].y)*(redPoints[p1].x - redPoints[p3].x) + (redPoints[p3].x - redPoints[p2].x)*(redPoints[p1].y - redPoints[p3].y));
		beta = ((redPoints[p3].y - redPoints[p1].y)*(bluePoints[i].x - redPoints[p3].x) + (redPoints[p1].x - redPoints[p3].x)*(bluePoints[i].y - redPoints[p3].y)) / 
			((redPoints[p2].y - redPoints[p3].y)*(redPoints[p1].x - redPoints[p3].x) + (redPoints[p3].x - redPoints[p2].x)*(redPoints[p1].y - redPoints[p3].y));
		gamma = 1.0f - alpha - beta;
		if (alpha > 0 && beta > 0 && gamma > 0) {
			return 0;
		}
	}
	return 1;
}

int main (int argc, char *argv[]) {
	int count;
	int i, j, k;
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i += 1) {
		scanf("%lf %lf", &redPoints[i].x, &redPoints[i].y);
	}
	for (i = 0; i < M; i += 1) {
		scanf("%lf %lf", &bluePoints[i].x, &bluePoints[i].y);
	}
	qsort (bluePoints, M, sizeof(struct point), compare);
	count = 0;
	for (i = 0; i < N-2; i += 1) {
		for (j = i+1; j < N-1; j += 1) {
			for (k = j+1; k < N; k += 1) {
				count += isEmptyTriag(i, j, k);
			}
		}
	}
	printf("%d\n", count);
	return 0;
}
