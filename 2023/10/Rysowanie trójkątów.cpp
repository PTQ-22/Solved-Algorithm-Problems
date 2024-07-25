// https://szkopul.edu.pl/c/klasa-2b-20232024/problemset/problem/AfoFX3R1cGUsu6uLbplUDQgd/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

string translate(int num, string instr)
{
    string res;
    string bin;
    while (num > 0)
    {
        if (num & 1)
            bin = "1" + bin;
        else
            bin = "0" + bin;
        num /= 2;
    }
    reverse(bin.begin(), bin.end());
    if (bin[0] == '1')
    {
        res += instr;
    }
    for (int i = 1; i < bin.size(); ++i)
    {
        if (bin[i] == '1')
        {
            int to_close = 0;
            for (int j = i; j > 0; --j)
            {
                if (j >= 3)
                {
                    res += "8[";
                    j -= 2;
                }
                else if (j >= 2)
                {
                    res += "4[";
                    j--;
                }
                else
                {
                    res += "2[";
                }
                to_close++;
            }
            res += instr;
            for (int j = 0; j < to_close; ++j)
            {
                res += "]";
            }
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string res;
    bool flag = true;

    for (int level = n; level > 1; --level)
    {
        int cnt = 0;
        int tmp = level - 1;
        if (flag) {
            res += translate(tmp, "AEAC");
            res += "A2E";
        }
        else {
            res += translate(tmp, "CE");
        }
        flag = !flag;
    }
    if (n & 1)
    {
        res += "AE";
    }

    res += translate(n, "C");

    cout << res << '\n';

    return 0;
}