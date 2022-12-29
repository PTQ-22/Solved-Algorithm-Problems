// https://codeforces.com/gym/101853/submission/187050012
#include <bits/stdc++.h>
using namespace std;

int sumFromRow(int i, int mask, vector<vector<int>> &arr)
{
    int res = 0;
    for (int k = 0; (1 << k) <= mask; k++)
    {
        if ((1 << k) & mask)
        {
            res += arr[i][k];
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--)
    {
        int n;
        cin >> n;
        vector<vector<int>> arr(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> arr[i][j];
            }
        }

        vector<int> legalMasks;
        for (int mask = 0; mask < (1 << n); ++mask)
        {
            if (!(mask & (mask << 1)))
            {
                legalMasks.push_back(mask);
            }
        }

        vector<vector<int>> dp(n, vector<int>(1 << n));
        for (int mask : legalMasks)
        {
            dp[0][mask] = sumFromRow(0, mask, arr);
        }
        for (int i = 1; i < n; ++i)
        {
            for (int mask1 : legalMasks)
            {
                for (int mask2 : legalMasks)
                {
                    if (!(mask1 & (mask2 | (mask2 << 1) | (mask2 >> 1))))
                    {
                        dp[i][mask1] = max(dp[i][mask1], dp[i - 1][mask2] + sumFromRow(i, mask1, arr));
                    }
                }
            }
        }

        int maxi = 0;
        for (int mask : legalMasks)
        {
            maxi = max(maxi, dp[n - 1][mask]);
        }
        cout << maxi << '\n';
    }

    return 0;
}