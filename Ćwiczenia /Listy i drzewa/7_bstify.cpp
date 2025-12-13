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

void cut(node *t)
{
    if(t == NULL)
        return;
    cut(t->lc);
    cut(t->rc);
    free(t);
}

void dfs(node *t, int mn, int mx)
{
    if(t->lc != NULL)
    {
        int l_value = t->lc->val;
        if(l_value < mn || l_value > min(mx, t->val))
        {
            cut(t->lc);
            t->lc = NULL;
        }
        else
            dfs(t->lc, mn, min(mx, t->val));
    }
    if(t->rc != NULL)
    {
        int r_value = t->rc->val;
        if(r_value < max(mn, t->val) || r_value > mx)
        {
            cut(t->rc);
            t->rc = NULL;
        } 
        else
            dfs(t->rc, max(mn, t->val), mx);
    }
}

void bstify(bin_tree t)
{
    dfs(t, 0, INT_MAX);
}

int main() 
{
    return 0;
}