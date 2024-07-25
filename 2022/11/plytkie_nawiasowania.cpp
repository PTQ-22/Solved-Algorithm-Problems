// https://sio2.mimuw.edu.pl/c/oi30-1/p/ply/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, H;
    cin >> n >> H;

    char c;
    vector<pair<bool, bool>> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> c;
        if (c == '(')
        {
            arr[i].second = true;
        }
        else
        {
            arr[i].first = true;
        }
    }
    // H = 1 ???
    if (H == 1)
    {
        int res = 0;
        for (int i = 1; i < n; i += 2)
        {
            if (arr[i].second)
            {
                if (!arr[i + 1].first)
                {
                    res++;
                }
            }
            else
            {
                res++;
                if (!arr[i + 1].first)
                {
                    res++;
                }
            }
        }
        cout << res << '\n';
    }
    else
    {
        int cnt = 0;
        int res = 0;
        int overflow_right = 0;
        int opened = 0;
        int closed = 0;
        for (int i = 1; i < n; ++i)
        {
            if (arr[i].second)
            { // 1 -> 2
                cnt++;
                opened++;
                if (arr[i + 1].first)
                { // 1 -> <- 2
                    // cnt--;
                    continue;
                }
                if (cnt == H)
                {
                    if (!arr[i + 1].first)
                    { // not 1 -> <- 2
                        arr[i].second = false;
                        arr[i].first = true;
                        cnt -= 2;
                        res++;
                        overflow_right++;
                        opened--;
                        closed++;
                        continue;
                    }
                    else
                    {
                        cnt = 0;
                        continue;
                    }
                }
            }
            else if (arr[i].first) {
                cnt--;
                closed++;
                if (closed > opened) {
                    closed--;
                    cnt++;
                    arr[i].first = false;
                    arr[i].second = true;
                    i--;
                }
            }
        }

        int overflow_left = 0;
        cnt = 0;
        closed = 0;
        opened = 0;
        for (int i = n; i > 1; --i)
        {
            if (arr[i].first)
            {
                cnt++;
                closed++;
                if (arr[i - 1].second)
                {
                    // cnt = 0;
                    // cnt--;
                    continue;
                }
                if (cnt == H)
                {
                    if (!arr[i - 1].second)
                    {
                        arr[i].first = false;
                        arr[i].second = true;
                        cnt -= 2;
                        res++;
                        overflow_left++;
                        closed--;
                        opened++;
                        continue;
                    }
                }
            }
            else if (arr[i].second) {
                cnt--;
                opened++;
                if (opened > closed) {
                    opened--;
                    cnt++;
                    arr[i].second = false;
                    arr[i].first = true;
                    i++;
                }
            }
        }
        res += abs(overflow_left - overflow_right);
        cout << res << '\n';
        // cout << "O L" << overflow_left << '\n';
        // cout << "O R" << overflow_right << '\n';
    }
    // for (int i = 1; i <= n; ++i)
    // {
    //     if (arr[i].first)
    //         cout << "<- ";
    //     cout << i << " ";
    //     if (arr[i].second)
    //         cout << "-> ";
    //     else
    //         cout << " ";
    // }
    return 0;
}