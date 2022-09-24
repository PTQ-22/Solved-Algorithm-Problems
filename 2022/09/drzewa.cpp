#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2500 * 3;
vector<int> G[MAXN];
bool vis[MAXN];
int gen[MAXN];
int preorder[MAXN];
string naw;

int preCnt = 0;

void dfs(int v, int pred)
{
    ++preCnt;
    gen[preCnt] = pred;
    vis[v] = true;
    naw += '(';
    int x = preCnt;
    for (int u : G[v]) {
        if (!vis[u]) {
            dfs(u, x);
        }
    }
    naw += ')';
}

void addEdge(int a, int b)
{
    G[a].push_back(b);
    G[b].push_back(a);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> leaves(n + 1);
    int max_level = INT32_MIN;
    for (int i = 1; i <= n; ++i)
    {
        cin >> leaves[i].first;
        max_level = max(max_level, leaves[i].first);
    }

    int root = 0;
    for (int level = max_level; level >= 1; --level)
    {
        int cnt = 0;
        for (int i = 1; i < leaves.size(); ++i)
        {
            if (leaves[i].first == level)
            {
                cnt++;
            }
        }
        if (cnt % 2 == 1)
        {
            cout << "NIE";
            return 0;
        }

        for (int i = 1; i < leaves.size(); ++i)
        {
            if (leaves[i].first == level && leaves[i + 1].first == level)
            {
                root += 1;
                if (leaves[i].second)
                    addEdge(leaves[i].second, root + 2);
                else
                    addEdge(root, root + 2);
                if (leaves[i + 1].second)
                    addEdge(leaves[i + 1].second, root + 2);
                else
                    addEdge(root + 1, root + 2);
                root += 2;
                leaves.erase(leaves.begin() + i);
                leaves[i] = {level - 1, root};
            }
        }
    }

    dfs(root, 0);

    for (int i = 1; i <= 2 * n - 1; ++i) {
        cout << gen[i] << ' ';
    }
    cout << '\n';
    cout << naw;

    return 0;
}
