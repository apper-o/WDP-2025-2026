#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}


int trojkat(int n, int *arr)
{  
    qsort(arr, n, sizeof(int), comp);
    int res = 0; 
    for(int i=2;i<n;i++)
        res |= (2 * max(max(arr[i-1], arr[i-2]), arr[i]) <= arr[i-2] + arr[i-1] + arr[i]);
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    int *arr = malloc(n * sizeof(int));
    for(int i=0;i<n;i++)
        scanf("%d", &arr[i]);
    printf("%d", trojkat(n ,arr));
    return 0;
}