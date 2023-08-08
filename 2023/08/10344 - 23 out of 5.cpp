#include <bits/stdc++.h>
using namespace std;

constexpr int n = 5;
vector<int> arr(n);
char chars[] = {'+', '-', '*'};

int eval(string opers)
{
    int res = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (opers[i] == '+') res += arr[i];
        else if (opers[i] == '-') res -= arr[i];
        else res *= arr[i]; 
    }
    return res;
}

bool check()
{
    do {
        for (int i = 0; i < 3; i++) 
                for (int j = 0; j < 3; ++j) 
                    for (int k = 0; k < 3; ++k) 
                        for (int l = 0; l < 3; ++l) {
                            string x = " ";
                            x += chars[i];
                            x += chars[j];
                            x += chars[k]; 
                            x += chars[l];
                            if (eval(x) == 23) return true;
                        }
    } while (next_permutation(arr.begin(), arr.end()));
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> arr[0], arr[0] > 0)
    {
        for (int i = 1; i < n; ++i) cin >> arr[i];
        sort(arr.begin(), arr.end());
        if (check()) cout << "Possible\n";
        else cout << "Impossible\n";
    }

    return 0;
}