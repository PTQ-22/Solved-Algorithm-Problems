#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
        vector<vector<int>> g(200 + 1);
        vector<bool> vis(200 + 1);
        vector<int> color(200 + 1);
        for (int i = 1; i <= n; ++i) {
            int p, a;
            cin >> p;
            while (p--) {
                cin >> a;
                if (a > n) continue;
                g[a].push_back(i);
                g[i].push_back(a);
            }
        }   
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) {
                
                queue<int> q;
                vector<int> curr = {i};
                q.push(i);
                vis[i] = true;
                bool poss = true;
                while (q.size()) {
                    int v = q.front(); q.pop();
                    for (int u : g[v]) {
                        if (!vis[u]) {
                            q.push(u);
                            curr.push_back(u);
                            vis[u] = true;
                            color[u] = 1 - color[v];
                        }
                        else if (color[u] == color[v]) {
                            poss = false;
                        }
                    }
                }
                if (!poss) continue;
                int zeros = 0, ones = 0;
                for (int v : curr) {
                    if (color[v]) ones++;
                    else zeros++;
                }
                res += max(zeros, ones);
            }
        }
        cout << res << '\n';
    }    

    return 0;
}