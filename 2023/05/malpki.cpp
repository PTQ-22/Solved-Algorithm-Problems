// https://szkopul.edu.pl/problemset/problem/kd-sEDS37q_Q8vr-RjxBhw4p/site/?key=statement
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 200'002;
int right_hand[MAXN];
int left_hand[MAXN];

int res[MAXN];

int rep[MAXN];
vector<int> sets[MAXN];

void join(int a, int b)
{
    if (rep[a] == rep[b]) return;
    if (sets[rep[a]].size() > sets[rep[b]].size()) {
        int pre_rep = rep[b];
        for (int x : sets[rep[b]]) {
            rep[x] = rep[a];
            sets[rep[a]].push_back(x);
        }
        sets[pre_rep].clear();
    }
    else {
        int pre_rep = rep[a];
        for (int x : sets[rep[a]]) {
            rep[x] = rep[b];
            sets[rep[b]].push_back(x);
        }
        sets[pre_rep].clear();
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
    {
        int left, right;
        cin >> left >> right;
        if (left > 0) left_hand[i] = left;
        if (right > 0) right_hand[i] = right;
    }
    vector<pair<int, int>> edges_to_process;
    for (int i = 1; i <= m; ++i) {
        int monkey, hand;
        cin >> monkey >> hand;
        if (hand == 1) {
            edges_to_process.emplace_back(monkey, left_hand[monkey]);
            left_hand[monkey] = 0;
        }
        if (hand == 2) {
            edges_to_process.emplace_back(monkey, right_hand[monkey]);
            right_hand[monkey] = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        res[i] = -1;
        rep[i] = i;
        sets[i].push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        if (right_hand[i] > 0) {
            join(i, right_hand[i]);
        }
        if (left_hand[i] > 0) {
            join(i, left_hand[i]);
        }
    }

    int time = m - 1;
    reverse(edges_to_process.begin(), edges_to_process.end());
    for (auto e : edges_to_process) {
        int a = e.first;
        int b = e.second;
        if (rep[a] == rep[1] && rep[b] == rep[1]) {
            join(a, b);
        }
        else if (rep[a] != rep[1] && rep[b] != rep[1]) {
            join(a, b);
        }
        else {
            if (rep[a] != rep[1]) swap(a, b);
            // rep[a] == rep[1]
            for (int x : sets[rep[b]]) {
                res[x] = time;
            }
            join(a, b);
        }
        time--;
    }
    for (int i = 1; i <= n; ++i) {
        cout << res[i] << '\n';
    }

    return 0;
}