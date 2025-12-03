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

struct node
{
    int val;
    bin_tree left, right, next;
};

int solve(std::vector<int> v)
{   
    int res = 0;
    sort(v.begin(), v.end());
    for(int i=0;i<v.size();i++)
    {
        int k = i + 2;
        for(int j=i+1,curr=0;j<v.size();j++)
        {
            if(v[i] + v[j] != v[k])
            {
                curr = 0;
                while(k < v.size() && v[i] + v[j] > v[k])
                {
                    k++;
                    curr=0;
                }
            }
            while(k < v.size() && v[i] + v[j] == v[k])
            {
                k++;
                curr++;
            }
            res += curr;
        }
    }
    return res;
}

void test(std::vector<int> input, int expected) {
    int result = solve(input);
    if (result == expected) {
        printf("[OK] Test passed. Result: %d\n", result);
    } else {
        printf("[FAIL] Test failed! Input size: %lu. Expected: %d, Got: %d\n", 
               input.size(), expected, result);
    }
}

int main() 
{
    printf("--- Uruchamianie testów ---\n");
    // Test 1: Przykład z zadania (obrazek)
    // 1+1=2, 1+4=5, 1+4=5 -> Razem 3
    test({4, 2, 1, 5, 8, 1}, 3);

    // Test 2: Prosty ciąg arytmetyczny
    // 1+2=3 -> Razem 1
    test({1, 2, 3}, 1);

    // Test 3: Duplikaty składników
    // 1+1=2 (pierwsza i druga 1 dają pierwszą 2)
    // 1+1=2 (pierwsza i druga 1 dają drugą 2)
    // Razem 2
    test({1, 1, 2, 2}, 2);

    // Test 4: Wielokrotne wystąpienie sumy (ta sama suma z różnych par)
    // 1+2=3, 1+2=3, 1+2=3 (dla każdej trójki)
    test({1, 2, 3, 3, 3}, 3);

    // Test 5: Brak rozwiązań
    test({1, 5, 10}, 0);

    // Test 6: Pusty wektor / za mały
    test({}, 0);
    test({1, 2}, 0);

    // Test 7: Duże liczby i "dziury"
    // 10+20=30
    test({10, 50, 20, 30}, 2);

    printf("--- Koniec testów ---\n");
    
    return 0;
}