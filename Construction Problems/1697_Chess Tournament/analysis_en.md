# 1697 - Chess Tournament

A straightforward greedy approach works for this problem. A simple proof is
provided below. The approach goes as follows:

At each step, choose the player with the most unscheduled matches. Then, match
it against the player with the second most unscheduled matches and then with
the player with the third most, and so on until the chosen player has all his
remaining matches scheduled. Repeat this procedure until every player has each
one of their matches scheduled.

If at any point there is not enough players to match against the one with the
most unscheduled matches, it is not possible to construct a tournament that
satisfies all players.

We will store the players with their amounts of remaining matches in a
`priority_queue` which allows us to efficiently find the player with the highest
amount of matches left. This solution has a time complexity of $O(M \log n)$
where $M$ represents the sum of the given numbers.

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    priority_queue<pair<int, int>> nodes;

    for (int i = 1; i <= n; ++i) {
        int deg;
        cin >> deg;
        if (deg > 0) {
            nodes.emplace(deg, i);
        }
    }

    vector<pair<int, int>> ans;

    while (!nodes.empty()) {
        auto [d, s] = nodes.top();
        nodes.pop();
        if (nodes.size() < d) {
            cout << "IMPOSSIBLE" << '\n';
            return 0;
        }
        vector<pair<int, int>> others;
        for (int t = 1; t <= d; ++t) {
            others.push_back(nodes.top());
            nodes.pop();
        }
        for (auto [a, b] : others) {
            ans.emplace_back(s, b);
            if (a > 1) {
                nodes.emplace(a - 1, b);
            }
        }
    }

    cout << ans.size() << '\n';
    for (auto [a, b] : ans) {
        cout << a << ' ' << b << '\n';
    }
}
```

## Proof

Let $a$ be one of the players with the largest wish for matches $x\_a$. The
claim is that if a complete solution can be formed, it can also be formed such
that $a$ is paired only with the players having the next largest wishes for the
amount of games in order.

More specifically, given two players $b, c$ with $x\_b \ge x\_c$, if there exists
a solution not containing the match $(a, b)$ but only the match with the player
wishing a smaller (or equal) amount of games, $(a, c)$, then there also exists
a solution instead containing the match $(a, b)$ but not $(a, c)$.

It turns out that this existing solution with match $(a, c)$ can be modified
into the desired form.

Since $x\_b \ge x\_c$, there must exist a player $d \neq a,b,c$ who plays a game
against $b$ but not $c$. This is guaranteed also in the case $x\_b = x\_c$
because $c$ plays a game with $a$ while $b$ does not, so $b$ must have one more
game with someone else.

We can then replace the matches $(a, c)$ and $(b, d)$ in exchange for the
matches $(a, b)$ and $(c, d)$. The total amount of games attended by each
player does not change, and no pair of players play against each other twice
because the matches $(a, b)$ and $(c, d)$ did not exist before.

After choosing all matches for player $a$, we are left with a smaller instance
of the same problem, which is still possible to solve if the original was as
well.

## References

* [Wikipedia (Havel–Hakimi algorithm)](https://en.wikipedia.org/wiki/Havel%E2%80%93Hakimi_algorithm)
* [Wikipedia (Erdős–Gallai theorem)](https://en.m.wikipedia.org/wiki/Erd%C5%91s%E2%80%93Gallai_theorem)