// https://szkopul.edu.pl/problemset/problem/e5LK9PxWitOX0_1ujs123Gjq/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(2 * n);

    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        sum += arr[i];
        if (i != n) arr[i + n] = arr[i];
    }

    int p = 1;
    int k = 2;
    int seg_sum = arr[1];
    int res = -1;
    while (p <= n && k <= 2 * n) {
        res = max(res, min(seg_sum, sum - seg_sum));
        if (seg_sum < sum - seg_sum) {
            seg_sum += arr[k];
            k++;
        }
        else {
            seg_sum -= arr[p];
            p++;
        }
    }
    cout << res << '\n';

    return 0;
}