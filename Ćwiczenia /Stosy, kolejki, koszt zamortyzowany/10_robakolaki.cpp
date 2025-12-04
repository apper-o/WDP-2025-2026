#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

int robakolak(const std::vector<int> &r)
{
    std::queue<int> q, q2;
    for(int i=0;i<r.size();i++)
        q.push(r[i]);
    int x[2] = {0, 0};
    while(q.size() + q2.size() + (x[0] != 0) > 1)
    {
        if(x[0] == 0)
        {
            if(q2.empty() || (q.size() && q.front() < q2.front()))
            {
                x[0] = q.front();
                q.pop();
            }
            else
            {
                x[0] = q2.front();
                q2.pop();
            }
        }
        if(q2.empty() || q.front() < q2.front())
        {
            x[1] = q.front();
            q.pop();
        }
        else
        {
            x[1] = q2.front();
            q2.pop();
        }
        if(x[0] == x[1])
        {
            x[0]--;
            x[1] = 0;
        }
        else
        {
            q2.push(x[0] + x[1] - 1);
            x[0]=x[1]=0;
        }
    }
    return (q.size() ? q.front() : q2.size() ? q2.front() : x[0]);
}

int main() {
    // Test 1: Przykład z różnymi wagami
    std::vector<int> t1 = {2, 3, 5};
    // 2 walczy z 3 -> wygrywa 3, nowa waga 2+3-1 = 4. Zostają {4, 5}.
    // 4 walczy z 5 -> wygrywa 5, nowa waga 4+5-1 = 8.
    // Wynik: 8.
    std::cout << "Test 1 (2, 3, 5) -> " << robakolak(t1) << " (Oczekiwano: 8)" << std::endl;

    // Test 2: Przykład z równymi wagami
    std::vector<int> t2 = {2, 2, 5};
    // 2 walczy z 2 -> zostaje 1 (wyczerpany). Zostają {1, 5}.
    // 1 walczy z 5 -> wynik 1+5-1 = 5.
    // Wynik: 5.
    std::cout << "Test 2 (2, 2, 5) -> " << robakolak(t2) << " (Oczekiwano: 5)" << std::endl;

    // Test 3: Same dwójki
    std::vector<int> t3 = {2, 2, 2, 2};
    // 2 vs 2 -> 1. Zostają {1, 2, 2}.
    // 1 vs 2 -> 1+2-1 = 2. Zostają {2, 2} (jeden z q_out, jeden z q_in).
    // 2 vs 2 -> 1.
    // Wynik: 1.
    std::cout << "Test 3 (2, 2, 2, 2) -> " << robakolak(t3) << " (Oczekiwano: 1)" << std::endl;

    // Test 4: Większe liczby
    std::vector<int> t4 = {10, 10, 20};
    // 10 vs 10 -> 9. Zostaje {9, 20}.
    // 9 vs 20 -> 28.
    std::cout << "Test 4 (10, 10, 20) -> " << robakolak(t4) << " (Oczekiwano: 28)" << std::endl;

    return 0;
}