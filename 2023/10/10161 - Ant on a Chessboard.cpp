#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n, n > 0)
    {
        int ceil_sqrt = ceil(sqrt(n));

        int x = ceil_sqrt;
        int d = (ceil_sqrt * ceil_sqrt - n);
        int y = 1 + d;
        if (y > ceil_sqrt) {   
            y = (ceil_sqrt - (d - (ceil_sqrt - 1)));
        }

        if ((n > ceil_sqrt * ceil_sqrt - ceil_sqrt + 1) && (ceil_sqrt & 1))
            swap(x, y);
        if ((n <= ceil_sqrt * ceil_sqrt - ceil_sqrt + 1) && !(ceil_sqrt & 1))
            swap(x, y);
        cout << x << ' ' << y << '\n';
    }

    return 0;
}