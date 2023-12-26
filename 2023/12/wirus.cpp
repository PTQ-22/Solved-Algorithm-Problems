#include <bits/stdc++.h>
using namespace std;

constexpr int SIZE = 700;
typedef vector<bitset<SIZE>> matrix;

matrix mult(matrix& a, matrix& b, int n)
{
    matrix obr(n, bitset<SIZE>());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            obr[i][j] = b[j][i];
        }
    }
    matrix res(n, bitset<SIZE>());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = (a[i] & obr[j]).count() & 1;
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long d;
    cin >> n >> d;
    d--;

    matrix wir(1, bitset<SIZE>());
    string text;
    cin >> text;
    for (int i = 0; i < n; ++i) {
        wir[0][i] = text[i] - '0';
    }
    matrix mat(n, bitset<SIZE>());
    for (int i = 0; i < n - 1; ++i) {
        mat[i + 1][i] = 1;
    }
    mat[0][n - 1] = mat[1][n - 1] = 1;

    
    matrix res = mat;
    while (d) {
        if (d & 1LL) {
            res = mult(res, mat, n);
        }
        mat = mult(mat, mat, n);
        d /= 2LL;
    }

    vector<long long> ans(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans[i] += (wir[0][j] * res[j][i]);
        }
    }
    for (int x : ans) cout << (x & 1);
    cout << '\n';

    return 0;
}
