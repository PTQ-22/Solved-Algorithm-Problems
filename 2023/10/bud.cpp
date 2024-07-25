// https://szkopul.edu.pl/problemset/problem/E0WdV0P4l3hYG2WAuFWyQ-TV/site/?key=statement
// Piotr Kowalczyk
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1502;
char grid[MAXN][MAXN];
int px_poziom[MAXN][MAXN];
int px_pionow[MAXN][MAXN];
int n, m;

bool check(int length)
{
    vector<pair<int, int>> dobre_poziome, dobre_pionowe;
    int nr_poziome = -1, nr_pionowe = -1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n - length + 1; ++j) {
            if (grid[i][j] != 'X') {
                if (px_poziom[i][j] == px_poziom[i][j + length - 1]) {
                    if (nr_poziome == -1) {
                        dobre_poziome.emplace_back(j, j + length - 1);
                        nr_poziome = i;
                    }
                    else if (nr_poziome == i) {
                        dobre_poziome.emplace_back(j, j + length - 1);
                    }
                    else {
                        return true;
                    }

                    // cout << i << " (" << j << ", " << j << ' ' << j + length - 1 << '\n';
                }
            }
        }
    }
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= n - length + 1; ++i) {
            if (grid[i][j] != 'X') {
                if (px_pionow[i][j] == px_pionow[i + length - 1][j]) {
                    if (nr_pionowe == -1) {
                        dobre_pionowe.emplace_back(i, i + length - 1);
                        nr_pionowe = j;
                    }
                    else if (nr_pionowe == j) {
                        dobre_pionowe.emplace_back(i, i + length - 1);
                    }
                    else {
                        return true;
                    }
                    // cout << i << ' ' << i + length - 1 << ") " << j << '\n';
                }
            }
        }
    }
    if (dobre_pionowe.size() || dobre_poziome.size()) {
        if (m == 1) {
            return true;
        }

        if (dobre_poziome.size() && !dobre_pionowe.size()) {
            int d_poz = dobre_poziome.back().second - dobre_poziome[0].first + 1;
            return d_poz >= 2 * length;
        }
        else if (dobre_pionowe.size() && !dobre_poziome.size()) {
            int d_pion = dobre_pionowe.back().second - dobre_pionowe[0].first + 1;
            return d_pion >= 2 * length;
        }
        else {
            int d_poz = dobre_poziome.back().second - dobre_poziome[0].first + 1;
            int d_pion = dobre_pionowe.back().second - dobre_pionowe[0].first + 1;
            if (d_poz >= 2 * length || d_pion >= 2 * length) {
                return true;
            }
            int d_poz_lewe = nr_pionowe - dobre_poziome[0].first;
            int d_poz_prawe = dobre_poziome.back().second - nr_pionowe;
            int d_pion_gora = nr_poziome - dobre_pionowe[0].first;
            int d_pion_dol = dobre_pionowe.back().second - nr_poziome;
            
            if (d_poz_lewe >= length || d_poz_prawe >= length || d_pion_gora >= length || d_pion_dol >= length) {
                return true;
            }
            return false;
        }
    }

    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> grid[i][j];
        }
    }

    for (int i = 1; i <= n; ++i) {
        px_poziom[i][1] = (grid[i][1] == 'X') ? 1 : 0;
        for (int j = 2; j <= n; ++j) {
            px_poziom[i][j] = px_poziom[i][j - 1];
            if (grid[i][j] == 'X') {
                px_poziom[i][j]++;
            }
        }
        px_pionow[1][i] = (grid[1][i] == 'X') ? 1 : 0;
        for (int j = 2; j <= n; ++j) {
            px_pionow[j][i] = px_pionow[j - 1][i];
            if (grid[j][i] == 'X') {
                px_pionow[j][i]++;
            }
        }
    }

    int start = 1;
    int end = n + 1;
    while (start < end) {
        int mid = (start + end) / 2;
        if (!check(mid)) {
            end = mid;
        }
        else {
            start = mid + 1;
        }
    }
    cout << start - 1 << '\n';


    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         if (grid[i][j] == 'X') cout << "X ";
    //         else cout << px_poziom[i][j] << " ";
    //     }
    //     cout << '\n';
    // }
    // cout << '\n';
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         if (grid[i][j] == 'X') cout << "X ";
    //         else cout << px_pionow[i][j] << " ";
    //     }
    //     cout << '\n';
    // }
    // cout << '\n';


    return 0;
}