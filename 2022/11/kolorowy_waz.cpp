// https://sio2.mimuw.edu.pl/c/oi30-1/p/kol/
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXM = 2002;
int snacks_grid[MAXM][MAXM];
int counter_grid[MAXM][MAXM];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, p, n;
    cin >> m >> p >> n;

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            snacks_grid[i][j] = -1;
        }
    }

    int w, k, c;
    for (int i = 1; i <= p; ++i)
    {
        cin >> w >> k >> c;
        snacks_grid[w][k] = c;
    }

    vector<int> snacks;
    deque<pair<int, int>> snake;
    int counter = 1;

    snacks.push_back(0);
    snake.emplace_back(1, 1);
    counter_grid[1][1] = counter;

    char order;
    while (n--)
    {
        cin >> order;
        if (order == 'Z')
        {
            cin >> w >> k;
            if (counter_grid[w][k])
            {
                auto head = snake.back();
                int d = counter_grid[head.first][head.second] - counter_grid[w][k];
                cout << snacks[snacks.size() - d - 1] << '\n';
            }
            else {
                cout << -1 << '\n';
            }
        }
        else
        {
            int dx = 0, dy = 0;
            switch (order)
            {
            case 'G':
                dy = -1;
                break;
            case 'D':
                dy = 1;
                break;
            case 'L':
                dx = -1;
                break;
            case 'P':
                dx = 1;
                break;
            }
            auto head = snake.back();
            head = {head.first + dy, head.second + dx};
            snake.push_back(head);
            counter_grid[head.first][head.second] = ++counter;
            if (snacks_grid[head.first][head.second] == -1) // no snack
            {
                auto tail = snake.front();
                if (tail != head) {
                    counter_grid[tail.first][tail.second] = 0;
                }
                snake.pop_front();
            }
            else // snack
            {
                snacks.push_back(snacks_grid[head.first][head.second]);
                snacks_grid[head.first][head.second] = -1;
            }
        }
    }

    return 0;
}