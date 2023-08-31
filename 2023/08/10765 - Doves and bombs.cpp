#include <bits/stdc++.h>
using namespace std;

struct Station {
    int arct_point;
    int pigeons;
    int num;

    bool operator<(const Station& other) const {
        if (arct_point > other.arct_point) return true;
        else if (arct_point < other.arct_point) return false;
        else {
            if (pigeons > other.pigeons) return true;
            else if (pigeons < other.pigeons) return false;
            else {
                return num < other.num;
            }
        }
    }
};

vector<vector<int>> g;
vector<int> dfs_num, dfs_low, divided;
vector<bool> arct_point;
int dfs_cnt, root_children;

void dfs(int v, int p)
{
    dfs_num[v] = dfs_low[v] = ++dfs_cnt;
    for (int u : g[v]) {
        if (!dfs_num[u]) {
            if (v == 0) root_children++;
            dfs(u, v);

            if (dfs_num[v] <= dfs_low[u]) {
                divided[v]++;
                arct_point[v] = true;
            }
            dfs_low[v] = min(dfs_low[v], dfs_low[u]);
        }
        else if (u != p) {
            dfs_low[v] = min(dfs_low[v], dfs_num[u]);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m, n > 0)
    {
        g.assign(n, vector<int>());
        dfs_num.assign(n, 0);
        dfs_low.assign(n, 0);
        divided.assign(n, 1);
        arct_point.assign(n, false);
        dfs_cnt = root_children = 0;
        int a, b;
        while (cin >> a >> b, a != -1) {
            g[a].push_back(b);
            g[b].push_back(a);
        }
        divided[0] = 0;
        dfs(0, -1);

        vector<Station> stations(n);
        for (int i = 0; i < n; ++i) {
            stations[i].num = i;
            stations[i].pigeons = divided[i];
            stations[i].arct_point = arct_point[i] ? 1 : 0;
        }
        sort(stations.begin(), stations.end());
        for (int i = 0; i < m; ++i) {
            cout << stations[i].num << ' ' << stations[i].pigeons << '\n';
        }
        cout << '\n';
    }

    return 0;
}