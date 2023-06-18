#include <bits/stdc++.h>
using namespace std;

bool check(vector<int>& arr, int k)
{
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] - arr[i - 1] > k) return false;
        if (arr[i] - arr[i - 1] == k) k--;
    }
    return true;
}

int bin_search(vector<int>& arr)
{
    int start = 1;
    int end = arr.back();
    while (start < end)
    {
        int mid = (start + end) / 2;
        if (check(arr, mid)) {
            end = mid;
        }
        else {
            start = mid + 1;
        }
    }
    return start;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    int cnt = 0;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> arr(n + 1);
        arr[0] = 0;
        for (int i = 1; i <= n; ++i) cin >> arr[i];
        printf("Case %d: %d\n", ++cnt, bin_search(arr));
    }

    return 0;
}