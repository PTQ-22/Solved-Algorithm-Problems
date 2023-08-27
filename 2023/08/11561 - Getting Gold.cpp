#include <bits/stdc++.h>
using namespace std;

#define vs vector<string>
#define vvb vector<vector<bool>>

int moves[] = {-1, 0, 1};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> m >> n)
    {
        vs grid(n);
        vvb vis(n, vector<bool>(m));
        for (int i = 0; i < n; ++i) cin >> grid[i];


        int res = 0;
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < m; ++j) {
                
                if (grid[i][j] == 'P') {
                    
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    vis[i][j] = true;

                    while(q.size())
                    {
                        auto v = q.front(); q.pop();
                        if (grid[v.first][v.second] == 'G') {
                            res++;
                        }
                        int isMoving = true;
                        queue<pair<int, int>> tmp;
                        for (int dy : moves) {
                            for (int dx : moves) {
                                if (dy == 0 || dx == 0) {
                                    int y = dy + v.first;
                                    int x = dx + v.second;
                                    if (grid[y][x] == '#') continue;
                                    if (vis[y][x]) continue;
                                    if (grid[y][x] == 'T') {
                                        isMoving = false;
                                        break;
                                    }
                                    vis[y][x] = true;
                                    tmp.push({y, x});
                                }
                            }
                            if (!isMoving) break;
                        }
                        if (isMoving) {
                            while (tmp.size()) {
                                q.push(tmp.front());
                                tmp.pop();
                            }
                        }
                        else {
                            while (tmp.size()) {
                                auto v = tmp.front();
                                vis[v.first][v.second] = false;
                                tmp.pop();
                            }
                        }
                    }


                }

            }
        cout << res << '\n';
    }

    return 0;
}