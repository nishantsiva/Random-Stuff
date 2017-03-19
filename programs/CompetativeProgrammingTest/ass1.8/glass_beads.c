#include <stdio.h>
#include <stdlib.h>

int sArr[20005];
char str[20005];
int len;

int compare(char *str1, char *str2, int len)
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

int
main (int argc, char *argv[])
{
	int cases, count, tcount, ret;
	int i, j, k;
	char maxCur[10005], *cur;
	for (i = 0; i < 10005; i += 1)
	{
		maxCur[i] = 'z' + 1;
	}
	scanf("%d",&cases);
	while (cases--)
	{
		scanf("\n%s",str);
		for (len = 0; str[len] != '\0'; len += 1);
		for (i = 0; i < len; i += 1)
		{
			str[len+i] = str[i];
			sArr[i] = i;
		}
		count = len;
		k = 1;
		for (i = 1; i < len && count > 1; i *= 2)
		{
			cur = maxCur;
			for (j = 0; j < count; j += 1)
			{
				ret = compare((str+sArr[j]+i-1), cur, (i < len-(i-1))?i:(len-(i-1)));
				if(ret <  0){
					tcount = 0;
					cur = (str + sArr[j] + i-1);
					sArr[tcount++] = sArr[j];
				}
				else if(ret == 0)
				{
					sArr[tcount++] = sArr[j];
				}
			}
			if(len == tcount) break;
			count = tcount;
			k *= 2;
		}
		printf("%d\n",sArr[0] + 1);
	}
	return 0;
}

