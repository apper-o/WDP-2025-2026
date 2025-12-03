#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct node *bin_tree;
struct node{
    int val;
    bin_tree left, right;
};

void clear(bin_tree t)
{
    if(t != NULL)
    {
        clear(t->left);
        clear(t->right);
        free(t);
    }    
}

bool dfs(bin_tree t, int mx, int mn)
{
    if(t != NULL)
    {
        if(t->val >= mx || t->val <= mn)
            clear(t);
        else
        {
            dfs(t->left, min(mx, t->val), mn);
            dfs(t->right, mn, max(mn, t->val));
        }       
    }
    return true;
}

int main() 
{
    return 0;
}