#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

const int n = 8;

bool valid(int y, int x)
{
    return (min(x, y) >= 0 && max(x, y) <= 7);
}

int get_moves(int y, int x, int arr[8][8], vector<pair<int, int>> moves)
{
    if (!valid(y, x) || arr[y][x] == 1)
        return -1;
    int res = 0;
    for (auto [dx, dy] : moves)
        res += (valid(y + dy, x + dx) && arr[y + dy][x + dx] == 0);
    return res;
}

bool solve(int x, int y, int sum, int arr[n][n], vector<pair<int, int>> moves, vector<pair<int, int>> &res)
{
    arr[y][x] = 1;
    res.push_back({x, y});
    if (res.size() == sum)
        return 1;
    vector<pair<int, pair<int, int>>> pos;

    for (auto [dx, dy] : moves)
    {
        int tmp = get_moves(y + dy, x + dx, arr, moves);
        if (tmp >= 0)
            pos.push_back({tmp, {x + dx, y + dy}});
    }
    sort(pos.begin(), pos.end(), [](pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
         { return a.first < b.first; });
    for (auto [cnt, t] : pos)
        if (solve(t.first, t.second, sum, arr, moves, res))
            return 1;
    arr[y][x] = 0;
    res.pop_back();
    return 0;
}

int main()
{
    // Wejscie: Szachownica, gdzie zablokowane pola to 1, a puste to 0
    int sum = 64;
    int arr[8][8];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
            sum -= arr[i][j];
        }
    vector<pair<int, int>> moves = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    vector<pair<int, int>> res;

    for (int x = 0; x < n; x++)
        for (int y = 0; y < n; y++)
            if (arr[y][x] == 0 && solve(x, y, sum, arr, moves, res))
            {
                for (auto [a, b] : res)
                    cout << a << " " << b << "\n";
                return 0;
            }
    return 0;
}