#include <bits/stdc++.h>
using namespace std;

pair<int, int> moves[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int bfs(int X, int Y, vector<string> &grid, vector<vector<bool>>& vis, int M, int N, char landLetter)
{
    int res = 1;
    queue<pair<int, int>> q;
    q.push({X, Y});
    vis[X][Y] = true;
    while (q.size())
    {
        auto [x, y] = q.front();
        q.pop();
        for (auto [dx, dy] : moves)
        {
            int i = x + dx;
            int j = y + dy;
            if (i < 0 || i == M)
                continue;
            if (j < 0)
                j = N - 1;
            if (j == N)
                j = 0;
            if (vis[i][j] || grid[i][j] != landLetter)
                continue;

            q.push({i, j});
            vis[i][j] = true;
            res++;
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    while (cin >> M >> N)
    {
        vector<string> grid(M);
        vector<vector<bool>> vis(M, vector<bool>(N));
        for (int i = 0; i < M; ++i)
            cin >> grid[i];

        int X, Y;
        cin >> X >> Y;

        char landLetter = grid[X][Y];
        int res = 0;
        bfs(X, Y, grid, vis, M, N, landLetter);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == landLetter && !vis[i][j]) {
                    res = max(res, bfs(i, j, grid, vis, M, N, landLetter));
                } 
            }
        }
        cout << res << '\n';
    }

    return 0;
}