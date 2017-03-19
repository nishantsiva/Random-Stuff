#include <stdio.h>
#include <stdlib.h>

struct Strings {
	char str[100005];
	int len;
};

struct Strings *strArr;

int compare (const void * p1, const void * p2)
{
	struct Strings *str1 = (struct Strings*)p1;
	struct Strings *str2 = (struct Strings*)p2;
	return (str1->len - str2->len);
}

int cmpStr(const void * p1, const void * p2) {
	struct Strings *str1 = (struct Strings*)p1;
	struct Strings *str2 = (struct Strings*)p2;
	int i;
	for (i = 0; i < str1->len && i < str2->len; i += 1) {
		if( str1->str[i] == str2->str[i]){
			continue;
		}
		return str1->str[i] - str2->str[i];
	}
	if(str1->len == str2->len)
		return 0;
	if(i == str1->len)
		return -1;
	return 1;
}

int compareStr(char *str1, char *str2, int len)
{
	int i = 0;
	while (i < len)
	{
		if(str1[i] == str2[i]){
			i++;
			continue;
		}
		return str1[i] - str2[i];
	}
	return 0;
}



int radixSearch(int cur, int n) {
	int i, j, iter, ret, len, cmplen;
	char *str1, *str2;
	str1 = strArr[cur].str;
	str2 = strArr[cur+1].str;
	len = strArr[cur].len;
	i = 1;
	iter = 0;
	while (1) {
		cmplen = (i < len-(i-1))?i:(len-(i-1));
		ret = compareStr(str1 + iter, str2 + iter, cmplen);
		if(ret != 0)
			return 0;
		i *= 2;
		iter += cmplen;
		if(iter >= len-1)
			break;
	}
	return 1;
}

int main (int argc, char *argv[]) {
	int cases, n, flag, templen;
	int i, j;
	scanf("%d",&cases);
	while (cases--) {
		scanf("%d",&n);
		strArr = (struct Strings*)malloc(sizeof(struct Strings) * n);
		for (i = 0; i < n; i += 1) {
			scanf("%s",strArr[i].str);
			for (j = 0; strArr[i].str[j] != '\0'; j += 1);
			strArr[i].len = j;
		}
		qsort(strArr, n, sizeof(struct Strings), compare);
		
		qsort(strArr, n, sizeof(struct Strings), cmpStr);
		flag = 0;
		for (i = 0; i < n-1; i += 1) {
			if(radixSearch(i, n) == 1) {
				flag = 1;
				break;
			}
		}
		if(flag == 1)
			printf("1");
		else
			printf("0");
		free(strArr);
	}
	printf("\n");
	return 0;
}
