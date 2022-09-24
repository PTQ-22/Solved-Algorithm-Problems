// https://szkopul.edu.pl/problemset/problem/fYXVXOreVxlXTRoHZJXyXF2l/site/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> diameters(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> diameters[i];
    }

    for (int i = 1; i < n; ++i)
    {
        diameters[i] = min(diameters[i], diameters[i - 1]);
    }

    reverse(diameters.begin(), diameters.end());

    // for (int i : diameters) cout << i << ' ';
    // cout << '\n';

    int block = 0;
    int puck;
    while (m--)
    {
        cin >> puck;
        auto up = lower_bound(diameters.begin() + block, diameters.end(), puck);
        int pos = up - diameters.begin();
        // cout << pos << ' ';
        // res = min(res, n - pos);
        block = pos + 1;
    }
    if (n - block + 1 < 0)
        cout << 0;
    else
        cout << n - block + 1;

    return 0;
}
