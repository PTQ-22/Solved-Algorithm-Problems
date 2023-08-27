#include <bits/stdc++.h>
using namespace std;

bool valid[101][101];
bool vis[101][101];
int even, odd;

void dfs(int i, int j, int R, int C, set<pair<int, int>>& moves)
{
    vis[i][j] = true;
    int cnt = 0;
    for (auto move : moves) {
        int y = move.first + i;
        int x = move.second + j;
        if (y < 0 || x < 0 || y >= R || x >= C) continue;
        if (valid[y][x]) {
            cnt++;
            if (!vis[y][x]) dfs(y, x, R, C, moves);
        }
    }
    if (cnt & 1) odd++;
    else even++;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    int cnt = 0;
    while (t--)
    {
        memset(valid, true, sizeof(valid));
        memset(vis, false, sizeof(vis));
        even = odd = 0;
        int R, C, M, N, W;
        cin >> R >> C >> M >> N >> W;
        for (int i = 0; i < W; ++i) {
            int x, y;
            cin >> x >> y;
            valid[x][y] = false;
            vis[x][y] = true;
        }
        set<pair<int, int>> moves = {{N, M}, {-N, M}, {N, -M}, {-N, -M},
                                        {M, N}, {-M, N}, {M, -N}, {-M, -N}};
        dfs(0, 0, R, C, moves);
        cout << "Case " << ++cnt << ": " << even << " " << odd << '\n';
    }

    return 0;
}