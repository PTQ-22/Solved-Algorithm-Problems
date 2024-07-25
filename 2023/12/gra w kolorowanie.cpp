// https://szkopul.edu.pl/problemset/problem/BefzQSkyOOBhuycp8gvD8XdG/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 500'002;
vector<int> g[MAXN];
int subtree[MAXN];
int parent[MAXN];
int dist[MAXN];
int which_centr[MAXN];
int n;
set<int> A, B;

class SegTree {
    int base;
    vector<int> tree;
public:
    SegTree(int n)
    {
        base = 1 << int(ceil(log2(n)));
        tree.assign(2 * base, 0);
    }

    void add(int v, int x)
    {
        v += base;
        while (v > 0) {
            tree[v] += x;
            v /= 2;
        }
    }

    int query(int a, int b)
    {
        a += (base - 1);
        b += (base + 1);
        int res = 0;
        while (a / 2 != b / 2) {
            if (!(a & 1)) {
                res += tree[a + 1];
            }
            if (b & 1) {
                res += tree[b - 1];
            }
            a /= 2;
            b /= 2;
        }
        return res;
    }

    void print()
    {
        for (int i = 0; i <= n; ++i) {
            cout << i << ": " << query(i, i) << '\n';
        }
    }
};

void bfs(int centroid1, int centroid2)
{
    for (int i = 1; i <= n; ++i) dist[i] = -1;
    queue<int> q;
    q.push(centroid1);
    dist[centroid1] = 0;
    which_centr[centroid1] = 1;
    while (q.size())
    {
        int v = q.front(); 
        q.pop();
        for (int u : g[v]) {
            if (dist[u] == -1 && u != centroid2) {
                dist[u] = dist[v] + 1;
                which_centr[u] = 1;
                q.push(u);
            }
        }
    }
    if (centroid2 != -1) {
        q.push(centroid2);
        dist[centroid2] = 0;
        which_centr[centroid2] = 2;
        while (q.size())
        {
            int v = q.front(); 
            q.pop();
            for (int u : g[v]) {
                if (dist[u] == -1 && u != centroid1) {
                    dist[u] = dist[v] + 1;
                    which_centr[u] = 2;
                    q.push(u);
                }
            }
        }
    }
}

void dfs(int v, int p)
{
    subtree[v] = 1;
    parent[v] = p;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            subtree[v] += subtree[u];
        }
    }
}

int find_centroid(int v)
{
    for (int u : g[v]) {
        if (u == parent[v]) {
            if (n - subtree[v] > (n) / 2) return find_centroid(u);
        }
        else if (subtree[u] > (n) / 2) {
            return find_centroid(u);
        }
    }
    return v;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int Sa, Sb, q;
    cin >> Sa >> Sb >> q;
    for (int i = 0; i < Sa; ++i) {
        int x;
        cin >> x;
        A.insert(x);
    }
    for (int i = 0; i < Sb; ++i) {
        int x;
        cin >> x;
        B.insert(x);
    }

    dfs(1, 0);
    int centroid1 = find_centroid(1);
    int centroid2 = -1;
    if (n % 2 == 0) {
        for (int u : g[centroid1]) {
            if (subtree[u] == n / 2) centroid2 = u;
        }
    }

    bfs(centroid1, centroid2);
    SegTree atree(n), btree(n);
    SegTree aToCent2(n), bToCent2(n);

    for (int a : A) {
        atree.add(dist[a], 1);
        if (which_centr[a] == 2) {
            aToCent2.add(dist[a], 1);
        }
    }
    for (int b : B) {
        btree.add(dist[b], 1);
        if (which_centr[b] == 2) {
            bToCent2.add(dist[b], 1);
        }
    }
    // cout << centroid1 << ' ' << centroid2 << '\n';

    long long res = 0;
    for (int a : A) {
        res += btree.query(dist[a] + 1, n);
        int same = btree.query(dist[a], dist[a]);
        if (B.find(a) != B.end()) same--;
        if (same) {
            if (which_centr[a] == 1) {
                int oposite = bToCent2.query(dist[a], dist[a]);
                same -= oposite;
            }
            else if (which_centr[a] == 2) {
                int oposite = btree.query(dist[a], dist[a]) - bToCent2.query(dist[a], dist[a]);
                same -= oposite;
            }
        }
        res += same;
    }

    cout << res << '\n';    
    while (q--) {
        char zb, zn;
        int w;
        cin >> zb >> zn >> w;

        if (zb == 'A') {
            if (zn == '+') {
                A.insert(w);
                atree.add(dist[w], 1);
                if (which_centr[w] == 2) {
                    aToCent2.add(dist[w], 1);
                }

                res += btree.query(dist[w] + 1, n);
                int same = btree.query(dist[w], dist[w]);
                if (B.find(w) != B.end()) same--;
                if (same) {
                    if (which_centr[w] == 1) {
                        int oposite = bToCent2.query(dist[w], dist[w]);
                        same -= oposite;
                    }
                    else if (which_centr[w] == 2) {
                        int oposite = btree.query(dist[w], dist[w]) - bToCent2.query(dist[w], dist[w]);
                        same -= oposite;
                    }
                }
                res += same;
            }
            else {
                A.erase(w);
                atree.add(dist[w], -1);
                if (which_centr[w] == 2) {
                    aToCent2.add(dist[w], -1);
                }

                res -= btree.query(dist[w] + 1, n);
                int same = btree.query(dist[w], dist[w]);
                if (B.find(w) != B.end()) same--;
                if (same) {
                    if (which_centr[w] == 1) {
                        int oposite = bToCent2.query(dist[w], dist[w]);
                        same -= oposite;
                    }
                    else if (which_centr[w] == 2) {
                        int oposite = btree.query(dist[w], dist[w]) - bToCent2.query(dist[w], dist[w]);
                        same -= oposite;
                    }
                }
                res -= same;
            }
        }

        else {
            if (zn == '+') {
                B.insert(w);
                btree.add(dist[w], 1);
                if (which_centr[w] == 2) {
                    bToCent2.add(dist[w], 1);
                }

                res += atree.query(0, dist[w] - 1);
                int same = atree.query(dist[w], dist[w]);
                if (A.find(w) != A.end()) same--;
                if (same) {
                    if (which_centr[w] == 1) {
                        int oposite = aToCent2.query(dist[w], dist[w]);
                        same -= oposite;
                    }
                    else if (which_centr[w] == 2) {
                        int oposite = atree.query(dist[w], dist[w]) - aToCent2.query(dist[w], dist[w]);
                        same -= oposite;
                    }
                }
                res += same;
            }

            else {
                B.erase(w);
                btree.add(dist[w], -1);
                if (which_centr[w] == 2) {
                    bToCent2.add(dist[w], -1);
                }

                res -= atree.query(0, dist[w] - 1);
                int same = atree.query(dist[w], dist[w]);
                if (A.find(w) != A.end()) same--;
                if (same) {
                    if (which_centr[w] == 1) {
                        int oposite = aToCent2.query(dist[w], dist[w]);
                        same -= oposite;
                    }
                    else if (which_centr[w] == 2) {
                        int oposite = atree.query(dist[w], dist[w]) - aToCent2.query(dist[w], dist[w]);
                        same -= oposite;
                    }
                }
                res -= same;
            }
        }
        cout << res << '\n';    
    }

    return 0;
}