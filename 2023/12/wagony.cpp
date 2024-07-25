// https://szkopul.edu.pl/problemset/problem/UtJx9fM6UT2oxXFenSPjiz5C/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

long long n;
long long d;
unsigned long long a, b;

inline unsigned long long f(unsigned long long w, unsigned long long u)
{
    return (a * w + b * u) % 1001ULL;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d >> a >> b;
    map<long long, unsigned long long> dp;
    dp[0] = dp[1] = 0;
    for (long long dw = 1; dw <= n; dw *= 2) {
        for (long long x = max(2LL, n / dw - d); x <= n / dw + d; x++) {
            dp[x] = UINT64_MAX;
        }
    }

    for (auto [x, val] : dp) {
        auto it = dp.find(max(1LL, (x - d) / 2));
        for (long long i = max(1LL, (x - d) / 2); i <= min(x, (x + d) / 2); ++i) {
            long long j = x - i;
            if (abs(i - j) <= d) {
                if (i == x) val = min(val, val + dp[j] + f(i, j));
                else val = min(val, it->second + dp[j] + f(i, j));
            }
            it++;
        }
        dp[x] = val;
    }
    cout << dp[n] << '\n';

    return 0;
}