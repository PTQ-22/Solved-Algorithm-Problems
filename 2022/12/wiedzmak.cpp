#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int b;
    int w;
    int maskMonst;
};

constexpr int MAXN = 202;
constexpr int MAX2K = (1 << 14) + 1;
vector<Edge> G[MAXN];
int smith[MAXN];
int dist[MAXN][MAX2K];
bool vis[MAXN][MAX2K];

void dijkstra(int n)
{
    int mask = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int msk = 0; msk < MAX2K; ++msk)
        {
            dist[i][msk] = INT32_MAX;
        }
    }

    dist[1][mask] = 0;
    priority_queue<pair<int, pair<int, int>>> Q;
    Q.push({0, {1, mask}});
    while (Q.size())
    {
        int v = Q.top().second.first;
        int msk = Q.top().second.second;
        Q.pop();
        

        if (vis[v][msk]) continue;
        vis[v][msk] = true;
        
        int preMsk = msk;
        msk |= smith[v];
        dist[v][msk] = dist[v][preMsk];

        for (Edge e : G[v])
        {
            int u = e.b;
            int w = e.w;
            int monst = e.maskMonst;

            if ((msk & monst) != monst) {
                continue;
            }
            if (dist[v][msk] + w < dist[u][msk])
            {
                dist[u][msk] = dist[v][msk] + w;
                Q.push({-dist[u][msk], {u, msk}});
            }
        }
    }
    int mini = INT32_MAX;
    for (int msk = 0; msk < MAX2K; ++msk)
    {
        mini = min(mini, dist[n][msk]);
    }
    if (mini == INT32_MAX) cout << -1 << '\n';
    else cout << mini << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p, k;
    cin >> n >> m >> p >> k;

    for (int i = 0; i < k; ++i)
    {
        int w, q, r;
        cin >> w >> q;
        int mask = 0;
        while (q--)
        {
            cin >> r;
            mask |= (1 << r);
        }
        smith[w] |= mask;
    }

    for (int i = 0; i < m; ++i)
    {
        int v, w, t, s, u;
        cin >> v >> w >> t >> s;
        int mask = 0;
        while (s--)
        {
            cin >> u;
            mask |= (1 << u);
        }
        G[v].push_back({w, t, mask});
        G[w].push_back({v, t, mask});
    }
    dijkstra(n);

    return 0;
}