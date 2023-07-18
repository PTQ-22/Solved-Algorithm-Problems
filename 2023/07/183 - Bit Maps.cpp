#include <bits/stdc++.h>
using namespace std;

string fromB(int x, int m, int y, int n, string line, int startM)
{
    int cnt1 = 0;
    int cnt0 = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            (line[(i + y) * startM + (j + x)] == '1') ? (cnt1++) : (cnt0++);

    if (cnt1 == 0) {
        return "0";
    }
    else if (cnt0 == 0) {
        return "1";
    }
    int newMCeil = (m + 1) / 2;
    int newMFloor = m / 2;
    int newNCeil = (n + 1) / 2;
    int newNFloor = n / 2;
    if (n == 1) {
        return "D" +
            fromB(x, newMCeil, y, newNCeil, line, startM) +
            fromB(x + newMCeil, newMFloor, y, newNCeil, line, startM);
    }
    else if (m == 1) {
        return "D" +
            fromB(x, newMCeil, y, newNCeil, line, startM) +
            fromB(x, newMCeil, y + newNCeil, newNFloor, line, startM);
    }
    return "D" +
        fromB(x, newMCeil, y, newNCeil, line, startM) +
        fromB(x + newMCeil, newMFloor, y, newNCeil, line, startM) +
        fromB(x, newMCeil, y + newNCeil, newNFloor, line, startM) +
        fromB(x + newMCeil, newMFloor, y + newNCeil, newNFloor, line, startM);
}

void fromD(int x, int m, int y, int n, int startM, string& res, int& idx, string line)
{
    if (m == 0 || n == 0) return;
    if (line[idx] != 'D') {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                res[(i + y) * startM + (j + x)] = line[idx];
        idx++;
        return;
    }
    idx++;
    int newMCeil = (m + 1) / 2;
    int newMFloor = m / 2;
    int newNCeil = (n + 1) / 2;
    int newNFloor = n / 2;
    if (n == 1) {
        fromD(x, newMCeil, y, newNCeil, startM, res, idx, line);
        fromD(x + newMCeil, newMFloor, y, newNCeil, startM, res, idx, line);
        return;
    }
    else if (m == 1) {
        fromD(x, newMCeil, y, newNCeil, startM, res, idx, line);
        fromD(x, newMCeil, y + newNCeil, newNFloor, startM, res, idx, line);
        return;
    }
    fromD(x, newMCeil, y, newNCeil, startM, res, idx, line);
    fromD(x + newMCeil, newMFloor, y, newNCeil, startM, res, idx, line);
    fromD(x, newMCeil, y + newNCeil, newNFloor, startM, res, idx, line);
    fromD(x + newMCeil, newMFloor, y + newNCeil, newNFloor, startM, res, idx, line);
}

int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);

    char c;
    while (cin >> c, c != '#')
    {
        int n, m;
        cin >> n >> m;
        string line, x;
        cin >> line;
        while (c == 'B' && line.size() != n * m) {
            cin >> x;
            line += x;
        }
        if (c == 'B') {
            printf("D%4d%4d",n, m);
            string res = fromB(0, m, 0, n, line, m);
            for (int i = 0; i < res.size(); ++i) {
                if ((i) % 50  == 0) cout << '\n';
                cout << res[i];
            }
            cout << '\n';
        }
        else {
            printf("B%4d%4d",n, m);
            string res = "";
            for (int i = 0; i < n * m; ++i) res += ' ';
            int idx = 0;
            fromD(0, m, 0, n, m, res, idx, line);
            for (int i = 0; i < res.size(); ++i) {
                if ((i) % 50  == 0) cout << '\n';
                cout << res[i];
            }
            cout << '\n';
        }
    }

    return 0;
}