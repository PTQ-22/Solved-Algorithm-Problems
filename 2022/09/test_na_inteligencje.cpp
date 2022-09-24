// https://szkopul.edu.pl/problemset/problem/Ak4wWPkNtHpF-OiulN1gixfW/site/
#include <bits/stdc++.h>
using namespace std;

bool check(int x, vector<int> &ind, int act)
{
    if (ind[x] > act)
        return true;
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    const int MAXM = 1'000'001;
    vector<vector<int>> indexes(MAXM, vector<int>());

    int m, x;
    cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> x;
        indexes[x].push_back(i);
    }

    int n;
    cin >> n;
    while (n--)
    {
        int k, a;
        cin >> k;
        vector<int> arr(k + 1);
        bool poss = true;
        for (int i = 1; i <= k; ++i)
        {
            cin >> a;
            if (indexes[a].size() == 0 || !poss)
            {
                poss = false;
                continue;
            }
            int start = 0;
            int end = indexes[a].size() - 1;
            while (start < end)
            {
                int mid = (start + end) / 2;
                if (check(mid, indexes[a], arr[i - 1]))
                    end = mid;
                else
                    start = mid + 1;
            }
            arr[i] = indexes[a][start];
        }
        if (!poss) {
            cout << "NIE\n";
        }
        else {
            for (int i = 2; i <= k; ++i) {
                if (arr[i - 1] >= arr[i]) {
                    poss = false;
                    break;
                }
            }
            if (poss) {
                cout << "TAK\n";
            }
            else {
                cout << "NIE\n";
            }
        }
    }

    return 0;
}
