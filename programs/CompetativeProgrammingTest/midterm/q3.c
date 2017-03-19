#include <stdio.h>
#include <stdlib.h>

char str[100005];
int suffArr[100005];
int length;

int cmpStr(const void * p1, const void * p2) {
	char *str1 = str + *(int*)p1;
	char *str2 = str + *(int*)p2;
	int len, iter, chunk, ret, i;
	len = (*(int*)p1 > *(int*)p2) ? length - *(int*)p1 : length - *(int*)p2;  
	i = 1;
	iter = 0;
	while (iter < len) {
		chunk = (i < (len - iter) ? i : (len - iter));
		ret = strncmp(str1 + iter, str2 + iter, chunk);
		if (ret != 0) {
			return ret;
		}
		iter += chunk;
		i *= 2;
	}
	if(str1[iter] == '\0') {
		return -1;
	}
	return 1;
}

int main (int argc, char *argv[]) {
	int cases, test, K, minLen, maxLen, longest, count, ret;
	int i, iter, iter1, skipFlag, skip;
	scanf("%d",&cases);
	for (test = 1; test <= cases; test += 1) {
		scanf("%s",str);
		scanf("%d",&K);
		for (length = 0; str[length] != '\0'; length += 1){
			suffArr[length] = length;
		}
		qsort(suffArr, length, sizeof(int), cmpStr);
		
		minLen = 1;
		maxLen = length / K;
		longest = 0;
		
		for (i = minLen; i <= maxLen; i++) {
			count = 1;
			iter = 0;
			skipFlag = 0;
			skip = 0;
			while (iter + skip < length) {
				if (abs(suffArr[iter+skip] - suffArr[iter]) > i){
					ret = strncmp(str+suffArr[iter], str+suffArr[iter+skip], i);
					if (ret == 0) {
						count++;
					}
					else {
						if(skipFlag == 1) {
							iter = iter1;
							skipFlag = 0;
						}
						skip = 0;
						count = 1;
					}
					if (count == K) {
						longest = i;
						break;
					}
					iter++;
				}
				else{
					skipFlag = 1;
					iter1 = iter + 1;
					skip++;
				}
			}
			if(iter >= length){
				break;
			}
		}
		printf("Case %d: %d\n", test, longest);
	}
	return 0;
}
