// Piotr Kowalczyk
#include <bits/stdc++.h>
using namespace std;

struct Segment
{
    int a, b, i;

    bool operator<(const Segment& other) const {
        if (b < other.b) return true;
        else if (b > other.b) return false;
        else {
            return a < other.a;
        }
    }
};

bool collide(Segment x, Segment y)
{
    if (x.b <= y.a || y.b <= x.a) return false;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Segment> arr(n);
    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        arr[i - 1] = {a, b, i};
    }
    sort(arr.begin(), arr.end());

    Segment curr_zap = {-1, -1, -1}, pre = {-1, -1, -1}, pre_zap = {-1, -1, -1};
    Segment curr = arr[0];
    Segment cand_zap = {-1, -1, -1};
    int good_used = 1;
    string pre_action = "new";
    vector<pair<int, int>> res_norm;
    for (int i = 1; i < n; ++i) {
        if (pre_action == "new") {
            if (collide(curr, arr[i])) {
                if (pre.i == -1 || !collide(arr[i], pre)) {
                    curr_zap = arr[i];
                    res_norm.emplace_back(curr.i, curr_zap.i);
                    pre_action = "zap";
                }
            }
            else {
                curr_zap = arr[i];
                pre_action = "zap_no_col"; // todo
            }
        }
        else if (pre_action == "zap") {
            if (collide(arr[i], curr_zap)) {
                if (!collide(arr[i], curr)) {
                    cand_zap = arr[i];
                }
            }
            else if (!collide(arr[i], curr)){
                pre = curr;
                pre_zap = curr_zap;
                curr_zap = {-1, -1, -1};
                curr = arr[i];
                pre_action = "new";
                good_used++;
                if (cand_zap.i != -1) {
                    if (collide(curr, cand_zap)) {
                        curr_zap = cand_zap;
                        res_norm.emplace_back(curr.i, curr_zap.i);
                        pre_action = "zap";
                    }
                    else {
                        pre_action = "zap_for_all";
                    }
                    cand_zap = {-1, -1, -1};
                }
            }
        }
        else if (pre_action == "zap_no_col") {
            if (collide(curr_zap, arr[i])) {
                // pre = curr;
                // curr = arr[i];
                // good_used++;
                // pre_action = "zap";
            }
            else {
                if (!collide(arr[i], curr)) {
                    curr = arr[i];
                    good_used++;
                }
                pre_action = "zap_for_all";
            }
        }
        else if (pre_action == "zap_for_all") {
            if (!collide(arr[i], curr)) {
                curr = arr[i];
                good_used++;
            }
        }
    }
    int k = 0;
    curr = arr[0];
    int zap_greed = curr.i;
    vector<pair<int, int>> res_greed;
    for (int i = 1; i < n; ++i) {
        if (!collide(arr[i], curr)) {
            curr = arr[i];
            res_greed.emplace_back(curr.i, zap_greed);
            k++;
        }
    }
    // cout << k << '\n';
    if (curr_zap.i == -1 && pre_action != "zap_for_all") {
        good_used--;
    }
    cout << max(good_used, k) << '\n';
    if (k >= good_used) {
        for (auto [x, y] : res_greed) {
            cout << x << ' ' << y << '\n';
        }
    }
    else {
        for (auto [x, y] : res_norm) {
            cout << x << ' ' << y << '\n';
        }
    }
    return 0;
}