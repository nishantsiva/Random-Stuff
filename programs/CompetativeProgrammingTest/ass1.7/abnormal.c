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
	int len,i,l,r;
	scanf("%d",&cases);
	while (cases--) {
		scanf("\n%s",str);
		for (len = 0; str[len] != '\0'; len += 1);
		for (i = 0; i < len-1; i += 1) {
			l = 0;
			r = i;
			flag = 1;
			while (l < r) {
				if (str[l++] != str[r--]) {
					flag = 0;
					break;
				}
			}
			if(flag == 0) continue;
			l = i+1;
			r = len-1;
			while (l < r) {
				if (str[l++] != str[r--]) {
					flag = 0;
					break;
				}
			}
			if(flag == 0) continue;
			printf("alindrome\n");
			flag = 1;
			break;
		}
		if (flag == 1) {
			continue;
		}
		flag = 1;
		l = 0;
		r = len-1;
		while (l < r) {
			if (str[l++] != str[r--]) {
				flag = 0;
				break;
			}
		}
		if(flag == 1) {
			printf("palindrome\n");
			continue;
		}
		printf("simple\n");
	}
	return 0;
}
