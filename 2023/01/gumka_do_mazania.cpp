// https://szkopul.edu.pl/problemset/problem/CNrWfGt3eL5nu1HJ_Og05_v4/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // isLetter

    int n;
    cin >> n;

    vector<string> names(n);
    for (int i = 0; i < n; ++i)
        cin >> names[i];

    vector<vector<int>> cnt(n, vector<int>(26, 0));
    for (int i = 0; i < n; ++i)
    {
        for (char c : names[i]) {
            cnt[i][c - 'a']++;
        }
    }
    vector<int> startPos(n, 0);
    string res = "";
    for (int j = 25; j >= 0; --j)
    {
        int mini = INT32_MAX;
        for (int i = 0; i < n; ++i)
        {
            mini = min(mini, cnt[i][j]);
        }
        if (mini > 0)
        {
            for (int i = 0; i < n; ++i)
            {
                int currCnt = 0;
                for (int k = startPos[i]; k < names[i].size(); ++k) 
                {
                    cnt[i][names[i][k] - 'a']--;
                    if (names[i][k] == char(j + 'a')) currCnt++;
                    if (currCnt == mini) {
                        startPos[i] = k + 1;
                        break;
                    }
                }
            }
            for (int i = 0; i < mini; ++i) res += char(j + 'a');
        }
    }
    string normal = "bitek";
    int minLen = min(normal.size(), res.size());
    for (int i = 0; i < minLen; ++i)
    {
        if (res[i] == normal[i])
        {
            continue;
        }
        else if (res[i] > normal[i])
        {
            break;
        }
        else if (res[i] < normal[i])
        {
            cout << normal << '\n';
            return 0;
        }
    }
    cout << res << '\n';

    return 0;
}