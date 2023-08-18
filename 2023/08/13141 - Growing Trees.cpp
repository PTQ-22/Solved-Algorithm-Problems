#include <bits/stdc++.h>
using namespace std;


unsigned long long fib[90];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    fib[1] = fib[2] = 1;

    for (int i = 3; i < 90; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    int n;
    while (cin >> n, n > 0) 
    {
        cout << fib[n] << '\n';
    }

    return 0;
}