#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << setprecision(3) << fixed << showpoint;
    int a, b;
    int caseCnt = 0;
    while (cin >> a >> b, a > 0)
    {
        int AM[101][101];
        for (int i = 1; i <= 100; ++i) for (int j = 1; j <= 100; ++j) AM[i][j] = 1e9;

        AM[a][b] = 1;
        while (cin >> a >> b, a > 0) AM[a][b] = 1;
        for (int i = 1; i <= 100; ++i) AM[i][i] = 0;
        
        for (int k = 1; k <= 100; k++) 
            for (int i = 1; i <= 100; i++) 
                for (int j = 1; j <= 100; ++j) 
                    AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
        int sum = 0;
        int num = 0;
        for (int i = 1; i <= 100; ++i)
            for (int j = 1; j <= 100; ++j) {
                if (AM[i][j] != 1e9 && i != j) {
                    sum += AM[i][j];
                    num++;
                }
            }
        double res = (double)sum / (double)num;
        cout << "Case " << ++caseCnt << ": average length between pages = ";
        cout << res << " clicks\n";
    }

    return 0;
}