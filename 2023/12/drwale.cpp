// https://szkopul.edu.pl/problemset/problem/fh8k3DcWsZB3OwD8rSLJw7SQ/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_S = 5'000'000 / 2 + 1;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int maxi = -1;
    vector<int> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i];
        maxi = max(maxi, all[i]);
    }
    vector<int> cnt(MAX_S);
    bool flag = false;
    for (int i = 0; i < n; ++i) {
        if (all[i] == maxi) {
            if (flag) cnt[all[i]]++;
            flag = true;
        }
        else {
            cnt[all[i]]++;
        }
    }
    bool change = true;
    while (change) {
        change = false;
        for (int i = 0; i < cnt.size() / 2; ++i) {
            if (cnt[i]) {
                if (cnt[i] > 2) {
                    int d = cnt[i] / 3; // 13 / 3 = 4
                    cnt[i] -= (d * 3); // 13 - 3 * 4 = 1
                    cnt[i] += d;
                    cnt[i * 2] += d;
                    change = true;
                }
            }
        }
    }
    int sum = 0;
    int m = 0;
    for (int i = 0; i < cnt.size(); ++i) {
        if (cnt[i]) {
            sum += (cnt[i] * i);
            m += cnt[i];
            // for (int j = 0; j < cnt[i]; j++) arr.push_back(i); 
        }
    }
    vector<int> arr(m);
    int it = 0;
    for (int i = 0; i < cnt.size(); ++i) {
        if (cnt[i]) {
            for (int j = 0; j < cnt[i]; j++) arr[it++] = i; 
        }
    }
    int S = sum / 2;
    bitset<MAX_S> dp;
    dp[0] = true;
    for (int i = 1; i <= m; ++i) {
        dp |= (dp << arr[i - 1]);
    }
    int closest = S;
    for (; closest >= 0; closest--) {
        if (dp[closest]) {
            break;
        }
    }
    cout << closest + maxi << '\n';

    return 0;
}