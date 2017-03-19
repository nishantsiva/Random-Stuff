/* qsort example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */

char values[][10] = { "nish", "div", "singh", "cat", "mesh", "nish" };

int compare (const void * p1, const void * p2)
{
	return strcmp((char**)p1,(char**)p2);
}

int main ()
{
	int n;
	qsort (values, 6, sizeof(char)*10, compare);
	for (n=0; n<6; n++)
		printf ("%s ",values[n]);
	return 0;
}
