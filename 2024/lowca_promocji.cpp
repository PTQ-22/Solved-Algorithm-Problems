#include <bits/stdc++.h>
using namespace std;

bool cmp(tuple<pair<int, int>, int, int>& a, tuple<pair<int, int>, int, int>& b)
{
    return get<1>(a) < get<1>(b);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> ceny_pocz(n + 1);
    vector<bool> calc(n + 1);
    for (int i = 1; i <= n; ++i) cin >> ceny_pocz[i];

    vector<tuple<pair<int, int>, int, int>> promocje;
    for (int i = 0; i < m; ++i) {
        int nr, p, k, d;
        cin >> nr >> p >> k >> d;
        if (ceny_pocz[nr] - d > 0) {
            promocje.emplace_back(make_pair(p, k), nr, ceny_pocz[nr] - d);
        }
    }
    sort(promocje.begin(), promocje.end());
    priority_queue<tuple<int, int, int, int>> pq;

    long long maxi = -1;
    long long suma = 0;
    for (int i = 0; i < promocje.size(); ++i) {
        auto curr = promocje[i];
        auto [pk, nr, d] = curr;
        while (pq.size() && pk.first > -get<0>(pq.top())) {
            suma -= get<1>(pq.top());
            pq.pop();
        }
        suma += (long long)(d);
        pq.push({-pk.second, d, nr, pk.first});
        maxi = max(maxi, suma);
    }
    while (pq.size()) pq.pop();
    vector<tuple<int, int, int>> policzone;
    suma = 0;
    for (int i = 0; i < promocje.size(); ++i) {
        auto curr = promocje[i];
        auto [pk, nr, d] = curr;
        while (pq.size() && pk.first > -get<0>(pq.top())) {
            suma -= get<1>(pq.top());
            pq.pop();
        }
        suma += (long long)(d);
        pq.push({-pk.second, d, nr, pk.first});
        if (suma == maxi) {
            while (pq.size()) {
                policzone.push_back({get<2>(pq.top()), get<3>(pq.top()), get<1>(pq.top())});
                pq.pop();
            }
            break;
        }
    }

    vector<int> prz;

    long long price = 0;
    for (auto [i, pcz, d] : policzone) {
        price += (long long)(ceny_pocz[i] - d);
        calc[i] = true;
        prz.push_back(pcz);
    }
    for (int i = 1; i <= n; ++i) {
        if (!calc[i]) price += (long long)(ceny_pocz[i]);
    }
    sort(prz.begin(), prz.end(), greater<int>());
    if (prz.size())
        cout << price << ' ' << prz[0] << '\n';
    else {
        cout << price << ' ' << 1 << '\n';
    }

    return 0;
}