#include <bits/stdc++.h>
using namespace std;

bool cmp(const pair<double, double> a, const pair<double, double> b)
{
    return (a.second == b.second) ? (a.first < b.first) : (a.second < b.second);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, d;
    int caseCnt = 0;
    while (cin >> n >> d, n > 0)
    {
        vector<pair<int, int>> islands(n);
        vector<pair<double, double>> segments(n);
        bool flag = false;
        for (int i = 0; i < n; ++i) {
            cin >> islands[i].first >> islands[i].second;
            if (islands[i].second > d) {
                flag = true;
            } 
        }
        if (flag) {
            printf("Case %d: -1\n", ++caseCnt);
            continue;
        }
        for (int i = 0; i < n; ++i) {
            double x = islands[i].first;
            double y = islands[i].second;
            double dx = sqrt((double)(d*d) - (y*y));
            segments[i] = {x - dx, x + dx};
        }
        sort(segments.begin(), segments.end(), cmp);
        int cnt = 1;
        double radar = segments[0].second;
        for (int i = 1; i < n; ++i) {
            if (segments[i].first > radar) {
                cnt++;
                radar = segments[i].second;
            }
        }

        printf("Case %d: %d\n", ++caseCnt, cnt);
    }

    return 0;
}