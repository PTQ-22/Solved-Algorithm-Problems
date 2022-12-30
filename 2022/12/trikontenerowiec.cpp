#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    //          h   val
    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; ++i)
    {
        int val, h;
        cin >> val >> h;
        arr[i] = {h, val};
    }
    sort(arr.begin(), arr.end());

    priority_queue<int> pq;

    int i = 0;
    int64_t res = 0;
    for (int h = 1; h <= m; ++h)
    {
        if (i < n)
        {
            pair<int, int> curr = arr[i];
            while (curr.first == h && i - 1 < n)
            {
                pq.push(curr.second);
                curr = arr[++i];
            }
        }
        if (pq.size())
        {
            res += pq.top();
            pq.pop();
        }
    }
    cout << res << '\n';

    return 0;
}