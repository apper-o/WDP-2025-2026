#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct Node{
    int val;
    struct Node *next;
    struct Node *prev;
} node; 

void update(node *list)
{
    node *curr = list; 
    while(curr != NULL)
    {
        node *nxt = curr->next;
        node *new_node = (node *)malloc(sizeof(node));
        curr->next = new_node;
        new_node->prev = curr;
        new_node->val = curr->val;
        if(nxt != NULL)
        {
            new_node->next = nxt;
            nxt->prev = new_node;
        }
        curr = nxt;
    }
}

int main()
{   
    node **head = (node**)malloc(5 * sizeof(node*));
    for(int i=0;i<5;i++)
        head[i] = (node*)malloc(sizeof(node));
    for(int i=0;i<5;i++)
        head[i]->val = i;
    for(int i=0;i<4;i++)
        head[i]->next = head[i+1];
    for(int i=1;i<5;i++)
        head[i]->prev = head[i-1];
    head[0]->prev = NULL;
    head[4]->next = NULL;

    update(head[0]);

    // Sprawdzenie wyniku (0 0 1 1 2 2 3 3 4 4)
    node *tmp = head[0];
    while(tmp != NULL)
    {
        printf("%d ", tmp->val);
        tmp = tmp->next;
    }
    
    return 0;
}