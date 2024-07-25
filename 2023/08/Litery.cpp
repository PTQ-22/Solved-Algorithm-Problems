// https://szkopul.edu.pl/problemset/problem/V1PYHlhJQGTY6KR5ODoTTYU4/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

long long merge(vector<int>& arr, vector<int>& temp, int start, int mid, int end)
{
    long long cnt = 0;

    int i = start;
    int j = mid + 1;
    int k = start;

    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
            cnt += (mid - i + 1);
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= end) temp[k++] = arr[j++];
    for (i = start; i <= end; ++i) arr[i] = temp[i];
    return cnt;
}

long long mergeSort(vector<int>& arr, vector<int>& temp, int start, int end)
{
    long long cnt = 0;
    if (start < end) {
        int mid = (start + end) / 2;
        
        cnt += mergeSort(arr, temp, start, mid);
        cnt += mergeSort(arr, temp, mid + 1, end);
        cnt += merge(arr, temp, start, mid, end);
    }  
    return cnt; 
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string jan, malg;
    cin >> jan >> malg;

    vector<queue<int>> correctPos(26);

    for (int i = 0; i < n; ++i) {
        correctPos[jan[i] - 'A'].push(i);
    }

    vector<int> arr(n), temp(n);

    for (int i = 0; i < n; ++i) {
        arr[i] = correctPos[malg[i] - 'A'].front();
        correctPos[malg[i] - 'A'].pop();
    }
    cout << mergeSort(arr, temp, 0, n - 1) << '\n';

    return 0;
}