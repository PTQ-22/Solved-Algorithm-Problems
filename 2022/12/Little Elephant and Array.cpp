#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> arr(n + 1);
    unordered_map<int, int> occ;
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
        occ[arr[i]]++;
    }

    int k = 1;
    vector<int> candidates = {0};
    for (auto x : occ)
    {
        if (x.first <= x.second)
        {
            candidates.push_back(x.first);
            k++;
        }
    }
    vector<vector<int>> pref(candidates.size() + 1, vector<int>(n + 1));
    for (int j = 1; j < candidates.size(); ++j)
    {
        pref[j][1] = arr[1] == candidates[j] ? 1 : 0;
        for (int i = 2; i <= n; ++i)
        {
            pref[j][i] = pref[j][i - 1] + (arr[i] == candidates[j] ? 1 : 0);
        }
    }
    while (q--)
    {
        int l, r;
        cin >> l >> r;

        int res = 0;
        for (int j = 1; j < candidates.size(); ++j)
        {
            int currOcc = pref[j][r] - pref[j][l - 1];
            if (currOcc == candidates[j])
                res++;
        }
        cout << res << '\n';
    }

    return 0;
}