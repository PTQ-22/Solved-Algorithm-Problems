#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int value;
        cin >> value;

        int n;
        cin >> n;

        vector<int> coins(n);
        for (int i = 0; i < n; ++i) {
            cin >> coins[i];
        }

        vector<int> dp(10001, INT16_MAX);
        dp[0] = 0;

        for (int c : coins) {
            for (int v = 10000; v > 0; --v) {
                if (v >= c) {
                    dp[v] = min(dp[v], dp[v - c] + 1);
                }
            }
        }     
        int i;  
        for (i = value; dp[i] == INT16_MAX; ++i);
        cout << i << ' ' << dp[i] << '\n';
    }

    return 0;
}