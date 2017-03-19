#include <stdio.h>
#include <stdlib.h>

int main(){
	char str[102];
	int i, num;

	while (scanf("%s", str) == 1){
		num = 0;
		for (i = 0; str[i] != '#'; ++i)
		{
			if (str[i] == '\0')
			{
				scanf("%s", str);
				i = -1;
				continue;
			}
			num = num << 1;
			num += str[i] - '0';
			num %= 131071;
		}
		if (num == 0){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}