#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1001;
int grid[MAXN][MAXN];
int dist[MAXN][MAXN];
int moves[] = {-1, 0, 1};
map<pair<int, int>, int> direction = {
    {{-1, 0}, 0},
    {{-1, 1}, 1},
    {{0, 1}, 2},
    {{1, 1}, 3},
    {{1, 0}, 4},
    {{1, -1}, 5},
    {{0, -1}, 6},
    {{-1, -1}, 7}};

int bfs(pair<int, int> start, pair<int, int> end, int n, int m)
{
    deque<pair<int, int>> q = {start};
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) dist[i][j] = INT32_MAX;
    dist[start.first][start.second] = 0;

    while (q.size())
    {
        auto p = q.front();
        q.pop_front();
        for (int di : moves)
        {
            for (int dj : moves)
            {
                if (di == 0 && dj == 0)
                    continue;
                int i = di + p.first;
                int j = dj + p.second;
                if (i == 0 || j == 0 || i > n || j > m)
                    continue;

                int w = (grid[p.first][p.second] == direction[{di, dj}]) ? 0 : 1;
                if (dist[p.first][p.second] + w < dist[i][j])
                {
                    dist[i][j] = dist[p.first][p.second] + w;
                    if (w)
                        q.push_back({i, j});
                    else
                        q.push_front({i, j});
                }
            }
        }
    }

    return dist[end.first][end.second];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string line;
    for (int i = 1; i <= n; ++i)
    {
        cin >> line;
        for (int j = 1; j <= m; ++j)
        {
            grid[i][j] = line[j - 1] - '0';
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        int rs, cs, rd, cd;
        cin >> rs >> cs >> rd >> cd;
        cout << bfs({rs, cs}, {rd, cd}, n, m) << '\n';
    }

    return 0;
}