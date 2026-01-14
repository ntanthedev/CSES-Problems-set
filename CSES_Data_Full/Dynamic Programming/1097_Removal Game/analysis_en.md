# 1097 - Removal Game

The game is a kind of zero-sum game, as any number chosen by one player is an
equivalent loss to the other. To make the game fully symmetric, let us define
the score of the player making the next move as the sum of elements chosen by
them minus the the sum of elements chosen by the other player.

In this variation there is no need to keep count of the players' scores
separately. The current player always tries to maximize the score, and when
moving to the next player, the total score is negated, which the other player
then also tries to maximize.

For an optimal strategy, the current player should choose the move which
maximizes the score that can be achieved by the end of the game regardless of
the other player's moves. This approach is generally called minimax. Dynamic
programming is a natural way to implement it, because the worst case scores
that each move lead to can be computed beforehand as smaller subproblems.

Define the function $\mathrm{score}(l, r)$ as the maximum score the first player
can achieve, when the game is played on the list $x\_l, x\_{l+1}, \dots, x\_r$.

After one move, the game reduces to an equivalent one with either the left or
right number removed, and some difference in the score. The score of the smaller
game is negated as the roles are reversed.

$$\mathrm{score}(l, r) = \max(x\_l - \mathrm{score}(l+1, r), x\_r -
\mathrm{score}(l, r-1))$$

In the base case, when $l = r$, the first player has to choose the only number.

$$\mathrm{score}(l, l) = x\_l$$

A suitable order for computing these scores with dynamic programming is in
increasing order of length, or $r - l + 1$. A one-dimensional DP array is enough
since the recursion only refers to subproblems that have the previous length.

Finally, we must convert the obtained score back into the form required by the
problem statement: the score of the first player. Say $a, b$ are the scores of
the first and second player, respectively. The result we have obtained is
$r = a - b$. We also know the total sum of all numbers in the list,
$\mathrm{sum} = a + b$. Adding these two values together, we get

$$r + \mathrm{sum} = (a - b) + (a + b) = 2a.$$

This is then divided by two to get the desired answer.

The time complexity of this solution is $O(n^2)$ because each value of
the $\mathrm{score}$ function is computed in constant time.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const int N = 5000;
int x[N];
ll score[N];

int main() {
    int n;
    cin >> n;

    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        score[i] = x[i];
        sum += x[i];
    }

    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            int r = l + len - 1;
            score[l] = max(x[l] - score[l + 1], x[r] - score[l]);
        }
    }

    cout << (sum + score[0]) / 2 << endl;
}
```

## References

* [Minimax (Wikipedia)](https://en.wikipedia.org/wiki/Minimax)