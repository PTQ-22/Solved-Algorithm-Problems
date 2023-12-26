// Piotr Kowalczyk
#include <bits/stdc++.h>
using namespace std;

int log_2(int x) {
    int l = 0;
    for(int i = 1; i < x; i *= 2) {
        ++l;
    }
    return l;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p, M;
    cin >> n >> p >> M;

    vector<vector<bool>> g(2 * (n + 1), vector<bool>(2 * (n + 1), false));

    while (p--)
    {
        int a, b;
        cin >> a >> b;
        g[a][b] = g[b][a] = true;
    }
    int log = log_2(n);
    vector<vector<char>> codes_to_n(n + 1, vector<char>(n + 1 + 2 * log, 'C'));
    vector<vector<char>> codes_to_2n(n + 1, vector<char>(n + 1 + 2 * log, 'A'));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (g[i][n + j]) {
                codes_to_n[i][j] = 'B';
                codes_to_2n[j][j] = 'B';
            }
        }
    }

    int d = (1 << log) / 2;
    for (int j = 1; j <= log; ++j) {

        int x = 1;
        for (int i = 1; i <= n; ++i) {
            if (x <= d) {
                codes_to_n[i][n + j] = 'B';
                codes_to_2n[i][n + log + j] = 'B';
                x++;
            }
            else {
                i = i - 1 + x - 1;
                x = 1;
            }
        }
        d /= 2;
    }
    cout << n + 2 * log << '\n';
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < codes_to_n[i].size(); ++j) {
            cout << codes_to_n[i][j];
        }
        cout << '\n';
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < codes_to_2n[i].size(); ++j) {
            cout << codes_to_2n[i][j];
        }
        cout << '\n';
    }
    

    return 0;
}