#include <bits/stdc++.h>
using namespace std;

int dfs(int v, vector<vector<pair<int, int>>>& g, vector<bool>& vis, int maxi)
{
    int res = 1;
    vis[v] = true;
    for (auto [u, w] : g[v]) {
        if (!vis[u] && w == maxi) {
            res += dfs(u, g, vis, maxi);
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m, n > 0)
    {
        vector<vector<pair<int, int>>> g(n + 1);
        vector<bool> vis(n + 1);
        int a, b, c;
        int maxi = INT32_MIN;
        vector<int> maxiVs;
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> c;
            g[a].emplace_back(b, c);
            g[b].emplace_back(a, c);
            if (maxi < c) {
                maxi = c;
                maxiVs.clear();
                maxiVs.push_back(a);
            }
            else if (maxi == c) maxiVs.push_back(a);
        }

        int res = -1;
        for (int v : maxiVs) res = max(dfs(v, g, vis, maxi), res);
        cout << res << '\n';

    }

    return 0;
}