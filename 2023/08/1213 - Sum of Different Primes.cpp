#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1121;
int dp[190][MAXN][15];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> primes = {-1}; // index from 1
    vector<bool> is_prime(MAXN, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAXN; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i; j < MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
    int num_p = primes.size();

    for (int i = 1; i < num_p; ++i) {
        for (int j = 1; j <= primes[i]; ++j) {
            if (j == primes[i] || dp[i - 1][j][1] == 1) {
                dp[i][j][1] = 1;
            }
        }
    }

    for (int i = 1; i < num_p; ++i) {
        for (int j = 1; j < MAXN; ++j) {
            for (int k = 2; k <= 14; ++k) {
                dp[i][j][k] += dp[i - 1][j][k];
                if (j >= primes[i]) {
                    dp[i][j][k] += (dp[i - 1][j - primes[i]][k - 1]);
                }
            }
        }
    }
    int n, k;
    while (cin >> n >> k, n > 0 && k > 0)
    {
        cout << dp[num_p - 1][n][k] << '\n';
    }

    return 0;
}