#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int l, g;
    while (cin >> l >> g, l > 0)
    {
        vector<pair<int, int>> stations(g);
        for (int i = 0; i < g; ++i) {
            int x, r;
            cin >> x >> r;
            stations[i] = {x - r, x + r};
        }
        sort(stations.begin(), stations.end());
        stations.emplace_back(INT32_MAX, INT32_MAX);

        int covered = 0;
        bool flag = false;
        int unused = 0;
        for (int i = 0; i < g; ++i) {
            if (stations[i].first > covered) {
                flag = true;
                continue;
            }
            int maxi = -1;
            for (int j = i; j <= g; ++j) {
                if (stations[j].first > covered) {
                    i = j - 1;
                    unused--;
                    break;
                }
                maxi = max(maxi, stations[j].second);
                unused++;
            }
            covered = maxi;
            if (covered >= l) {
                unused += (g - (i + 1));
                break;
            }
        }

        if (flag || covered < l) {
            cout << -1 << '\n';
            continue;
        }
        else {
            cout << unused << '\n';
        }
    }

    return 0;
}