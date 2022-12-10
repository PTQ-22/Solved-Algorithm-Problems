#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 8'000'002;
int P[MAXN];
string pattern, text;

void makeP()
{
    int j = 0;
    for (int i = 2; i <= pattern.size(); ++i)
    {
        while (j > 0 && pattern[j + 1] != pattern[i]) j = P[j];
        if (pattern[j + 1] == pattern[i]) j++;
        P[i] = j;
    }
}

void KMP()
{
    pattern = 'X' + pattern;
    text = 'X' + text;
    makeP();
    
    int j = 0; 
    for (int i = 1; i <= text.size(); ++i)
    {
        while (j > 0 && pattern[j + 1] != text[i]) j = P[j];
        if (pattern[j + 1] == text[i]) j++;
        if (j == pattern.size() - 1) {
            cout << i - pattern.size() + 2 << '\n';
            j = P[j];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    cin >> pattern >> text;

    KMP();

    return 0;
}