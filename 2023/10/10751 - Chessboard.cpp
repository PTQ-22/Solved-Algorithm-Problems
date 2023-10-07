#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << setprecision(3) << fixed;

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        double x = 4 * (n - 1);
        if (x > 0)
            cout << x + sqrt(2) * (double(n*n) - x) << '\n'; 
        else 
            cout << 0.000 << '\n';
            
        if (t) cout << '\n';
    }

    return 0;
}