#include <bits/stdc++.h>
using namespace std;

int toConsump(int x)
{
    int res = 0;

    while (x > 0 && res < 100)
    {
        x -= 100;
        if (x < 0)
        {
            return res + (x + 100) / 2;
        }
        res += 50;
    }
    while (x > 0 && res < 9900)
    {
        x -= 9900;
        if (x < 0)
        {
            return res + (x + 9900) / 3;
        }
        res += 3300;
    }
    while (x > 0 && res < 990000)
    {
        x -= 990000;
        if (x < 0)
        {
            return res + (x + 990000) / 5;
        }
        res += 198000;
    }
    if (x > 0)
        return res + x / 7;
    return res;
}

int toAmount(int x)
{
    int res = 0;
    if (x <= 100)
        return 2 * x;
    res = 200;
    x -= 100;
    if (x < 0)
        return res;
    if (x <= 9900)
        return res + (3 * x);
    res += (3 * 9900);
    x -= 9900;
    if (x < 0)
        return res;
    if (x <= 990000)
        return res + (5 * x);
    res += (5 * 990000);
    x -= 990000;
    if (x <= 0)
        return res;
    return res + (7 * x);
}

bool check(int A, int B, int x)
{
    int y = B + x;
    int total = toConsump(x) + toConsump(y);
    return toAmount(total) >= A;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    int A, B;
    while (cin >> A >> B, A > 0)
    {
        int start = 1;
        int end = 1e9 / 2;
        while (start < end)
        {
            int mid = (start + end) / 2;
            if (check(A, B, mid)) {
                end = mid;
            }
            else {
                start = mid + 1;
            }
        }
        cout << start << '\n';
    }

    return 0;
}