// https://szkopul.edu.pl/problemset/problem/FWVAF1ZpKFQnEHkbt1d5Hayl/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 200'002;
int req[MAXN];

struct Team
{
    int s, t, p;
    int len;

    bool operator<(const Team& other) const {
        return len < other.len;
    }
};

Team teams[MAXN];

constexpr int BASE = 1 << 18;
pair<int, int> min_tree[BASE * 2];
int sum_tree[BASE * 2];

void set_min(int v, int val)
{
    int start_v = v;
    v += BASE;
    while (v > 0) {
        if (val < min_tree[v].first) {
            min_tree[v] = {val, start_v};
        }
        // min_tree[v] = min(min_tree[v], val);
        v /= 2;
    }
}

void del_min(int v, int prev)
{
    v += BASE;
    bool flag = false;
    while (v > 0) {
        if (flag) {
            if (min_tree[v].first == prev) {
                if (min_tree[v * 2].first < min_tree[v * 2 + 1].first) {
                    min_tree[v] = min_tree[v * 2];
                }
                else {
                    min_tree[v] = min_tree[v * 2 + 1];
                }
            }
        }
        else {
            min_tree[v].first = INT32_MAX;
        }
        // min_tree[v] = min(min_tree[v], val);
        flag = true;
        v /= 2;
    }
}

pair<int, int> mini(int a, int b)
{
    a += BASE - 1;
    b += BASE + 1;
    pair<int, int> res = {INT32_MAX, -1};
    while (a / 2 != b / 2) {
        if (!(a & 1)) {
            if (min_tree[a + 1].first < res.first) {
                res = min_tree[a + 1];
            }
            // res = min(res, min_tree[a + 1]);
        }
        
        if (b & 1) {
            if (min_tree[b - 1].first < res.first) {
                res = min_tree[b - 1];
            }
            // res = min(res, min_tree[b - 1]);
        }
        a /= 2;
        b /= 2;
    }
    return res;
}

void add(int v, int val)
{
    v += BASE;
    while (v > 0) {
        sum_tree[v] += val;
        v /= 2;
    }
}

int sum(int a, int b)
{
    a += BASE - 1;
    b += BASE + 1;
    int res = 0;
    while (a / 2 != b / 2)
    {
        if (!(a & 1)) res += sum_tree[a + 1];
        if (b & 1) res += sum_tree[b - 1];
        a /= 2;
        b /= 2;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> req[i];
    }

    for (int i = 0; i < BASE * 2; ++i) {
        min_tree[i] = {INT32_MAX, -1};
    }
    for (int i = 1; i <= n; ++i) {
        set_min(i, req[i]);
    }

    int m;
    cin >> m;

    for (int i = 1; i <= m; ++i) 
    {
        int s, t, p;
        cin >> s >> t >> p;
        teams[i] = {s, t, p, t - s + 1};
    } 
    sort(teams + 1, teams + m + 1);

    for (int i = 1; i <= m; ++i) 
    {
        while (sum(teams[i].s, teams[i].t) < teams[i].p) {
            auto chosen = mini(teams[i].s, teams[i].t);
            del_min(chosen.second, chosen.first);
            add(chosen.second, 1);
        }
    }
    long long res = 0;
    vector<int> pos;
    for (int i = 1; i <= n; ++i) {
        if (sum(i, i)) {
            res += req[i];
            pos.push_back(i);
        }
    }
    cout << res << '\n' << pos.size() << '\n';
    for (int i : pos) cout << i << ' ';
    cout << '\n';

    return 0;
}