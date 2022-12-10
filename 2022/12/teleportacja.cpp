#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    cin >> N;

    int res = 0;

    long long i = 1;
    while (N - i > 0)
    {
        N -= i;
        i *= 2;
        res++;
    }
    res += __builtin_popcountll(N);
    cout << res << '\n';

    return 0;
}