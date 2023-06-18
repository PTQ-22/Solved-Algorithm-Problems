#include <bits/stdc++.h>
using namespace std;

constexpr int BASE = 1 << 17;
int tree[2 * BASE];

void insert(int v, int x)
{
    v += BASE;
    tree[v] = x;
    v /= 2;
    while (v > 0) {
        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        v /= 2;
    }
}

int query(int a, int b)
{
    a += (BASE - 1);
    b += (BASE + 1);
    int res = INT32_MAX;
    while (a / 2 != b / 2)
    {
        if (!(a & 1)) res = min(res, tree[a + 1]);
        if (b & 1) res = min(res, tree[b - 1]);
        a /= 2;
        b /= 2;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 2 * BASE; ++i) tree[i] = INT32_MAX;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        insert(i, x);
    } 
    while (q--)
    {
        string text;
        cin >> text;
        if (text[0] == 'q') {
            string aa = "", bb = "";
            bool is_a = true;
            for (int i = 6; i < text.size() - 1; i++) {
                if (text[i] == ',') {
                    is_a = false;
                    continue;
                }
                if (is_a) aa += text[i];
                else bb += text[i];
            }
            int a = stoi(aa);
            int b = stoi(bb);
            cout << query(a, b) << '\n';
        }
        else {
            vector<int> idx_to_shift;
            string curr = "";
            for (int i = 6; i < text.size(); i++) {
                if (text[i] == ',' || text[i] == ')') {
                    idx_to_shift.push_back(stoi(curr));
                    curr = "";
                    continue;
                }
                curr += text[i];
            }
            vector<int> to_shift;
            for (int i : idx_to_shift) to_shift.push_back(query(i, i));
            to_shift.push_back(to_shift.front());
            for (int i = 0; i < idx_to_shift.size(); ++i) {
                insert(idx_to_shift[i], to_shift[i + 1]);
            }

            // for (int i = 1; i <= n; ++i) {
            //     cout << query(i , i) << ' ';
            // }
            // cout << '\n';
        }
    }
    return 0;
}