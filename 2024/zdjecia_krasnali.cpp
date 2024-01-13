#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 500'002;
vector<int> g[MAXN];
vector<int> g_sk[MAXN];
bool czy_na_kol[MAXN];
bool vis[MAXN];
int stop_wejs[MAXN];

bool czy_wszyt_izo(int n)
{
    for (int i = 1; i <= n; ++i) {
        if (g[i].size() != 0) return false;
    }
    return true;
}

bool czy1i2razem(int v)
{
    vis[v] = true;
    if (v == 2) return true;
    bool flag = false;
    for (int u : g[v]) {
        if (!vis[u]) {
            flag |= czy1i2razem(u);
        }
    }
    return flag;
}

int dfs_size(int v)
{
    vis[v] = true;
    int size = 1;
    for (int u : g[v]) {
        if (!vis[u]) {
            size += dfs_size(u);
        }
    }
    return size;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    if (czy_wszyt_izo(n)) {
        cout << "TAK\n";
        for (int i = 1; i <= n; ++i) cout << i << ' ';
        cout << '\n';
        return 0;
    }

    if (g[1].size() == 0 || g[2].size() == 0) {
        cout << "NIE\n";
        return 0;
    }
    if (!czy1i2razem(1)) {
        cout << "NIE\n";
        return 0;
    }
    for (int i = 1; i <= n; ++i) vis[i] = false;
    dfs_size(1);
    for (int i = 3; i <= n; ++i) {
        if (!vis[i]) {
            if (dfs_size(i) > 1) {
                cout << "NIE\n";
                return 0;
            }
        }
    }

    for (int i = 3; i <= n; ++i) {
        if (g[i].size() == 0) {
            g[i].push_back(1);
            g[1].push_back(i);

            g[i].push_back(2);
            g[2].push_back(i);
        }
    }

    for (int i = 1; i <= n; ++i) vis[i] = false;
    queue<int> ma_pol;
    ma_pol.push(1);
    czy_na_kol[1] = true;
    vis[1] = true;

    while (ma_pol.size()) {
        int v = ma_pol.front();
        czy_na_kol[v] = false;
        vis[v] = true;
        ma_pol.pop();
        for (int u : g[v]) {
            if (!vis[u]) {
                if (czy_na_kol[u]) {
                    cout << "NIE\n";
                    return 0;
                }
                g_sk[v].push_back(u);
                stop_wejs[u]++;
                if (stop_wejs[u] == g[u].size() / 2 && u != 2) {
                    ma_pol.push(u);
                    czy_na_kol[u] = true;
                }
                else if (stop_wejs[u] > g[u].size() / 2 && u != 2) {
                    cout << "NIE\n";
                    return 0;
                }
            }
        }
    }
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << ": ";
    //     for (int j : g_sk[i]) cout << j << ' ';
    //     cout << '\n';
    // }
    // return 0;
    for (int i = 3; i <= n; ++i) {
        if (!vis[i]) {
            cout << "NIE\n";
            return 0;
        }
    }

    queue<int> q;
    q.push(1);
    vector<int> topo;
    while(q.size())
    {
        int v = q.front();
        topo.push_back(v);
        q.pop();
        for (int u : g_sk[v]) {
            stop_wejs[u]--;
            if (stop_wejs[u] == 0) {
                q.push(u);
            }
        }
    }
    vector<int> res(n + 1);
    for (int i = 1; i <= n; ++i) {
        res[topo[i - 1]] = i;
    }
    cout << "TAK\n";
    for (int i = 1; i <= n; ++i) {
        cout << res[i] << ' ';
    }
    cout << '\n';

    return 0;
}