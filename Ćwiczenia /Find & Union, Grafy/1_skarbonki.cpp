#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct node *bin_tree;

typedef struct node{
    int val;
    struct node *lc;
    struct node *rc;
} node;

int solve(int *arr, int n)
{
    int *vis = (int *)malloc((n+1) * sizeof(int));
    int res = 0;
    int timer = 0;
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            int v = i;
            timer++;
            while(!vis[v])
            {
                vis[v] = timer;
                v = arr[v];
            }
            res += (vis[v] == timer);
            vis[v] = 1; 
        }
    }
    return res;
}

int main() 
{
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++)
        scanf("%d", &arr[i]);
    printf("%d", solve(arr, n));
    return 0;
}