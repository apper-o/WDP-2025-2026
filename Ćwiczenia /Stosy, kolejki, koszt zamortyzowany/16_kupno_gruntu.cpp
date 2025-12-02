#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct{
    int x, y;
} pii;

struct cmp
{
    bool operator () (pii a, pii b)
    {
        return !(a.y < b.y);
    }
};

int get(int **arr, int x0, int y0, int x1, int y1)
{
    return arr[y1][x1] - arr[y0-1][x1] - arr[y1][x0-1] + arr[y0-1][x0-1];
}

void solve(int **arr, int n, int k)
{
    std::stack<int> off[n+2]; // points such that their value is greater that k [columns][rows]
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(arr[i][j] > 2*k)
            {
                off[j].push(i);
                arr[i][j] = 0;
            }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            arr[i][j] += arr[i][j-1] + arr[i-1][j] - arr[i-1][j-1];
    for(int y=n;y>0;y--)
    {
        std::priority_queue<pii, std::vector<pii>, cmp> rect; // stores all valid rectangles, each rectangle is checked only once - when it is maximal 
        for(int x=1;x<=n;x++)
        {
            while(off[x].size() && off[x].top() > y)
                off[x].pop();
            int top = (off[x].size() ? off[x].top() + 1 : 1); // highest valid element
            while(rect.size() && rect.top().y < top)
            {
                pii tmp = rect.top();
                rect.pop();
                int sum = get(arr, tmp.x, tmp.y, x-1, y);
                if(k <= sum && sum <= 2*k)
                {
                    printf("%d %d %d %d\n", tmp.x, tmp.y, x-1, y);
                    return;
                }
                rect.push((pii){tmp.x, top}); 
            }
            rect.push((pii){x, top});
        }
        while(rect.size())
        {
            pii tmp = rect.top();
            rect.pop();
            int sum = get(arr, tmp.x, tmp.y, n, y);
            if(k <= sum && sum <= 2*k)
            {
                printf("%d %d %d %d\n", tmp.x, tmp.y, n, y);
                return;
            }
        }
    }
    printf("NIE\n");
}

int main()
{
    int n, k;
    scanf("%d%d", &k, &n);    
    int **arr = (int **)malloc((n+2) * sizeof(int*)); 
    for(int i=0;i<=n+1;i++)
        arr[i] = (int *)malloc((n+2) * sizeof(int));
    for(int i=0;i<=n+1;i++)
        arr[i][0] = arr[0][i] = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d", &arr[i][j]);
    solve(arr, n, k);
    return 0;
}