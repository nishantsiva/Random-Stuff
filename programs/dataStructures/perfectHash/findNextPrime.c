/*
 * NextPrime
 *
 * Return the first prime number larger than the integer
 * given as a parameter. The integer must be positive.
 */
#define PRIME_FALSE   0     /* Constant to help readability. */
#define PRIME_TRUE    1     /* Constant to help readability. */
#include <stdio.h>
#include <stdlib.h>
int nextprime(int inval) {
    int perhapsprime; /* Holds a tentative prime while we check it. */
    int testfactor; /* Holds various factors for which we test perhapsprime. */
    int found; /* Flag, false until we find a prime. */

    if (inval < 3) /* Initial sanity check of parameter. */
    {
        if (inval <= 0)
            return (1); /* Return 1 for zero or negative input. */
        if (inval == 1)
            return (2); /* Easy special case. */
        if (inval == 2)
            return (3); /* Easy special case. */
    } else {
        /* Testing an even number for primeness is pointless, since
         * all even numbers are divisible by 2. Therefore, we make sure
         * that perhapsprime is larger than the parameter, and odd. */
        perhapsprime = (inval + 1) | 1;
    }
    /* While prime not found, loop. */
    for (found = PRIME_FALSE; found != PRIME_TRUE; perhapsprime += 2) {
        /* Check factors from 3 up to perhapsprime/2. */
        for (testfactor = 3; testfactor <= (perhapsprime >> 1) + 1; testfactor
                += 1) {
            found = PRIME_TRUE; /* Assume we will find a prime. */
            if ((perhapsprime % testfactor) == 0) /* If testfactor divides perhapsprime... */
            {
                found = PRIME_FALSE; /* ...then, perhapsprime was non-prime. */
                goto check_next_prime;
                /* Break the inner loop, go test a new perhapsprime. */
            }
        }
        check_next_prime: ; /* This label is used to break the inner loop. */
        if (found == PRIME_TRUE) /* If the loop ended normally, we found a prime. */
        {

            return (perhapsprime); /* Return the prime we found. */
        }
    }

    return (perhapsprime); /* When the loop ends, perhapsprime is a real prime. */
}

int main(int argc, char *argv[]) {
    int intvar;
    if (sscanf(argv[1], "%i", &intvar) != 1) {
        printf("please use an integer parameter to compute the next prime\n");
    } else
        printf("%d => %d\n", intvar, nextprime(intvar));
    return 0;
}


