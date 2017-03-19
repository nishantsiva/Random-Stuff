#include <unistd.h>
#include <stdio.h>
 
int main(void)
{
     
    printf("I'll be back in 1 seconds...\n\n");
    sleep(1);
    printf("I'm back!");
    getchar();
     
    return(0);
}
