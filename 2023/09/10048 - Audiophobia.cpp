#include <bits/stdc++.h>
using namespace std;


class DSU {
    vector<int> set_size, rep;
public:
    DSU(int n) : set_size(n + 1, 1), rep(n + 1) {
        for (int i = 1; i <= n; ++i) rep[i] = i;
    }

    int find(int a) {
        if (rep[a] == a) return a;
        return rep[a] = find(rep[a]);
    }

    void join(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (set_size[b] > set_size[a]) swap(a, b);
        set_size[a] += set_size[b];
        rep[b] = a;
    }
};

int dfs(int v, int p, int res, int end, vector<vector<pair<int, int>>>& g)
{
    if (v == end) return res;
    int to_pass = -1;
    for (auto [u, w] : g[v]) {
        if (u != p) {
            to_pass = max(dfs(u, v, max(res, w), end, g), to_pass);
        }
    }
    return to_pass;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseCnt = 0;
    int n, m, q;
    while (cin >> n >> m >> q, n > 0)
    {
        vector<tuple<int, int, int>> edges(m);
        vector<vector<pair<int, int>>> g(n + 1);
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            edges[i] = {c, a, b};
        }
        sort(edges.begin(), edges.end());

        DSU dsu = DSU(n);
        for (auto [w, a, b] : edges) {
            if (dsu.find(a) == dsu.find(b)) continue;
            dsu.join(a, b);
            g[a].emplace_back(b, w);
            g[b].emplace_back(a, w);
        }
        if (caseCnt) cout << '\n';
        cout << "Case #" << ++caseCnt << '\n';
        for (int i = 0; i < q; ++i) {
            int s, t;
            cin >> s >> t;
            int res = dfs(s, -1, -1, t, g);
            if (res == -1) cout << "no path\n";
            else cout << res << '\n';
        }
    }

    return 0;
}