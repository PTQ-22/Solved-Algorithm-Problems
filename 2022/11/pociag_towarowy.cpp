// https://sio2.mimuw.edu.pl/c/oi30-1/p/poc/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

int bin_search(vector<int>& arr, int x)
{
    int start = 0;
    int end = arr.size() - 1;
    while (start < end)
    {
        int mid = (start + end) / 2;
        if (arr[mid] >= x) end = mid;
        else start = mid + 1;
    }
    return start;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // vector<int> x = {9, 11, 13, 17, 18, 19};
    // cout << bin_search(x, 19) << '\n';

    // return 0;

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> A(n + 1);
    vector<int> B(m + 1);
    vector<vector<int> > idxA(k + 1);

    for (int i = 1; i <= n; ++i)
    {
        cin >> A[i];
        idxA[A[i]].push_back(i);
    }
    for (int i = 1; i <= m; ++i)
    {
        cin >> B[i];
    }

    vector<int> pos(m + 1);
    vector<bool> res(n + 1);

    int b_i = 1;
    int curr = B[b_i];   
    for (int i = idxA[B[1]][0]; i <= n; ++i)
    {
        if (A[i] == curr) {
            res[i] = true;
            pos[b_i] = i;
            b_i++;
            if (b_i > m) break;
            curr = B[b_i];
        }
    }

    int lim = n;
    int pred_lim = n;
    for (int i = m; i >= 1; --i)
    {
        int num = B[i];
        int idx = pos[i];
        int num_idx_idx = bin_search(idxA[num], idx) + 1;
        bool already = false;
        while (num_idx_idx < idxA[num].size())
        {
            if (res[idxA[num][num_idx_idx]]) {
                // num_idx_idx++;
                already = true;
                break;
            }
            if (idxA[num][num_idx_idx] <= lim) {
                res[idxA[num][num_idx_idx]] = true;
                num_idx_idx++;
            }
            else {
                // num_idx_idx++;
                break;
            }
        }
        if (already) {
            pred_lim = lim;
            lim = idxA[num][bin_search(idxA[num], pred_lim) - 1];
        }
        else {
            pred_lim = lim;
            lim = idxA[num][num_idx_idx - 1];
        }
    }


    for (int i = 1; i <= n; ++i) 
    {
        cout << res[i] << ' ';
    }
    cout << '\n';

    return 0;
}