#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1001;
int price[MAXN];
int weight[MAXN];

int memo[MAXN][101];
int n;

int dp(int idx, int rem_cap)
{
    if (idx == n + 1 || rem_cap == 0) return 0;
    if (memo[idx][rem_cap] != -1) return memo[idx][rem_cap];
    if (weight[idx] > rem_cap) return memo[idx][rem_cap] = dp(idx + 1, rem_cap);
    return memo[idx][rem_cap] = max(dp(idx + 1, rem_cap), price[idx] + dp(idx + 1, rem_cap - weight[idx]));
}

// int knacksack(int capacity)
// {
//     for (int i = 0; i <= n; ++i) for (int j = 0; j < 101; ++j) dp[i][j] = 0;

//     for (int i = 1; i <= n; ++i)
//         for (int j = 1; j <= capacity; ++j)
//             if (weight[i] > j) 
//                 dp[i][j] = dp[i - 1][j];
//             else
//                 dp[i][j] = max(dp[i - 1][j], price[i] + dp[i - 1][j - weight[i]]);
//     return dp[n][capacity];
// }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i <= n; ++i) for (int j = 0; j < 101; ++j) memo[i][j] = -1;

        for (int i = 1; i <= n; ++i) {
            cin >> price[i] >> weight[i];
        }
        int g;
        cin >> g;
        int res = 0;
        for (int i = 0; i < g; ++i) {
            int capacity;
            cin >> capacity;
            res += dp(0, capacity);
        }
        cout << res << '\n';
    }

    return 0;
}