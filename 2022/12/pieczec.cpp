#include <bits/stdc++.h>
using namespace std;

bool check(int n, int m, vector<string> &toCheck, vector<pair<int, int>> &instr)
{
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (toCheck[i][j] == 'x' && !vis[i][j])
            {
                vis[i][j] = true;
                pair<int, int> p = {i, j};
                for (auto x : instr)
                {
                    p = {p.first + x.first, p.second + x.second};

                    if (p.first < 0 || p.first >= n || p.second < 0 || p.second >= m)
                        return false;
                    if (vis[p.first][p.second])
                        return false;
                    if (toCheck[p.first][p.second] == '.')
                        return false;
                    vis[p.first][p.second] = true;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (toCheck[i][j] == 'x' && !vis[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    while (q--)
    {
        int n, m, a, b;
        cin >> n >> m >> a >> b;

        vector<string> toCheck(n);
        for (int i = 0; i < n; ++i)
            cin >> toCheck[i];

        vector<string> seal(a);
        for (int i = 0; i < a; ++i)
            cin >> seal[i];

        vector<pair<int, int>> instr;
        pair<int, int> pred = {-1, -1};
        for (int i = 0; i < a; ++i)
        {
            for (int j = 0; j < b; ++j)
            {
                if (seal[i][j] == 'x')
                {
                    if (pred == make_pair(-1, -1))
                    {
                        pred = {i, j};
                    }
                    else
                    {
                        pair<int, int> neww;
                        neww.first = i - pred.first;
                        neww.second = j - pred.second;
                        instr.push_back(neww);
                        pred = {pred.first + neww.first, pred.second + neww.second};
                    }
                }
            }
        }
        if (check(n, m, toCheck, instr))
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }

    return 0;
}