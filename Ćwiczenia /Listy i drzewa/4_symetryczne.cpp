#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct node
{
    int val;
    struct node *lc;
    struct node *rc;
} node;

int i=0;

node* new_node(int val)
{
    node* n = (node*)malloc(sizeof(node));
    n->val = val;
    n->lc = NULL;
    n->rc = NULL;
    return n;
}

int init(node *v)
{
    if(v == NULL)
        return 0;
    return 1 + init(v->lc) + init(v->rc);
}

void dfs(node *v, int *arr, int mode)
{
    if(v == NULL)
    {
        arr[i++] = 0;
        return;
    }
    arr[i++] = v->val;
    if(mode == 1)
    {
        dfs(v->lc, arr, mode);
        dfs(v->rc, arr, mode);
    }
    else
    {
        dfs(v->rc, arr, mode);
        dfs(v->lc, arr, mode);
    }
}

bool solve(node *t)
{
    int n = init(t);
    int *left = (int*)calloc(2*n, sizeof(int));
    int *right = (int*)calloc(2*n, sizeof(int));
    i=0; dfs(t->lc, left, 0);
    i=0; dfs(t->rc, right, 1);
    for(int i=0;i<n;i++)
        if(left[i] != right[i])
            return 0;
    return 1;
}
int main() 
{
    printf("--- TEST 1: Drzewo Symetryczne ---\n");
    //      1
    //     / \
    //    2   2
    //   / \ / \
    //  3  4 4  3
    node *root1 = new_node(1);
    root1->lc = new_node(2);
    root1->rc = new_node(2);
    root1->lc->lc = new_node(3);
    root1->lc->rc = new_node(4);
    root1->rc->lc = new_node(4);
    root1->rc->rc = new_node(3);
    
    if(solve(root1)) printf("Wynik: SYMETRYCZNE (Poprawnie)\n");
    else printf("Wynik: NIESYMETRYCZNE (Blad)\n");

    printf("\n--- TEST 2: Drzewo Niesymetryczne (Wartosci) ---\n");
    //      1
    //     / \
    //    2   2
    //   /     \
    //  3       5  <-- rozna wartosc
    node *root2 = new_node(1);
    root2->lc = new_node(2);
    root2->rc = new_node(2);
    root2->lc->lc = new_node(3);
    root2->rc->rc = new_node(5); 

    if(solve(root2)) printf("Wynik: SYMETRYCZNE (Blad)\n");
    else printf("Wynik: NIESYMETRYCZNE (Poprawnie)\n");

    printf("\n--- TEST 3: Drzewo Niesymetryczne (Struktura) ---\n");
    //      1
    //     / \
    //    2   2
    //     \   \
    //      3   3 <-- obie trojki po prawej stronie
    node *root3 = new_node(1);
    root3->lc = new_node(2);
    root3->rc = new_node(2);
    root3->lc->rc = new_node(3); // Prawy syn
    root3->rc->rc = new_node(3); // Prawy syn

    if(solve(root3)) printf("Wynik: SYMETRYCZNE (Blad)\n");
    else printf("Wynik: NIESYMETRYCZNE (Poprawnie)\n");

    return 0;
}