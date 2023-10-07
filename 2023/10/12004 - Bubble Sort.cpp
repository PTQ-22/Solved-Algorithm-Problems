#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    int caseCnt = 0;
    while (t--)
    {
        long long n;
        cin >> n;

        cout << "Case " << ++caseCnt << ": ";

        long long p = n * (n - 1LL);

        if (p % 4 == 0) {
            cout << p / 4;
        }
        else if (p % 2 == 0) {
            cout << p / 2 << "/2";
        }
        else {
            cout << p << "/4";
        }


        cout << '\n';
    }

    return 0;
}