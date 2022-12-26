#include <bits/stdc++.h>
using namespace std;

constexpr int BASE = 1 << 21;
int tree[2 * BASE];

void add(int a, int b, int x)
{
    a += (BASE - 1);
    b += (BASE + 1);
    while ((a >> 1) != (b >> 1))
    {
        if (!(a & 1))
            tree[a + 1] += x;
        if (b & 1)
            tree[b - 1] += x;
        a >>= 1;
        b >>= 1;
    }
}

int query(int v)
{
    v += BASE;
    int res = 0;
    while (v > 0)
    {
        res += tree[v];
        v >>= 1;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int maxi = 0;
    int mini = INT32_MAX;
    for (int i = 1; i <= n; ++i)
    {
        int a, b;
        cin >> a >> b;
        maxi = max(maxi, b);
        mini = min(mini, a);
        add(a * 2, b * 2, 1);
    }
    int start = -1;
    bool isSegment = true;
    int end = 2 * maxi + 2;
    for (int i = 1; i <= end; i += 2)
    {
        if (query(i) == 0)
        {
            isSegment = false;
            if (start != -1)
            {
                cout << start << ' ' << ((i - 1) >> 1) << '\n';
                start = -1;
            }
            if (query(i + 1) != 0)
            {
                if (!isSegment)
                {
                    start = (i + 1) >> 1;
                }
                isSegment = true;
            }
        }
    }

    return 0;
}