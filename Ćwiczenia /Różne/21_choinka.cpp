#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int INF = 1e9;

typedef struct node *bin_tree;
struct node
{
    int val;
    bin_tree left, right;
};

void get_size(bin_tree t, int &n)
{
    if(t == NULL)
        return;
    t->val = n++;
    get_size(t->left, n);
    get_size(t->right, n);
}

void dfs(bin_tree t, int n, vector<vector<long long>> &dp)
{
    if(t->left == NULL && t->right == NULL)
        dp[t->val][0] = dp[t->val][1] = dp[t->val][2] = dp[t->val][3] = 1;
    if(t->left == NULL || t->right == NULL)
        return;
    dfs(t->left, n, dp);
    dfs(t->right, n, dp);
    for(int i=0;2*i<=3*n;i++)
    {
        int val = dp[t->left->val][i] * dp[t->right->val][i];
        for(int j=0;j<=3;j++)
            dp[t->val][2*i+j] += val; 
    }
}

int solve(bin_tree t)
{
    int n = 0;
    get_size(t, n);
    vector<vector<long long>> dp(n, vector<long long>(3*n + 4));
    dfs(t, n, dp);
    int res = 0;
    for(int i=0;i<=3*n;i++)
        res += dp[t->val][i];
    return res;
}

int main() 
{
    return 0;
}
