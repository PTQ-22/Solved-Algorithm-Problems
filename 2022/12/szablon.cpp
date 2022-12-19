#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 500'002;
int pText[MAXN];

void makeP(string text)
{
    // p[1] = 0;
    int n = text.size();
    text = 'X' + text;
    int j = 0;
    for (int i = 2; i <= n; ++i)
    {
        while (j > 0 && text[i] != text[j + 1])
            j = pText[j];
        if (text[i] == text[j + 1])
            j++;
        pText[i] = j;
    }
}

bool KMP(string &text, string pattern)
{
    int j = 0;
    int n = text.size();
    int m = pattern.size();
    text = 'X' + text;
    pattern = 'X' + pattern;
    vector<int> posFound;
    for (int i = 1; i <= n; ++i)
    {
        while (j > 0 && text[i] != pattern[j + 1])
            j = pText[j];
        if (text[i] == pattern[j + 1])
            j++;
        if (j == m)
        {
            posFound.push_back(i - m + 1);
            j = pText[j];
        }
    }
    text = text.substr(1, n);
    for (int i = 1; i < posFound.size(); ++i)
    {
        if (posFound[i - 1] + m < posFound[i])
            return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string text;
    cin >> text;

    makeP(text);

    int x = text.size();
    int res = 0;
    while (x > 1)
    {
        if (pText[x] <= x / 2)
        {
            if (KMP(text, text.substr(0, x)))
            {
                res = x;
            }
        }
        x = pText[x];
    }

    cout << res << '\n';

    return 0;
}