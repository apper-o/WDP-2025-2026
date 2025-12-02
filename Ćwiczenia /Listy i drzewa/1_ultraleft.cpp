#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;
int k = INF;

typedef struct node
{
    int val;
    struct node *lc;
    struct node *rc;
} node;

void dfs(node *t, int dep)
{
    if(t->lc == NULL && t->rc == NULL)
    {
        k = (k < dep ? -1 : dep);
        return;
    }
    if(t->lc)
        dfs(t->lc, dep+1);
    if(t->rc)
        dfs(t->rc, dep+1);
}

bool ultraleft(node t)
{
    k = INF;
    dfs(&t, 1);
    return k != -1;
}

int main() 
{
    return 0;
}