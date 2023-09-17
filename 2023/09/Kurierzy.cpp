#include <bits/stdc++.h>
using namespace std;

constexpr int BASE = 1 << 19;
pair<int, int> tree[2 * BASE];

void add(int v, int x)
{
    v += BASE;
    tree[v] = {x, 1};
    v /= 2;
    while (v > 0) {
        if (tree[v * 2].first == tree[v * 2 + 1].first) {
            tree[v] = {tree[v * 2].first, tree[v * 2].second + tree[v * 2 + 1].second};
        }
        else {
            if (tree[v * 2].second > tree[v * 2 + 1].second) {
                tree[v] = {tree[v * 2].first, tree[v * 2].second - tree[v * 2 + 1].second};
            }
            else if (tree[v * 2].second < tree[v * 2 + 1].second) {
                tree[v] = {tree[v * 2 + 1].first, tree[v * 2 + 1].second - tree[v * 2].second};
            }
            else {
                tree[v] = {0, 0};
            }
        }
        v /= 2;
    }
}

pair<int, int> query(int v, int a, int b, int p, int k)
{
    if (k < a || b < p) return {0, 0};
    else if (p <= a && b <= k) {
        return tree[v];
    }
    else {
        int l = 2 * v, r = 2 * v + 1;
        int mid = (a + b) / 2;

        auto left = query(l, a, mid, p, k);
        auto right = query(r, mid + 1, b, p, k);
        if (left.first == right.first) {
            return {left.first, left.second + right.second};
        }
        else if (left.second > right.second) {
            return {left.first, left.second - right.second};
        }
        else if (left.second < right.second) {
            return {right.first, right.second - left.second};
        }
        else return {0, 0};
    }
}

struct Zap {
    int d;
    int kandydat;
    int na_p, na_k;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> firma(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> firma[i];
        add(i, firma[i]);
    }
    vector<Zap> zapyt(m + 1);
    vector<vector<int>> zacz(n + 1, vector<int>());
    vector<vector<int>> kon(n + 1, vector<int>());
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        zapyt[i] = {b - a + 1, query(1, 0, BASE - 1, a, b).first, 0, 0};
        zacz[a].push_back(i);
        kon[b].push_back(i);
    }
    vector<int> cnt(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        for (int z : zacz[i]) {
            zapyt[z].na_p = cnt[zapyt[z].kandydat];
        }
        cnt[firma[i]]++;
        for (int z : kon[i]) {
            zapyt[z].na_k = cnt[zapyt[z].kandydat];
        }
    }

    for (int i = 1; i <= m; ++i) {
        if (zapyt[i].na_k - zapyt[i].na_p > zapyt[i].d / 2) {
            cout << zapyt[i].kandydat << '\n';
        }
        else {
            cout << 0 << '\n';
        }
    }

    return 0;
}