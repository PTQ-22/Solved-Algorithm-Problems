#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> forD[330];
int64_t arr[100005];
int64_t px[100335];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int sqrtN = sqrt(n);

    while (k--)
    {
        int a, l, d;
        cin >> a >> l >> d;
        if (l <= sqrtN)
        {
            for (int i = a; i < a + l * d; i += d)
            {
                arr[i]++;
            }
        }
        else
        {
            forD[d].push_back({a, l});
        }
    }

    for (int d = 1; d < 330; ++d)
    {
        for (int i = 1; i <= n; ++i) px[i] = 0;
        for (auto x : forD[d])
        {
            int a, l;
            tie(a, l) = x;
            px[a]++;
            px[a + l * d]--;
        }
        for (int i = 1; i <= n; ++i)
        {
            px[i + d] += px[i];
        }
        for (int i = 1; i <= n; ++i)
        {
            arr[i] += px[i];
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n';

    return 0;
}