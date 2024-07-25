// https://szkopul.edu.pl/problemset/problem/eQ4z7Bnhqsl67nKb_NlISLNZ/site/?key=statement
// Piotr Kowalczyk
#include <bits/stdc++.h>
using namespace std;

vector<int> idxs;
bool check(vector<pair<int, int>>& buttons, int n, int m)
{
    vector<int> sum_row(n + 1), sum_col(n + 1);
    for (int v : idxs) {
        auto [r, c] = buttons[v + 1];
        sum_row[r]++;
        sum_col[c]++;
    }
    int mod = sum_row[1] % 2;
    for (int i = 1; i <= n; ++i) {
        if (sum_col[i] % 2 != mod || sum_row[i] % 2 != mod) {
            return false;
        }
    }
    return true;
}

void brut(vector<pair<int, int>>& buttons, int n, int m)
{
    int W = 1 << m;
    for (int i = 0; i < W; ++i)
    {
        idxs.clear();
        for (int j = 0; j < m; ++j)
        {
            if (i & (1 << j))
            {
                idxs.push_back(j);
            }
        }
        if (idxs.size() && check(buttons, n, m)) {
            cout << "TAK\n";
            cout << idxs.size() << '\n';
            for (int x : idxs) cout << x + 1 << ' ';
            cout << '\n';
            return;
        }
    }
    cout << "NIE\n";
}

// vector<int> cycle;
// vector<int> cycle_stack;
// bool cycle_check(int v, int p, vector<vector<pair<int, int>>>& g, vector<bool>& vis)
// {
//     vis[v] = true;
//     cycle_stack.push_back(v);
//     for (auto [u, nr] : g[v]) {
//         if (!vis[u]) {
//             if (cycle_check(u, v, g, vis)) {
//                 return true;
//             }
//         }
//         else if (u != p) {
//             bool flag = true;
//             // cout << cycle_stack.size() << '\n';
//             // while (cycle_stack.size()) {
//             //     int x = cycle_stack.top();
//             //     cycle_stack.pop();
//             //     if (x != u && flag) {
//             //         continue;
//             //     }
//             //     flag = false;
//             //     // cycle.push_back(x);
//             // }
//             cout << cycle_stack.size() << '\n';
//             for (int x : cycle_stack) {
//                 if (x != u && flag) {
//                     continue;
//                 }
//                 flag = false;
//                 cycle.push_back(x);
//             }
//             return true;
//         }
//     }
//     cycle_stack.pop_back();
//     return false;
// }

vector<int> cycle;
void cycle_check(int v, int p, vector<int>& color, vector<int>& par, int& cyclenumber, vector<vector<pair<int, int>>>& g)
{
    if (color[v] == 2) {
        return;
    }
    if (color[v] == 1) {
        // vector<int> v;
        if (cyclenumber) return;
        cyclenumber++;
           
        int cur = p;
        //   v.push_back(cur);
        cycle.push_back(cur);
 
        while (cur != v) {
            cur = par[cur];
            cycle.push_back(cur);
            //   v.push_back(cur);
        }
        //   cycles.push_back(v);
        return;
    }
    par[v] = p;
    color[v] = 1;
 
    for (auto p : g[v]) {
        int u = p.first;
        if (u == par[v]) {
            continue;
        }
        cycle_check(u, v, color, par, cyclenumber, g);
    }
    color[v] = 2;
}

int dfs(int v, vector<vector<pair<int, int>>>& g, vector<bool>& vis, int& res, vector<bool>& off)
{
    vis[v] = true;
    int currComponentNode = 0;
    for (int i = 0; i < g[v].size(); ++i)
    {   
        auto [u, nr] = g[v][i];
        if (!vis[u])
        {

            int subtreeNodeCount = dfs(u, g, vis, res, off);
            if (subtreeNodeCount % 2 == 0) {
                res++;
                off[nr] = true;
            }
            else
                currComponentNode += subtreeNodeCount;
        }
    }
    return (currComponentNode + 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(2 * (n + 1), vector<pair<int, int>>());
    vector<bool> vis(2 * (n + 1), false);
    vector<int> color(2 * (n + 1), 0);
    vector<int> par(2 * (n + 1), 0);
    vector<bool> off(m + 1, false);
    vector<vector<int>> g2(2 * (n + 1), vector<int>());
    vector<pair<int, int>> input(m + 1);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        input[i] = {a, b};
    }

    for (int i = 1; i <= m; ++i) {
        int a = input[i].first;
        int b = input[i].second;
        g[a].emplace_back(b + n, i);
        g[b + n].emplace_back(a, i);
    }

    // // 
    // cout << g.size() << '\n';
    // cout << "X\n";
    // return 0;
    // //
    bool flag = false;
    for (int i = 1; i <= 2 * n; ++i) {
        if (!color[i]) {
            // if (cycle_check(i, i, g, vis)) {
            int num = 0;
            cycle_check(i, 0, color, par, num, g);
            if (num) {
                flag = true;
                break;
            }
            // }
        }
    }
    if (flag) {
        vector<int> res;
        cycle.push_back(cycle.front());
        for (int i = 1; i < cycle.size(); ++i) {
            for (auto [u, nr] : g[cycle[i - 1]]) {
                if (u == cycle[i]) {
                    res.push_back(nr);
                }
            }
        }
        cout << "TAK\n";
        cout << res.size() << '\n';
        for (int x : res) cout << x << ' ';
        cout << '\n';
    }
    else {
        vis.assign(vis.size(), false);

        for (int i = 1; i <= 2 * n; ++i) {
            if (g[i].size() == 0) {
                cout << "NIE\n";
                return 0;
            } 
        }

        int rem = 0;
        for (int i = 1; i <= 2 * n; ++i) {
            if (!vis[i])
                dfs(i, g, vis, rem, off);
        }
        for (int i = 1; i <= m; ++i) {
            if (!off[i]) {
                auto [a, b] = input[i];
                g2[a].push_back(b + n);
                g2[b + n].push_back(a);
            }
        }
        for (int i = 1; i <= 2 * n; ++i) {
            if (g2[i].size() % 2 == 0) {
                cout << "NIE\n";
                return 0;
            }
        }

        cout << "TAK\n";
        cout << m - rem << '\n';
        for (int i = 1; i <= m; ++i) {
            if (!off[i]) {
                cout << i << ' ';
            }
        }
        cout << '\n';
    }


    return 0;
}