#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> g;
vector<int> dist;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    int cnt = 0;
    while (t--)
    {
        int N, E, T, M;
        cin >> N >> E >> T >> M;
        g.assign(N + 1, vector<pair<int, int>>());
        dist.assign(N + 1, INT32_MAX);

        for (int i = 0; i < M; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            g[b].emplace_back(a, c);
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[E] = 0;
        pq.emplace(0, E);
        while (pq.size()) {
            auto [d, v] = pq.top(); pq.pop();
            if (d > dist[v]) continue;
            for (auto [u, w] : g[v]) {
                if (dist[v] + w < dist[u] && dist[v] + w <= T) {
                    dist[u] = dist[v] + w;
                    pq.emplace(dist[u], u);
                }
            }
        }
        int res = 0;
        for (int i = 1; i <= N; ++i) {
            if (dist[i] != INT32_MAX) res++;
        }
        if (cnt++) cout << '\n';
        cout << res << '\n';
    }

    return 0;
}