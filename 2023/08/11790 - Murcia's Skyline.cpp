#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    int caseCnt = 0;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> heights(n), widths(n);
        for (int i = 0; i < n; ++i) cin >> heights[i];
        for (int i = 0; i < n; ++i) cin >> widths[i];

        vector<int> lis_dp(widths);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (heights[j] < heights[i]) {
                    lis_dp[i] = max(lis_dp[i], lis_dp[j] + widths[i]);
                }
            }
        }
        int lis = -1;
        for (int i = 0; i < n; ++i) lis = max(lis, lis_dp[i]);

        vector<int> lds_dp(widths);
        lds_dp[0] = widths[0];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (heights[j] > heights[i]) {
                    lds_dp[i] = max(lds_dp[i], lds_dp[j] + widths[i]);
                }
            }
        }
        int lds = -1;
        for (int i = 0; i < n; ++i) lds = max(lds, lds_dp[i]);

        cout << "Case " << ++caseCnt << ". ";
        if (lis >= lds) {
            cout << "Increasing (" << lis << "). Decreasing (" << lds << ").\n";
        }
        else {
            cout << "Decreasing (" << lds << "). Increasing (" << lis << ").\n";
        }
    }
    

    return 0;
}