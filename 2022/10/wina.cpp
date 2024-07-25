// https://szkopul.edu.pl/c/olimpiada-od-podstaw-2022-23/problemset/problem/T-F5dZGgu3pmKAzGdWUfoHy6/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2002;
vector<int> wines[MAXN];
vector<int> dist[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
    {
        wines[i].resize(i + 1);
        dist[i].resize(i + 1);
        for (int j = 1; j <= i; ++j)
        {
            cin >> wines[i][j];
        }
    }

    dist[0].resize(1);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i / 2 + 1; ++j) 
        {
            dist[i][j] = dist[i - 1][j] + j;
            dist[i][i - j + 1] = dist[i - 1][j] + j;
        }
    }

    int res = INT32_MAX;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j) 
        {
            if (dist[i][j] <= k) {
                res = min(res, wines[i][j]);
            }
        }
    }

    cout << res;

    return 0;
}
