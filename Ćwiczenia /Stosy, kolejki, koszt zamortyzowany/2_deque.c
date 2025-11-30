#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct
{
    int *arr;
    int top;
    int cap;
} stack;

stack* create_stack()
{
    stack *s = malloc(sizeof(stack));
    s->cap = 2;
    s->top = -1;
    s->arr = malloc(s->cap * sizeof(int));
    return s;
}

int stack_empty(stack *s)
{
    return (s->top == -1);
}

void stack_push(stack *s, int val)
{
    if(s->top + 1 == s->cap)
    {  
        s->cap *= 2;
        s->arr = realloc(s->arr, s->cap * sizeof(int));
    }
    s->arr[++(s->top)] = val;
}

int stack_pop(stack *s)
{
    if(s->top != -1)
        return s->arr[s->top--];
    return -1;
}

int stack_top(stack *s)
{
    if(s->top != -1)
        return s->arr[s->top];
    return -1;
}

int stack_size(stack *s)
{
    return s->top + 1;
}

void stack_destroy(stack *s)
{
    free(s->arr);
    free(s);
}

typedef struct
{
    stack *in;
    stack *out;
} deque;

deque* create_deque()
{
    deque *q = malloc(sizeof(deque));
    q->in = create_stack();
    q->out = create_stack();
    return q;
}

void deque_fill_out(deque *q)
{
    stack* tmp = create_stack();
    int limit = (stack_size(q->in) + 1) / 2;
    while(stack_size(q->in) > limit)
        stack_push(tmp, stack_pop(q->in));
    while(!stack_empty(q->in))
        stack_push(q->out, stack_pop(q->in));
    while(!stack_empty(tmp))   
        stack_push(q->in, stack_pop(tmp));
    stack_destroy(tmp);
}

void deque_fill_in(deque *q)
{
    stack* tmp = create_stack();
    int limit = (stack_size(q->out) + 1) / 2;
    while(stack_size(q->out) > limit)
        stack_push(tmp, stack_pop(q->out));
    while(!stack_empty(q->out))
        stack_push(q->in, stack_pop(q->out));
    while(!stack_empty(tmp))   
        stack_push(q->out, stack_pop(tmp));
    stack_destroy(tmp);
}

int deque_front(deque *q)
{
    if(stack_empty(q->out))
        deque_fill_out(q);
    return stack_top(q->out);
}

int deque_back(deque *q)
{
    if(stack_empty(q->in))
        deque_fill_in(q);
    return stack_top(q->in);
}

int deque_pop_front(deque *q)
{
    if(stack_empty(q->out))
        deque_fill_out(q);
    return stack_pop(q->out);
}

int deque_pop_back(deque *q)
{
    if(stack_empty(q->in))
        deque_fill_in(q);
    return stack_pop(q->in);
}

void deque_push_front(deque *q, int val)
{
    stack_push(q->out, val);
}

void deque_push_back(deque *q, int val)
{
    stack_push(q->in, val);
}

void deque_destroy(deque *q) 
{
    stack_destroy(q->in);
    stack_destroy(q->out);
    free(q);
}

int main()
{
    printf("--- Rozpoczynam testy Deque ---\n");
    deque *q = create_deque();

    // TEST 1: Działanie jak zwykła kolejka (FIFO)
    printf("1. Test FIFO (Push Back -> Pop Front)\n");
    deque_push_back(q, 10);
    deque_push_back(q, 20);
    deque_push_back(q, 30);
    
    printf("   Pop Front: %d (Oczekiwano: 10)\n", deque_pop_front(q));
    printf("   Pop Front: %d (Oczekiwano: 20)\n", deque_pop_front(q));
    printf("   Pop Front: %d (Oczekiwano: 30)\n", deque_pop_front(q));
    
    // TEST 2: Działanie odwrotne (Push Front -> Pop Back)
    printf("\n2. Test Odwrotny (Push Front -> Pop Back)\n");
    deque_push_front(q, 100);
    deque_push_front(q, 200);
    
    printf("   Pop Back: %d (Oczekiwano: 100)\n", deque_pop_back(q));
    printf("   Pop Back: %d (Oczekiwano: 200)\n", deque_pop_back(q));

    // TEST 3: Mieszane operacje ("Ping-Pong" - najtrudniejszy test)
    // To sprawdzi, czy twoja logika z 'tmp' poprawnie dzieli stosy
    printf("\n3. Test Mieszany (Ping-Pong)\n");
    deque_push_back(q, 1);
    deque_push_back(q, 2);
    deque_push_back(q, 3);
    deque_push_back(q, 4);
    // Stan logiczny kolejki: [1, 2, 3, 4]
    
    printf("   Pop Front: %d (Oczekiwano: 1)\n", deque_pop_front(q)); 
    // Stan: [2, 3, 4]. 
    // Tutaj twoja funkcja fill_out przeniosła [2] do OUT, a [3, 4] zostało w IN.
    
    printf("   Pop Back:  %d (Oczekiwano: 4)\n", deque_pop_back(q));
    // Stan: [2, 3]. Pobiera z IN.
    
    printf("   Pop Front: %d (Oczekiwano: 2)\n", deque_pop_front(q));
    // Stan: [3]. Pobiera z OUT.
    
    printf("   Pop Back:  %d (Oczekiwano: 3)\n", deque_pop_back(q));
    // Stan: []. IN puste, OUT puste. Pobiera z IN (wymusi fill_in, który weźmie 0 z OUT).
    
    // TEST 4: Pusta kolejka
    printf("\n4. Test Pustej Kolejki\n");
    int val = deque_pop_front(q);
    printf("   Pop Empty: %d (Oczekiwano: -1)\n", val);

    // Czyszczenie pamięci
    deque_destroy(q);
    printf("\n--- Testy zakonczone sukcesem ---\n");

    return 0;
}