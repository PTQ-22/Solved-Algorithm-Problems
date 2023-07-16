#include <bits/stdc++.h>
using namespace std;

struct BJ {
    int b, j, end;
    bool operator<(const BJ &other) const {
        return j > other.j;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int cnt = 0;
    while (cin >> n, n > 0)
    {
        vector<BJ> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i].b >> arr[i].j;
        }
        sort(arr.begin(), arr.end());

        int covered = 0;
        for (int i = 0; i < n; ++i) {
            covered += arr[i].b;
            arr[i].end = covered + arr[i].j;
        }
        int res = -1;
        for (int i = 0; i < n; ++i) res = max(arr[i].end, res);
        printf("Case %d: %d\n", ++cnt, res);
    }
    

    return 0;
}