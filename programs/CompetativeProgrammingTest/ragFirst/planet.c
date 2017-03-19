#include <stdio.h>
#include <math.h>

int minAngle = 10;
float relT[3];

struct tIntersect {
	int id, isL, nLoop;
	float time;
};
struct tIntersect timeSlots[6];

int compareF (const void * p1, const void * p2)
{
	if ( *(float*)p1 > *(float*)p2 ) return 1;
	if ( *(float*)p1 < *(float*)p2 ) return -1;
	return 0;
}

int compareStruct (const void * p1, const void * p2) {
	float t1 = ((const struct tIntersect*)p1)->time;
	float t2 = ((const struct tIntersect*)p2)->time;
	if ( t1 > t2 ) return 1;
	if ( t1 < t2 ) return -1;
	return 0;
}

void updateTime (int id) {
	int i;
	for (i = 0; i < 6; i += 1) {
		if(timeSlots[i].id == id) {
			if (timeSlots[i].isL == 1) {
				timeSlots[i].time = relT[id] * (++(timeSlots[i].nLoop)) * (360.0 - minAngle)/360.0;
			}
			else {
				timeSlots[i].time = relT[id] * (++(timeSlots[i].nLoop)) * (360.0 + minAngle)/360.0;
			}
		}
	}
}

int main (int argc, char *argv[]) {
	float T[3];
	float pi = 3.14159265359;
	int i;
	scanf("%f %f %f",&T[0],&T[1],&T[2]);
	qsort(T, 3, sizeof(float), compareF);
	if (T[0] <= 0) {
		printf("NA\n");
		return 0;
	}
	/*
	 * 0-1 : 0
	 * 1-2 : 1
	 * 0-2 : 2
	 */
	
	relT[0] = 1 / (1/T[0] - 1/T[1]);
	relT[1] = 1 / (1/T[1] - 1/T[2]);
	relT[2] = 1 / (1/T[0] - 1/T[2]);
	for (i = 0; i < 3; i += 1) {
		timeSlots[2*i].isL 		= 1;
		timeSlots[2*i].nLoop 	= 1;
		timeSlots[2*i].id 		= i;
		timeSlots[2*i].time 	= (360 - minAngle)/360.0 * relT[i];

		timeSlots[2*i+1].isL 	= 0;
		timeSlots[2*i+1].nLoop 	= 1;
		timeSlots[2*i+1].id 	= i;
		timeSlots[2*i+1].time 	= (360 + minAngle)/360.0 * relT[i];
	}
	while (1) {
		qsort((void*)&timeSlots, 6, sizeof(struct tIntersect), compareStruct);
		for (i = 0; i < 3; i += 1) {
			if (timeSlots[i].isL == 0) {
				break;
			}
		}
		if (i == 3) {
			printf("%f\n",timeSlots[2].time);
			break;
		}
		updateTime(timeSlots[i].id);
	}
	return 0;
}
