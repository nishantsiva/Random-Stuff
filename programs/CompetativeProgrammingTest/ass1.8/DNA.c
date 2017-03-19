#include <stdio.h>
#include <stdlib.h>

struct Suffix {
	int index;
	char *suff;
};

char s1[303], s2[303];
int len1, len2;

int compare(const void * p1, const void * p2) {
	struct Suffix *a = (struct Suffix*)p1;
	struct Suffix *b = (struct Suffix*)p2;
	return strcmp(a->suff,b->suff);
}

void buildSuffixArray(char *str, int *arr, int len) {
	struct Suffix suffixes[303];
	int i;
	for (i = 0; i < len; i += 1) {
		suffixes[i].index = i;
		suffixes[i].suff = str + i;
	}
	qsort(suffixes, len, sizeof(struct Suffix), compare);
	for (i = 0; i < len; i += 1) {
		arr[i] = suffixes[i].index;
	}
}

int findMaxEqual(int *arr, int start1, int start2, int low, int high) {
	int l, r, mid, first, last;
	if (low > high || s1[start1] == '\0') {
		return 0;
	}
	l = low;
	r = high;
	first = -1;
	while (r >= l) {
		mid = (l + r)/2;
		if (((mid == low) || (s2[start2+arr[mid - 1]] < s1[start1])) && (s2[start2+arr[mid]] == s1[start1])) {
			first = mid;
			break;
		}
		if (s2[start2+arr[mid]] < s1[start1]) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	if (first == -1) {
		return 0;
	}
	l = low;
	r = high;
	while (r >= l) {
		mid = (l + r)/2;
		if (((mid == high) || (s2[start2+arr[mid + 1]] > s1[start1])) && (s2[start2+arr[mid]] == s1[start1])) {
			last = mid;
			break;
		}
		if (s2[start2+arr[mid]] > s1[start1]) {
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	return 1 + findMaxEqual(arr, start1+1, start2+1, first, last);
}

int main (int argc, char *argv[]) {
	int sArr1[303], sArr2[303], ansArr[300];
	int i, j, iter, maxLen, ret, flag = 0;;
	while (scanf("%s",s1) == 1) {
		scanf("%s",s2);
		if(flag == 1) {
			printf("\n");
		}
		flag = 1;
		for (len1 = 0; s1[len1]; len1 += 1);
		for (len2 = 0; s2[len2]; len2 += 1);
		buildSuffixArray(s1, sArr1, len1);
		buildSuffixArray(s2, sArr2, len2);
		maxLen = 0;
		for (i = 0; i < len1; i += 1) {
			ret = findMaxEqual(sArr2, sArr1[i], 0, 0, len2-1);
			if (ret > maxLen) {
				maxLen = ret;
				iter = 0;
				ansArr[iter++] = sArr1[i];
			}
			else if (ret != 0 && ret == maxLen) {
				ansArr[iter++] = sArr1[i];
			}
		}
		if (maxLen > 0) {
			for (i = 0; i < iter; i += 1) {
				if((i > 0) && (strncmp(s1+ansArr[i], s1+ansArr[i-1], maxLen) == 0)){
					continue;
				}
				for (j = 0; j < maxLen; j += 1) {
					printf("%c",s1[ansArr[i] + j]);
				}
				printf("\n");
			}
		}
		else {
			printf("No common sequence.\n");
		}
		scanf("\n");
	}
	return 0;
}
