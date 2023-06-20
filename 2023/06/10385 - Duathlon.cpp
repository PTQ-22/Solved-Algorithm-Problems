#include <bits/stdc++.h>
using namespace std;

constexpr double EPS = 1e-9;

double timeMargin(double r, int t, vector<pair<double, double>>& speeds, int n)
{
    double k = (double)t - r;
    vector<double> times(n);
    for (int i = 0; i < n; ++i) {
        times[i] = (r / speeds[i].first) + (k / speeds[i].second);
    }
    double mini = INT32_MAX;
    for (int i = 0; i < n - 1; ++i) {
        mini = min(mini, times[i]);
    }
    return (mini - times.back()) * 3600.0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    int n;
    cout << setprecision(2) << fixed;
    while (cin >> t >> n)
    {
        vector<pair<double, double>> speeds(n);
        for (int i = 0; i < n; ++i) {
            cin >> speeds[i].first >> speeds[i].second;
        }
        
        double hi = (double)t;
        double lo = 0.0;
        while (fabs(hi - lo) > EPS)
        {
            double m1 = (lo + lo + hi) / 3.0;
            double m2 = (lo + hi + hi) / 3.0;
            if (timeMargin(m1, t, speeds, n) < timeMargin(m2, t, speeds, n)) {
                lo = m1;
            }
            else {
                hi = m2;
            }
        }
        double r = hi;
        int time = round(timeMargin(hi, t, speeds, n));
        if (time < 0) {
            cout << "The cheater cannot win.\n";
        }
        else {
            cout << "The cheater can win by " << time << " seconds with r = " << r << "km and k = " << double(t) - r << "km.\n";
        }
    }

    return 0;
}