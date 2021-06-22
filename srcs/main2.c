#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
# include <fcntl.h>
int main (void)
{
    int i;
    i = 0;

    int  fd = open("./txt", O_RDONLY);
    perror("error");
    
    while (i < 300)
    {
        printf("%d, %s\n",i,  strerror(i));
        i++;
    }
    return (0);
}