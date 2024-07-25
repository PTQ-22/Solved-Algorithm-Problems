// https://szkopul.edu.pl/problemset/problem/R6kgLB2Xz3fsLFYKA-4P9fzp/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 250'002; 
vector<int> G[MAXN];
int height[MAXN];
pair<int, int> segment[MAXN];
int preorder[MAXN];
int preCnt = 0;

int dfs(int v, int p)
{
    preorder[v] = ++preCnt;
    height[preorder[v]] = height[preorder[p]] + 1;
    int maxi = preorder[v];
    for (int u : G[v])
    {
        if (u != p)
        {
            maxi = max(maxi, dfs(u, v));
        }
    }
    segment[preorder[v]] = {preorder[v], maxi};
    return maxi;
}

constexpr int BASE = 1 << 18;
int tree[BASE * 2];

void add(int a, int b, int x)
{
    a += (BASE - 1);
    b += (BASE + 1);
    while (a / 2 != b / 2)
    {
        if (a % 2 == 0)
        {
            tree[a + 1] += x;
        }
        if (b % 2 == 1)
        {
            tree[b - 1] += x;
        }
        a /= 2;
        b /= 2;
    }
}

int query(int v)
{
    v += BASE;
    int res = 0;
    while (v > 0)
    {
        res += tree[v];
        v /= 2;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int a, b;
    for (int i = 1; i < n; ++i)
    {
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs(1, 1);

    int m;
    cin >> m;
    char x;
    for (int i = 0; i < n + m - 1; ++i)
    {
        cin >> x;
        if (x == 'W')
        {
            cin >> a;
            int v = preorder[a];
            cout << height[v] - query(v) - 1 << '\n';
        }
        else
        {
            cin >> a >> b;
            int v = preorder[b];
            add(segment[v].first, segment[v].second, 1);
        }
    }

    return 0;
}
