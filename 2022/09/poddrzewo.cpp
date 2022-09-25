#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    int ones = 0;
    for (int i = 1; i <= n; ++i) {
        if (arr[i] == 1) ones++;
    }

    if (ones == 0) {
        cout << "2\n";
    }
    else if (ones == 1) {
        cout << "1\n";
    }
    else {
        cout << "0\n";
    }
    cout << "2" << '\n';
    cout << "1 2" << '\n';

    return 0;
}
