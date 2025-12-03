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
    // struct Node *prev;
} node; 

node* update(node *list1, node *list2)
{
    node *res = (node *)malloc(sizeof(node));
    node *curr1 = list1;
    node *curr2 = list2;
    int tick = 0;
    node *curr = res;
    while(curr1 != NULL || curr2 != NULL)
    {
        if(curr1 != NULL && (!tick || curr2 == NULL))
        {   
            curr->next = curr1;
            curr1 = curr1->next;
        }
        else
        {
            curr->next = curr2;
            curr2 = curr2->next;
        }
        tick^=1;
        curr = curr->next;
    }
    return res->next;
}

int main()
{
    node **list = (node**)malloc(5 * sizeof(node*));
    node **list2 = (node**)malloc(5 * sizeof(node*));
    for(int i=0;i<5;i++)
    {
        list[i] = (node*)malloc(sizeof(node));
        list2[i] = (node*)malloc(sizeof(node));
    }
        
    for(int i=0;i<5;i++)
    {
        list[i]->val = i;
        list2[i]->val = 10-i;
    }
    for(int i=0;i<4;i++)
    {
        list[i]->next = list[i+1];
        list2[i]->next = list2[i+1];
    }
    
    list[4]->next = NULL;
    list2[4]->next = NULL;
    
    node *tmp = update(list[0], list2[0]);
    for(int i=0;i<10;i++)
    {
        printf("%d ", tmp->val);
        tmp = tmp->next;
    }
    
    return 0;
}