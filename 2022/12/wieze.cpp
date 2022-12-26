#include <bits/stdc++.h>
using namespace std;

struct cmp
{
    bool operator()(const string &a, const string &b) const
    {
        if (a.size() > b.size())
            return true;
        if (a.size() == b.size() && a.compare(b) < 0)
            return true;
        return false;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    set<string, cmp> cont;
    for (int i = 0; i < n; ++i)
    {
        string val = arr[i];
        auto itr = cont.find(val);
        while (itr != cont.end())
        {
            cont.erase(itr);
            val += val;
            itr = cont.find(val);
        }
        cont.insert(val);
    }
    cout << cont.begin()->size() << '\n';
    return 0;
}