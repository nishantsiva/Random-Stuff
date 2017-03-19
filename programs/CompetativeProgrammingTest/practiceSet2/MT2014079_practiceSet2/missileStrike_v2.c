#include <stdio.h>
#include <math.h>

struct missileNode {
	double dist1, dist2, x;
	int isincluded;
};

struct missileNode missile[1000];

int compareDist2 (const void * p1, const void * p2)
{
	struct missileNode *node1 = *(struct missileNode**)p1;
	struct missileNode *node2 = *(struct missileNode**)p2;
	if (node1->dist2 < node2->dist2) {
		return -1;
	}
	else if (node1->dist2 > node2->dist2) {
		return 1;
	}
	return 0;
}

int compareDist1 (const void * p1, const void * p2)
{
	struct missileNode *node1 = *(struct missileNode**)p1;
	struct missileNode *node2 = *(struct missileNode**)p2;
	if (node1->dist1 < node2->dist1) {
		return -1;
	}
	else if (node1->dist1 > node2->dist1) {
		return 1;
	}
	return 0;
}

double distPoints (double x1, double y1, double x2, double y2) {
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

int main (int argc, char *argv[]) {
	double x, y, tx1, ty1, tx2, ty2, totArea, R1, R2;
	double pi = 3.141;
	int i, cases, caseNo, noMissiles, covered;
	int i1, i2, temp, skip;
	struct missileNode *toTwr1[1000], *toTwr2[1000];
	scanf("%d", &cases);
	for (caseNo = 1; caseNo <= cases; caseNo += 1) {
		scanf("%d", &noMissiles);
		scanf("%lf %lf %lf %lf %lf", &tx1, &ty1, &tx2, &ty2, &totArea);
		for (i = 0; i < noMissiles; i += 1) {
			scanf("%lf %lf", &x, &y);
			missile[i].dist1 = distPoints(x, y, tx1, ty1);missile[i].x = x;
			missile[i].dist2 = distPoints(x, y, tx2, ty2);
			toTwr1[i] = missile + i;
			toTwr2[i] = missile + i;
		}
		qsort (toTwr1, noMissiles, sizeof(struct missileNode*), compareDist1);
		qsort (toTwr2, noMissiles, sizeof(struct missileNode*), compareDist2);
		R1 = totArea / (2*pi);
		R2 = 0;
		covered = 0;
		for (i = 0; i < noMissiles && toTwr1[i]->dist1 <= R1; i += 1) covered++;
		if (covered == noMissiles) {
			printf("%d. %d\n", caseNo, 0);
		}
		else {
			i1 = i-1; i2 = -1;
			skip = 0;
			while (i1 >= 0) {
				R2 = toTwr2[i2 + ++skip]->dist2;
				R1 = (totArea - 2*pi*R2) / (2*pi);
				if (R1 < 0) {
					break;
				}
				temp = skip;
				for (i = i1; i >= 0 && toTwr1[i]->dist1 > R1; i -= 1) temp--;
				if (temp > 0) {
					covered += temp;
					i1 = i;
					i2 += skip;
					skip = 0;
				}
			}
			printf("%d. %d\n", caseNo, noMissiles-covered);
		}
	}
	return 0;
}
