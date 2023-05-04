#include <bits/stdc++.h>
using namespace std;

constexpr int BASE = 1 << 19;
int tree[BASE * 2];

void add(int v, int x)
{
    v += BASE;
    while (v > 0) {
        tree[v] += x;
        v /= 2;
    }
}

int query(int a, int b)
{
    a += (BASE - 1);
    b += (BASE + 1);
    int res = 0;
    while (a / 2 != b / 2) {
        if (!(a & 1)) res += tree[a + 1];
        if (b & 1) res += tree[b - 1];
        a /= 2;
        b /= 2;
    }
    return res;
}

constexpr int MAXN = 500'002;
vector<int> g[MAXN];
int new_nr[MAXN];
bitset<MAXN> vis;
int new_nr_parent[MAXN];
pair<int, int> children_segment[MAXN];

void bfs()
{
    int new_nr_cnt = 1;
    queue<int> Q;
    new_nr[1] = new_nr_cnt;
    vis[1] = true;
    Q.push(1);

    while(Q.size())
    {
        int v = Q.front(); Q.pop();
        bool first_flag = false;
        for (int u : g[v]) {
            if (!vis[u]) {
                vis[u] = true;
                Q.push(u);
                new_nr[u] = ++new_nr_cnt;

                new_nr_parent[u] = new_nr[v];
                if (!first_flag) children_segment[v].first = new_nr[u];
                first_flag = true;
                children_segment[v].second = new_nr[u];
            }
        }
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    bfs();
    int m;
    cin >> m;
    int trees = 1;
    while(m--)
    {
        int x;
        cin >> x;
        if (x > 0) {
            add(new_nr[x], 1);
            int cnt = query(new_nr_parent[x], new_nr_parent[x]) + query(children_segment[x].first, children_segment[x].second);
            trees += (g[x].size() - cnt - 1);
        }
        else {
            add(new_nr[-x], -1);
            int cnt = query(new_nr_parent[-x], new_nr_parent[-x]) + query(children_segment[-x].first, children_segment[-x].second);
            trees -= (g[-x].size() - cnt - 1);
        }
        cout << trees << '\n';
    }

    return 0;
}