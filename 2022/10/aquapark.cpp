// https://szkopul.edu.pl/problemset/problem/J4wIQqR4YCpTUr-d-in1DKnt/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1002;
int grid[2 * MAXN][2 * MAXN];
long long pr[2 * MAXN][2 * MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r;
    cin >> n >> r;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            cin >> grid[n - j + i][i + j - 1];
        }
    }

    for (int i = 1; i <= n * 2; ++i)
    {
        for (int j = 1; j <= n * 2; ++j)
        {
            pr[i][j] = grid[i][j] + pr[i][j - 1] + pr[i - 1][j] - pr[i - 1][j - 1];
        }
    }

    int a, b, l;
    while (r--)
    {
        cin >> a >> b >> l;
        int i = n - b + a;
        int j = a + b - 1;

        long long res = pr[min(i + l, n * 2)][min(j + l, n * 2)];
        res -= pr[min(i + l, n * 2)][max(j - l - 1, 0)];
        res -= pr[max(i - l - 1, 0)][min(j + l, n * 2)];
        res += pr[max(i - l - 1, 0)][max(j - l - 1, 0)];
        cout << res << '\n';
    }
    // 26 - 6 -
    // (2, 2) -> (5 - 2 + 2, 2-1 + 2-1 + 1)
    // (4, 5) -> (5 - 4 + 5, 3 + 4 + 1) -> (6, 8)

    // for (int i = 1; i <= n * 2; ++i)
    // {
    //     for (int j = 1; j <= n * 2; ++j)
    //     {
    //         cout << grid[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    return 0;
}
