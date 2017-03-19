/* qsort example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */

int values[] = { 40, 10, 100, 90, 20, 25 };

/*
 * RETURNS
 * <0	The element pointed by p1 goes before the element pointed by p2
 * 0	The element pointed by p1 is equivalent to the element pointed by p2
 * >0	The element pointed by p1 goes after the element pointed by p2
*/
int compare (const void * p1, const void * p2)
{
	return ( *(int*)p1 - *(int*)p2 );
}

int main ()
{
	int n;
	qsort (values, 6, sizeof(int), compare);
	for (n=0; n<6; n++)
		printf ("%d ",values[n]);
	return 0;
}
