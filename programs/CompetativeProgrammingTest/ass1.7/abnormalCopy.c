#include<stdio.h>
#include<stdlib.h>

char str[200000];

int isPalindrome(int l,int r){
	while (l < r) {
		if (str[l++] != str[r--]) {
			return -1;
		}
	}
	return 1;
}

int main (int argc, char *argv[]) {
	int cases,flag;
	int len,i;
	scanf("%d",&cases);
	while (cases--) {
		scanf("\n%s",str);
		for (len = 0; str[len] != '\0'; len += 1);
		flag = 0;
		for (i = 0; i < len-1; i += 1) {
			if(isPalindrome(0,i) == 1 && isPalindrome(i+1,len-1) == 1){
				printf("alindrome\n");
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			continue;
		}
		if (isPalindrome(0,len-1) == 1) {
			printf("palindrome\n");
			continue;
		}
		printf("simple\n");
	}
	return 0;
}
