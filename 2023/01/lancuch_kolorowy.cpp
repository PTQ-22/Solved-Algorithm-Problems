// https://szkopul.edu.pl/problemset/problem/MAWN1VdLdXO29VvrVYuYxQyw/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1'000'010;
int lens[MAXN];
int correctCount[MAXN];
int currentCount[MAXN];
int arr[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, color;
    cin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        cin >> lens[i];
    }
    long long len = 0;
    for (int i = 0; i < m; ++i)
    {
        cin >> color;
        correctCount[color] = lens[i];
        len += lens[i];
    }
    if (len > n) {
        cout << 0;
        return 0;
    }

    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
    }

    for (int i = 1; i <= len; ++i)
    {
        currentCount[arr[i]]++;
    }

    long long good = 0;
    for (int num = 1; num < MAXN; ++num)
    {
        if (currentCount[num] == correctCount[num])
        {
            if (currentCount[num])
                good++;
        }
    }

    long long res = 0;
    if (good == m)
        res++;
    for (long long i = 2; i + len - 1 <= n; ++i)
    {
        currentCount[arr[i - 1]]--;
        currentCount[arr[i + len - 1]]++;
        if (arr[i + len - 1] != arr[i - 1])
        {
            if (currentCount[arr[i - 1]] == correctCount[arr[i - 1]] && correctCount[arr[i - 1]])
            {
                good++;
            }
            else if (correctCount[arr[i - 1]] && currentCount[arr[i - 1]] + 1 == correctCount[arr[i - 1]])
            {
                good--;
            }
            if (currentCount[arr[i + len - 1]] == correctCount[arr[i + len - 1]] && correctCount[arr[i + len - 1]])
            {
                good++;
            }
            else if (correctCount[arr[i + len - 1]] && currentCount[arr[i + len - 1]] - 1 == correctCount[arr[i + len - 1]])
            {
                good--;
            }
        }

        if (good == m)
            res++;
    }
    cout << res << '\n';
    return 0;
}