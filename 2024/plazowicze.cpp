#include <bits/stdc++.h>
using namespace std;

bool cmp(tuple<int, int, long long>& a, tuple<int, int, long long>& b)
{
    auto [a1, a2, a3] = a;
    auto [b1, b2, b3] = b;
    return a2 < b2;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, X, z;
    cin >> n >> X >> z;

    vector<long long> plazowicze(n);
    for (int i = 0; i < n; ++i) {
        cin >> plazowicze[i];
    }

    vector<tuple<int, int, long long>> zapyt(z);

    for (int i = 0; i < z; ++i) {
        int k;
        cin >> k;
        zapyt[i] = {k, i, 0};
    }
    sort(zapyt.begin(), zapyt.end());

    vector<tuple<long long, long long, int>> vct(n - 1);

    for (int i = 1; i < n; ++i) {
        long long d = plazowicze[i] - plazowicze[i - 1];
        d *= (long long)(1 << 30);
        long long x = -plazowicze[i - 1] * (long long)(1 << 30);
        vct[i - 1] = {d, x, 1};
    }
    sort(vct.begin(), vct.end());
    reverse(vct.begin(), vct.end());
    queue<tuple<long long, long long, int>> q;
    int i = 0;
    int curr_c = 0;
    int vi = 0;
    while (i < z) {
        long long d, x; int c;
        if (q.size()) {
            if (vi < n - 1) {
                auto [dv, xv, cv] = vct[vi];
                auto [dq, xq, cq] = q.front();
                if (dv > dq) {
                    d = dv; x = -xv; c = cv;
                    vi++;
                }
                else if (dv < dq) {
                    d = dq; x = -xq; c = cq;
                    q.pop();
                }
                else {
                    if (xv > xq) {
                        d = dv; x = -xv; c = cv;
                        vi++;
                    }
                    else {
                        d = dq; x = -xq; c = cq;
                        q.pop();
                    }
                }
            }
            else {
                auto [dq, xq, cq] = q.front();
                d = dq; x = -xq; c = cq;
                q.pop();
            }
        }
        else {
            auto [dv, xv, cv] = vct[vi];
            d = dv; x = -xv; c = cv;
            vi++;
        }
        curr_c += c;
        while (get<0>(zapyt[i]) <= curr_c && i < z) {
            int k = get<0>(zapyt[i]);
            int nr = get<1>(zapyt[i]);
            zapyt[i] = {k, nr, x + d / 2ll + (long long)(k - (curr_c - c) - 1) * d};

            i++;
        }
        q.emplace(d / 2ll, -x, 2 * c);
    } 

    sort(zapyt.begin(), zapyt.end(), cmp);
    for (int i = 0; i < z; ++i) {
        auto [k, nr, res] = zapyt[i];
        long long g = gcd(res, (long long)(1 << 30));
        cout << res / g << '/' << (1 << 30) / g << '\n';
    }


    return 0;
}