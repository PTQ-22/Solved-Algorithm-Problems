#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> arr(n);
    vector<pair<int, char>> pocz(n), kon(n); // dl, lit
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    for (int i = 0; i < n; ++i) {
        string x = arr[i];
        pocz[i] = {1, x[0]};
        int j = 1;
        while (j < x.size() && x[0] == x[j]) {
            pocz[i] = {pocz[i].first + 1, pocz[i].second};
            j++;
        }
        kon[i] = {1, x.back()};
        j = x.size() - 2;
        while (j >= 0 && x.back() == x[j]) {
            kon[i] = {kon[i].first + 1, kon[i].second};
            j--;
        }
    }
// 9
// w
// ispjhzklfq
// vsuwuivv <<<
// ujrvuk
// kcl
// to
// t
// vosy <<<
// ioid 

    int res = -1;
    for (char c = 'a'; c <= 'z'; ++c) {
        int max_pocz = 0;
        int max_pocz_i = -1;
        int max_kon = 0;
        int wait_pocz = -1;
        int wait_pocz_size = 0;
        for (int i = 0; i < n; ++i) {
            if (pocz[i].second == c) {
                if (pocz[i].first != arr[i].size()) {
                    if (pocz[i].second == kon[i].second && kon[i].first >= pocz[i].first) {
                        wait_pocz = i;
                        wait_pocz_size = pocz[i].first;
                        continue;
                    }

                    if (pocz[i].first > max_pocz) {

                        max_pocz = pocz[i].first;
                        max_pocz_i = i;
                    }
                }
            }
        }
        int max_kon_i = -1;
        for (int i = 0; i < n; ++i) {
            if (kon[i].second == c) {
                if (kon[i].first != arr[i].size()) {
                    if (max_pocz_i != i) {
                        if (kon[i].first > max_kon) {
                            max_kon_i = i;
                            max_kon = kon[i].first;
                        }
                    }
                }
            }
        }
        if (max_pocz == 0 && wait_pocz != -1) {
            if (max_kon_i != wait_pocz) {
                max_pocz = wait_pocz_size;
            }
        }
        int sum_cal = 0;
        for (int i = 0; i < n; ++i) {
            if (pocz[i].second == c) {
                if (pocz[i].first == arr[i].size()) {
                    sum_cal += pocz[i].first;
                }
            }
        }
        int max_sr = 0;
        for (int i = 0; i < n; ++i) {
            int dl = 0;
            for (int j = 0; j < arr[i].size(); ++j) {
                if (arr[i][j] == c) {
                    dl++;
                    max_sr = max(dl, max_sr);
                }
                else dl = 0;
            }
        }
        // cout << max_pocz << ' ' << max_kon << ' ' << sum_cal << '\n';
        res = max(res, max(max_pocz + max_kon + sum_cal, max_sr));
    }

    cout << res << '\n';

    return 0;
}