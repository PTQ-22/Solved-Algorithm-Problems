#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100'000;
constexpr int SIZE = 2 * (MAXN + 2);
vector<pair<int, int>> G[SIZE];
bool vis[SIZE];
bool used[SIZE];
int it[SIZE];
vector<int> euler_cycle;

void euler(int v)
{
    vis[v] = true;
    for (; it[v] < G[v].size(); ++it[v])
    {
        int u = G[v][it[v]].first;
        int u_i = G[v][it[v]].second;
        if (!used[u_i]) {
            used[u_i] = true;
            euler(u);
        }
    }
    euler_cycle.push_back(v);
}

bool comp(pair<string, pair<int, int>>& a, pair<string, pair<int, int>>& b)
{
    return a.second.first < b.second.first;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    int a, b;
    unordered_map<string, pair<int, int>> hash_map;
    for (int i = 1; i <= k; ++i)
    {
        cin >> a >> b;
        b += MAXN;
        G[a].emplace_back(b, i);
        G[b].emplace_back(a, i);
        string key = to_string(a) + ' ' + to_string(b);
        hash_map[key] = {i, 0};
    }

    for (int i = 1; i < SIZE; ++i)
    {
        if (G[i].size() & 1)
        {
            cout << "NIE";
            return 0;
        }
    }

    cout << "TAK\n";

    int maxi = max(n, m);
    for (int i = 1; i <= maxi; ++i)
    {
        if (G[i].size() > 0 && !vis[i])
        {
            euler(i);
        }
    }

    for (int i = 1; i < euler_cycle.size(); ++i)
    {
        // cout << euler_cycle[i - 1] << ' '; 
        if ((euler_cycle[i - 1] < MAXN && euler_cycle[i] < MAXN) || (euler_cycle[i - 1] > MAXN && euler_cycle[i] > MAXN))
            continue;
        if (euler_cycle[i - 1] < MAXN)
        {
            string key = to_string(euler_cycle[i - 1]) + ' ' + to_string(euler_cycle[i]);
            hash_map[key].second = -1;
        }
        else {
            string key = to_string(euler_cycle[i]) + ' ' + to_string(euler_cycle[i - 1]);
            hash_map[key].second = 1;
        }
    }

    // cout << '\n';

    vector<pair<string, pair<int, int>>> res(hash_map.begin(), hash_map.end());
    sort(res.begin(), res.end(), comp);

    for (auto i : res)
    {
        cout << i.second.second << '\n';
        // cout << i.first << ' ' << i.second.second << '\n';
    }
    // for (auto it : hash_map)
    // {
    //     // cout << it.first << ' ' << it.second << '\n';
    //     // cout << it.second << '\n';
    // }

    return 0;
}
