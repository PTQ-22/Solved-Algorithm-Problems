#include <bits/stdc++.h>
using namespace std;

long long merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right)
{
    long long inv_cnt = 0;

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];

            inv_cnt += (long long)(mid - i + 1);
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int i = left; i <= right; ++i) arr[i] = temp[i];
    return inv_cnt;
}

long long mergeSort(vector<int>& arr, vector<int>& temp, int left, int right)
{
    long long inv_cnt = 0;
    if (left < right) {
        int mid = (left + right) / 2;
        
        inv_cnt += mergeSort(arr, temp, left, mid);
        inv_cnt += mergeSort(arr, temp, mid + 1, right);

        inv_cnt += merge(arr, temp, left, mid, right);
    }
    return inv_cnt;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n, n > 0)
    {
        vector<int> arr(n), temp(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        long long inv_cnt = mergeSort(arr, temp, 0, n - 1);
        cout << inv_cnt << '\n';
    }    

    return 0;
}