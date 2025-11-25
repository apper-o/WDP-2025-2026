#include <stdlib.h>
#include <stdio.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct{
    int type;
    int dist;
} motel;

const int INF = 2000000;

int main()
{
    int n;
    scanf("%d", &n);
    motel *arr = (motel*)malloc(n * sizeof(motel)); 
    for(int i=0;i<n;i++)
        scanf("%d%d", &arr[i].type, &arr[i].dist);
    int resmx = 0, resmn = INF;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            for(int k=j+1;k<n;k++)
            {
                if(arr[i].type != arr[k].type && arr[i].type != arr[j].type && arr[j].type != arr[k].type)
                {
                    resmx = max(resmx, min(arr[j].dist - arr[i].dist, arr[k].dist - arr[j].dist));
                    resmn = min(resmn, max(arr[j].dist - arr[i].dist, arr[k].dist - arr[j].dist));
                }
            }

        }
    }
    if(resmn == 2000000)
        printf("%d %d\n", 0, 0);
    else
        printf("%d %d\n", resmn, resmx);
    free(arr);
    return 0;
}