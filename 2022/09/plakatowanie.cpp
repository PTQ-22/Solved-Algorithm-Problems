#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a;
    cin >> n;

    vector<int> heights(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> a >> heights[i];
    }

    stack<int> heights_stack;
    heights_stack.push(-1);

    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (heights[i] > heights_stack.top())
        {
            res++;
        }
        else if (heights[i] < heights_stack.top())
        {
            while (heights[i] < heights_stack.top())
            {
                heights_stack.pop();
            }
            if (heights[i] > heights_stack.top())
            {
                res++;
            }
        }

        heights_stack.push(heights[i]);
    }

    cout << res;

    return 0;
}
