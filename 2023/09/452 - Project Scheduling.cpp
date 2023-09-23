#include <bits/stdc++.h>
using namespace std;


void dfs(int v, vector<bool>& vis, vector<vector<int>>& g, vector<int>& topo)
{
    vis[v] = true;
    for (int u : g[v]) {
        if (!vis[u]) dfs(u, vis, g, topo);
    }
    topo.push_back(v);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    cin.ignore();
    string line;
    getline(cin, line);
    while (t--)
    {
        vector<vector<int>> g(27, vector<int>()), preds(27, vector<int>());
        vector<int> dist(27);
        vector<int> in_deg(27, 0);
        int n = 0;
        while (getline(cin, line), line != "")
        {
            n++;
            stringstream ss = stringstream(line);
            string aa, val, sas;
            ss >> aa;
            int a = aa[0] - 'A' + 1;
            ss >> val;
            dist[a] = -(stoi(val));
            if (ss >> sas) {
                in_deg[a] = sas.size();
                for (char c : sas) {
                    g[c - 'A' + 1].push_back(a);
                    preds[a].push_back(c - 'A' + 1);
                }
            }
        }
        vector<int> topo;
        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (in_deg[i] == 0) {
                topo.push_back(i);
                q.push(i);
            }
        }
        while (q.size())
        {
            int v = q.front(); q.pop();
            for (int u : g[v]) {
                --in_deg[u];
                if (in_deg[u] == 0) {
                    topo.push_back(u);
                    q.push(u);
                }
            }
        }
        
        for (int v : topo) {
            int mini = 0;
            for (int p : preds[v]) {
                mini = min(mini, dist[p]);
            }
            dist[v] += mini;
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) res = max(res, -dist[i]);
        cout << res << '\n';
        if (t) cout << '\n';
    }

    return 0;
}