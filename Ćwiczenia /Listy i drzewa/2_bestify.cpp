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

node* new_node(int val) {
    node* n = (node*)malloc(sizeof(node));
    n->val = val;
    n->lc = NULL;
    n->rc = NULL;
    return n;
}

void dfs(node *t)
{
    if(t == NULL)
        return;
    if(t->lc != NULL && t->lc->val > t->val)
    {
        node *tmp = t->lc;
        t->lc = t->rc;
        t->rc = tmp;
    }
    dfs(t->lc);
    dfs(t->rc);
}

void print_tree(node* t) {
    if (t) 
    {
        printf("%d ", t->val);
        print_tree(t->lc);
        print_tree(t->rc);
    }
}

int main() 
{
    node *root = new_node(10);
    root->lc = new_node(20); 
    root->rc = new_node(5);

    printf("Drzewo przed wywolaniem dfs (Pre-order): \n");
    print_tree(root);
    printf("\n");

    dfs(root);
    
    printf("Drzewo po wywolaniu dfs (Pre-order): \n");
    print_tree(root);
    printf("\n");

    free(root->lc);
    free(root->rc);
    free(root);
    return 0;
}