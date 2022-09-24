// https://codeforces.com/contest/279/problem/B
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;

    vector<int> times(n + 1);
    vector<int> pref(n + 1);

    pref[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin >> times[i];
        pref[i] = pref[i - 1] + times[i];
    }

    int maxi = 0;
    int p1 = 1;
    int p2 = 1;

    while (p1 <= n && p2 <= n)
    {
        if (pref[p1] - pref[p2 - 1] <= t) {
            maxi = max(maxi, p1 - p2 + 1);
            p1++;
        }
        else {
            p2++;
        }
    }

    cout << maxi;

    return 0;
}
