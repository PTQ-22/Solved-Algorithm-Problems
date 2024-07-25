// https://szkopul.edu.pl/problemset/problem/KkN5UonnNGIG3AuMqoI6xr62/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1'000'002;
set<pair<int, int>> starts, endss;
bool is_start[MAXN], is_end[MAXN];
pair<int, int> lawyers[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
    {
        int s, e;
        cin >> s >> e;
        lawyers[i] = {s, e};
        starts.emplace(s, i);
        endss.emplace(e, i);
    }

    int curr_lawyers = 0;
    int start = 0;
    int end = 0;
    pair<int, int> res = {0, 0};

    while (starts.size() || endss.size())
    {
        if (curr_lawyers < k && starts.size()) {
            auto taken = *starts.begin();
            starts.erase(starts.begin());
            if (is_end[taken.second]) {
                continue;
            }
            curr_lawyers++;
            is_start[taken.second] = true;
            start = taken.first;
        }
        else if (curr_lawyers >= k && endss.size()) {
            auto taken = *endss.begin();
            endss.erase(endss.begin());
            is_end[taken.second] = true;
            if (!is_start[taken.second]) {
                continue;
            }
            end = taken.first;
            if (end - start > res.second - res.first) {
                res = {start, end};
            }
            curr_lawyers--;
        }
        else {
            break;
        }
    }
    vector<int> ress;
    for (int i = 1; i <= n; ++i) 
    {
        if (lawyers[i].first <= res.first && lawyers[i].second >= res.second) {
            ress.push_back(i);
        }
    }
    cout << res.second - res.first << '\n';
    for (int i = 0; i < k; ++i) cout << ress[i] << ' ';
    cout << '\n';
    return 0;
}