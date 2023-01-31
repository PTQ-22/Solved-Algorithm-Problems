#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1'000'002;
vector<pair<int, int>> GP[MAXN];
pair<int, int> edges[MAXN];
char type_of_edge[MAXN];
bitset<MAXN> vis;

void dfs(int v, int p_e_num)
{
    vis[v] = true;
    for (auto pa : GP[v]) {
        int u = pa.first;
        int e = pa.second;
        if (p_e_num != e && type_of_edge[e] == 'x') {
            if (edges[e].first == v) 
                type_of_edge[e] = '>';
            else 
                type_of_edge[e] = '<';
            if (!vis[u])
                dfs(u, e);
        }
    }
}

vector<int> G[MAXN];
vector<int> TG[MAXN];
int scc[MAXN];
vector<int> postorder;

void postDfs(int v)
{
    vis[v] = true;
    for (int u : G[v]) {
        if(!vis[u]) postDfs(u);
    }
    postorder.push_back(v);
}

void transpDfs(int v, int cnt)
{   
    scc[v] = cnt;
    for (int u : TG[v]) {
        if (!scc[u]) {
            transpDfs(u, cnt);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int a, b;
    for (int i = 1; i <= m; ++i) {
        type_of_edge[i] = 'x';
        cin >> a >> b;
        GP[a].emplace_back(b, i);
        GP[b].emplace_back(a, i);
        edges[i] = {a, b};
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) dfs(i, 0);
    }

    for (int i = 1; i <= m; ++i) {
        tie(a, b) = edges[i];
        if (type_of_edge[i] == '>') {
            G[a].push_back(b);
            TG[b].push_back(a);
        }
        else {
            G[b].push_back(a);
            TG[a].push_back(b);
        }
    }
    vis.reset();
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) postDfs(i);
    }
    reverse(postorder.begin(), postorder.end());
    int cnt = 0;
    for (int v : postorder) {
        if (!scc[v]) {
            transpDfs(v, ++cnt);
        }
    }
    cout << cnt << '\n';
    for (int i = 1; i <= m; ++i) cout << type_of_edge[i];
    cout << '\n';

    return 0;
}