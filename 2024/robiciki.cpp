// https://szkopul.edu.pl/c/mistrz-programowania-2024/p/r4d/
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
constexpr int MAXN = 5002;
vector<int> g[MAXN];
ull umiej[MAXN];
bool vis[MAXN];

pair<ull, int> dfs(int v)
{
    vis[v] = true;
    ull val = umiej[v];
    int size = 1;
    for (int u : g[v]) {
        if (!vis[u]) {
            auto [vl, sz] = dfs(u);
            val += vl;
            size += sz;
        }
    }
    return {val, size};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> umiej[i];
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<ull> vals = {0LL};
    vector<int> sizes = {0};
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            auto [val, size] = dfs(i);
            vals.push_back(val);
            sizes.push_back(size);
        }
    }

    int num = vals.size() - 1;
    vector<vector<ull>> dp(num + 1, vector<ull>(k + 1));

    for (int i = 1; i <= num; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (sizes[i] > j) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - sizes[i]] + vals[i]);
            }
        }
    }
    cout << dp[num][k] << '\n';

    return 0;
}