#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100'002;
vector<int> G[MAXN];
bitset<MAXN> vis;
int pre[MAXN];
int low[MAXN];
int timer;

long long res[MAXN];

int dfs(int v, int p, int n)
{
    vis[v] = true;
    pre[v] = low[v] = ++timer;
    res[v] = (long long)2 * (n - 1);
    long long childrenSum = 0;
    int visited = 1;
    for (int u : G[v]) {
        if (u == p) continue;
        if (vis[u]) {
            low[v] = min(low[v], pre[u]);
        }
        else {
            int size = dfs(u, v, n);
            visited += size;
            low[v] = min(low[v], low[u]);
            if (low[u] >= pre[v]) {
                res[v] += (long long)(n - 1 - size) * (long long)size;
                childrenSum += (long long)size;
            }
        }
    }
    res[v] += (long long)(n - 1 - (long long)childrenSum) * (long long) childrenSum;
    return visited;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int a, b;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    timer = 0;
    dfs(1, -1, n);
    
    for (int v = 1; v <= n; ++v) {
        cout << res[v] << '\n';
    }
	
    return 0;
}
