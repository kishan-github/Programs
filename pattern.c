#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{
    int n = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
	
    scanf("%d", &n);

    for(i = 0, l = 0; l < (2 * n - 1) ;)
    {
        k = n;
        for(j = 0; j < n; j++)
        {
            printf("%d ", k);
            if(i > j)
                k--;
        }

        for(j = n - 2; j >= 0; j--)
        {
            if(i > j)
                k++;

            printf("%d ",k);
        }
        l++;
        if(l > (n - 1))
            i--;
        else
            i++;
        printf("\n");
    }

    return 0;
}