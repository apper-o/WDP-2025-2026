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

struct node
{
    int val;
    bin_tree left, right, next;
};

void solve(bin_tree t, std::vector<bin_tree> &nodes)
{  
    if(t == NULL)
        return;
    solve(t->left, nodes);
    nodes.push_back(t);
    solve(t->right, nodes);
}

void fastryguj(bin_tree t)
{
    std::vector<bin_tree> nodes;
    solve(t, nodes);
    for(int i=0,j=0;i<nodes.size();i++)
    {
        while(j < nodes.size() && nodes[j]->val <= nodes[i]->val)
            j++;
        nodes[i]->next = (j == nodes.size() ? NULL : nodes[j]);
    }
}

// TEST

bin_tree newNode(int val)
{
    bin_tree n = new node;
    n->val = val; n->left = n->right = n->next = NULL;
    return n;
}

int main() 
{
    // Test: 10 -> 20 -> 15 (Zygzak)
    bin_tree root = newNode(10);
    root->right = newNode(20);
    root->right->left = newNode(15);

    fastryguj(root);

    // Sprawdzenie: next dla 10 powinien być 15
    if(root->next && root->next->val == 15) 
        printf("OK: 10 -> 15\n");
    else 
        printf("BLAD dla 10\n");

    return 0;
}