#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int bin_search(vector<ll>& przed, ll x)
{
    int start = 0;
    int end = przed.size() - 1;
    while (start < end) {
        int mid = (start + end) / 2;
        if (przed[mid] >= x) {
            end = mid;
        } 
        else {
            start = mid + 1;
        }
    }
    return start;
}

ll podz(ll n, ll d)
{
    if (d == 2) return n / d;
    ll res = n / d;
    if ((n % d) > 1) res++;
    return res;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        ll N, a, b;
        cin >> N >> a >> b;

        ll maxi = max(a * N, b * N);
        vector<ll> przedz = {{1, 1}};
        if (N == 1) {
            cout << min(a, b) << '\n';
            continue;
        }
        ll pot = 1;
        ll pre = 1;
        ll kon = 1;
        while (pot < maxi) {
            pot *= N;
            kon += pot;
            przedz.push_back(pre + 1ll);
            pre = kon;
        }

        auto b_prz = przedz[bin_search(przedz, b + 1) - 1];
        auto a_prz = przedz[bin_search(przedz, a + 1) - 1];
        if (a_prz != b_prz) {
            if (a > b) {
                b_prz = przedz[bin_search(przedz, b + 1) - 1];
                while (true) {
                    a = podz(a, N);
                    a_prz = przedz[bin_search(przedz, a + 1) - 1];
                    if (a_prz == b_prz) {
                        break;
                    }
                }
            }
            else {
                a_prz = przedz[bin_search(przedz, a + 1) - 1];
                while (true) {
                    b = podz(b, N);
                    b_prz = przedz[bin_search(przedz, b + 1) - 1];
                    if (a_prz == b_prz) {
                        break;
                    }
                }
            }
        }

        while (a != b)
        {
            a = podz(a, N);
            b = podz(b, N);
        }
        cout << a << '\n';
    }

    return 0;
}