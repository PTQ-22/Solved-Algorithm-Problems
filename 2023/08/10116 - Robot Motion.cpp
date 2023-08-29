#include <bits/stdc++.h>
using namespace std;

pair<int, int> dfs(int i, int j, int pre, vector<string>& grid, vector<vector<int>>& vis, int n, int m)
{
    vis[i][j] = pre + 1;
    switch (grid[i][j]) {
        case 'N': i--; break;
        case 'S': i++; break;
        case 'E': j++; break;
        case 'W': j--; break;
    }
    if (i < 0 || j < 0 || i == n || j == m) return {pre + 1, 0};
    if (vis[i][j]) return {vis[i][j] - 1, pre + 1 - (vis[i][j] - 1)};
    return dfs(i, j, pre + 1, grid, vis, n, m);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, start;
    while (cin >> n >> m >> start, n > 0)
    {
        start--;
        vector<string> grid(n);
        vector<vector<int>> vis(n, vector<int>(m));

        for (int i = 0; i < n; ++i) cin >> grid[i];

        auto x = dfs(0, start, 0, grid, vis, n, m);
        if (x.second) {
            cout << x.first << " step(s) before a loop of " << x.second << " step(s)\n";
        }
        else {
            cout << x.first << " step(s) to exit\n";
        }
        // for (int i = 0; i < n; ++i) {
        //     for (int j = 0; j < m; ++j) cout << vis[i][j] << ' ';
        //     cout << '\n';
        // }
    }

    return 0;
}