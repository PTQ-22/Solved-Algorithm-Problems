#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> g, gt;
vector<int> dist, distT;
vector<bool> vis;

// int dfs(int v, int s)
// {
//     int res = 0;
//     vis[v] = true;
//     if (v == s) return 0;
//     for (auto [u, w]: gt[v]) {
//         res = max(res, w);
//         if (!vis[u]) res = max(res, dfs(u, s));
//     }
//     cout << res << '\n';
//     return res;
// }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int n, m, s, t, p;
        cin >> n >> m >> s >> t >> p;

        g.assign(n + 1, vector<pair<int, int>>());
        gt.assign(n + 1, vector<pair<int, int>>());
        dist.assign(n + 1, INT32_MAX);
        distT.assign(n + 1, INT32_MAX);
        vis.assign(n + 1, false);

        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a].emplace_back(b, c);
            gt[b].emplace_back(a, c);
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, s);
        dist[s] = 0;
        bool poss = false;
        while(pq.size()) {
            auto [d, v] = pq.top(); pq.pop();
            if (d > dist[v]) continue;
            if (v == t) {
                poss = true;
            }
            for (auto [u, w] : g[v]) {
                if (dist[v] + w <= p) {
                    if (dist[v] + w < dist[u]) {
                        dist[u] = dist[v] + w;
                        pq.emplace(dist[u], u);
                    }
                }
            }
        }
        if (!poss) {
            cout << -1 << '\n';
        }
        else {
            // cout << dfs(t, s) << '\n';
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq2;
            pq2.emplace(0, t);
            distT[t] = 0;
            while(pq2.size()) {
                auto [d, v] = pq2.top(); pq2.pop();
                if (d > distT[v]) continue;
                for (auto [u, w] : gt[v]) {
                    if (distT[v] + w <= p) {
                        if (distT[v] + w < distT[u]) {
                            distT[u] = distT[v] + w;
                            pq2.emplace(distT[u], u);
                        }
                    }
                }
            }
            int res = 0;
            for (int v = 1; v <= n; ++v) {
                if (dist[v] == INT32_MAX) continue;
                for (auto [u, w] : g[v]) {
                    if (distT[u] == INT32_MAX) continue;
                    if (dist[v] + w + distT[u] <= p) res = max(res, w);
                }
            }
            cout << res << '\n';
        }
    }

    return 0;
}