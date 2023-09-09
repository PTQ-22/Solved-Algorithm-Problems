#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g, gt, scc;
vector<bool> vis;
vector<int> postorder;

void dfsPost(int v)
{
    vis[v] = true;
    for (int u : g[v]) if (!vis[u]) dfsPost(u);
    postorder.push_back(v);
}

void dfsScc(int v, int scc_num)
{
    vis[v] = true;
    scc[scc_num].push_back(v);
    for (int u : gt[v]) if (!vis[u]) dfsScc(u, scc_num);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int caseCnt = 0;
    while (cin >> n >> m, n > 0)
    {
        g.assign(n + 1, vector<int>());
        gt.assign(n + 1, vector<int>());
        map<string, int> number;
        map<int, string> name;
        int name_cnt = 0;
        for (int i = 1; i <= m; ++i) {
            string s1, s2;
            cin >> s1 >> s2;
            if (!number[s1]) {
                number[s1] = ++name_cnt;
                name[number[s1]] = s1;
            }
            if (!number[s2]) {
                number[s2] = ++name_cnt;
                name[number[s2]] = s2;
            }
            g[number[s1]].push_back(number[s2]);
            gt[number[s2]].push_back(number[s1]);
        }

        vis.assign(n + 1, false);
        postorder.clear();

        for (int i = 1; i <= n; ++i) if (!vis[i]) dfsPost(i);


        vis.assign(n + 1, false);
        reverse(postorder.begin(), postorder.end());
        scc.assign(n + 1, vector<int>());

        int scc_num = 0;
        for (int v : postorder) {
            if (!vis[v]) dfsScc(v, ++scc_num);
        }
        
        if (caseCnt) cout << '\n';
        cout << "Calling circles for data set "<< ++caseCnt <<":\n";
        for (auto s : scc) {
            if (s.size() && m > 0) {
                cout << name[s[0]];
                for (int i = 1; i < s.size(); ++i) {
                    cout << ", " << name[s[i]];
                }
                cout << '\n';
            }
        }
    }

    return 0;
}