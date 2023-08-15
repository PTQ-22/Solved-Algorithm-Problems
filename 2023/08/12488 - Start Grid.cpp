#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n)
    {
        vector<int> start(n), finish(n);
        for (int i = 0; i < n; ++i) cin >> start[i];
        for (int i = 0; i < n; ++i) cin >> finish[i];

        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            set<int> before;
            for (int j = 0; j < i; ++j) before.insert(start[j]);


            for (int j = 0; j < n; ++j) {
                if (finish[j] == start[i]) break;
                if (before.find(finish[j]) == before.end()) res++;
            }
        }
        cout << res << '\n';
    }

    return 0;
}