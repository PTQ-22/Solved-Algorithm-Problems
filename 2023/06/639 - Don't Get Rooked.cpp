#include <bits/stdc++.h>
using namespace std;

bool canPlace(int i, int j, vector<string> &grid, int n)
{
    if (grid[i][j] == 'X') return false;
    for (int y = i + 1; y < n; ++y)
    {
        if (grid[y][j] == 'X')
            break;
        if (grid[y][j] == 'R')
            return false;
    }
    for (int y = i - 1; y >= 0; --y)
    {
        if (grid[y][j] == 'X')
            break;
        if (grid[y][j] == 'R')
            return false;
    }
    for (int x = j + 1; x < n; ++x)
    {
        if (grid[i][x] == 'X')
            break;
        if (grid[i][x] == 'R')
            return false;
    }
    for (int x = j - 1; x >= 0; --x)
    {
        if (grid[i][x] == 'X')
            break;
        if (grid[i][x] == 'R')
            return false;
    }
    return true;
}

vector<pair<int, int>> moves = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

vector<vector<string>> res;

void dfs(int i, int j, vector<string> grid, int n, vector<vector<bool>> vis, bool place)
{
    if (place)
        grid[i][j] = 'R';
    vis[i][j] = true;
    for (auto move : moves)
    {
        int y = i + move.first;
        int x = j + move.second;
        if (x < 0 || y < 0 || x == n || y == n)
            continue;
        if (vis[y][x])
            continue;

        dfs(y, x, grid, n, vis, false);
        if (canPlace(y, x, grid, n))
        {
            dfs(y, x, grid, n, vis, true);
        }
    }

    res.push_back(grid);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n, n > 0) {
        res.clear();
        vector<string> grid(n);
        vector<vector<bool>> vis(n, vector<bool>(n));
        for (int i = 0; i < n; ++i)
            cin >> grid[i];

        if (grid[0][0] != 'X')
            dfs(0, 0, grid, n, vis, true);
        dfs(0, 0, grid, n, vis, false);

        int maxi = -1;
        for (auto g : res)
        {
            int cnt = 0;
            for (string row : g) {
                // cout << row << '\n';
                for (char c : row) 
                    if (c == 'R') cnt++;
            }
            maxi = max(maxi, cnt);
            // cout << '\n';
        }
        cout << maxi << '\n';
    }
    return 0;
}
