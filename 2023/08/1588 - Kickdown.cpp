#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    string a, b;
    while (cin >> a >> b)
    {
        vector<int> bottom(a.size() + 2 * b.size());
        vector<int> top(b.size());
        for (int i = 0; i < a.size(); ++i) {
            bottom[b.size() + i] = a[i] - '0';
        }
        for (int i = 0; i < b.size(); ++i) {
            top[i] = b[i] - '0';
        }
        int res = INT32_MAX;
        for (int shift = 0; shift < a.size() + b.size(); ++shift) {
            
            bool check = true;
            int zeros = 0;
            for (int i = 0; i < top.size(); ++i) {
                if (top[i] + bottom[shift + i] > 3) {
                    check = false;
                    break;
                }
                if (bottom[shift + i] == 0) zeros++;
            }
            if (check) {
                res = min(res, (int)a.size() + zeros);
            }
        }
        cout << res << '\n';
    }
    
    

    return 0;
}