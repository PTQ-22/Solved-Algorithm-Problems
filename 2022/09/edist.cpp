#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        string A, B;
        cin >> A >> B;
        vector<vector<int>> dp(A.size() + 1, vector<int>(B.size() + 1, 0));
        for (int i = 1; i <= A.size(); ++i)
        {
            dp[i][0] = i;
        }
        for (int i = 1; i <= B.size(); ++i)
        {
            dp[0][i] = i;
        }

        for (int i = 1; i <= A.size(); ++i)
        {
            for (int j = 1; j <= B.size(); ++j)
            {
                dp[i][j] = min(dp[i][j - 1] + 1, dp[i - 1][j] + 1);
                if (A[i - 1] == B[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
        cout << dp[A.size()][B.size()] << '\n';
    }
}