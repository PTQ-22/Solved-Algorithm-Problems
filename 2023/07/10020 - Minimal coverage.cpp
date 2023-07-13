#include <bits/stdc++.h>
using namespace std;

struct Interval
{
    int l, r;

    bool operator<(const Interval &other) const
    {
        if (l < other.l)
            return true;
        else if (l > other.l)
            return false;
        else
        {
            if (r > other.r)
                return true;
            else
                return false;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int m;
        cin >> m;
        vector<Interval> intervals;
        int l, r;
        while (cin >> l >> r, !(l == 0 && r == 0))
        {
            if (r <= 0)
                continue;
            intervals.push_back({l, r});
        }
        sort(intervals.begin(), intervals.end());

        vector<Interval> used;
        int curr = 0;
        bool poss = true;
        for (int i = 0; i < intervals.size(); ++i)
        {
            if (curr >= m) break;
            if (intervals[i].r < curr) continue;
            if (intervals[i].l <= curr) {
                int max_r = -1;
                int new_i;
                for (int j = i; j < intervals.size(); ++j) {
                    if (intervals[j].l > curr) break;
                    if (intervals[j].r > max_r) {
                        max_r = intervals[j].r;
                        new_i = j;
                    }
                }
                used.push_back(intervals[new_i]);
                curr = max_r;
            }
            else {
                poss = false;
            }
        }
        if (!poss || curr < m) cout << "0\n";
        else {
            cout << used.size() << '\n';
            for (Interval intv : used) {
                cout << intv.l << ' ' << intv.r << '\n';
            }
        }
            cout << '\n';
    }

    return 0;
}