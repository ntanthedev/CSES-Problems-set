# 2207 - Grundys Game

## Solution 1

Let $\textrm{grundy}[x]$ denote the Grundy number of a heap that has $x$ coins,
and let $\oplus$ denote the xor operator.

When we divide a heap of $x$ coins into heaps of $a$ and $b$ coins, there will
be two subgames whose Grundy numbers are $\textrm{grundy}[a]$ and
$\textrm{grundy}[b]$, so the Grundy number after the move is
$\textrm{grundy}[a] \oplus \textrm{grundy}[b]$.

To calculate $\textrm{grundy}[x]$, we go through all possible ways to divide a
heap of $x$ coins into two heaps, calculate the Grundy number of each move and
then find their mex value, i.e., the smallest nonnegative integer that doesn't
appear among the numbers.

The solution works but it is too slow because it is quadratic and $N$ can be up
to $10^6$. However, we can study the problem using the solution.

```cpp
#include <iostream>
#include <set>
using namespace std;
const int N = 1000000;
int grundy[N + 1];

int main() {
    for (int i = 1; i <= N; i++) {
        set<int> s;
        for (int j = 1; i - j > j; j++) {
            s.insert(grundy[j] ^ grundy[i - j]);
        }
        grundy[i] = 0;
        while (s.count(grundy[i])) {
            grundy[i]++;
        }
    }

    int t;
    cin >> t;
    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        cout << (grundy[n] ? "first" : "second") << "\n";
    }
}
```

## Solution 2

By studying the first solution, we can notice that $1222$ is the last state
whose Grundy number is zero, i.e., we are in a losing position. Thus, it
suffices to calculate the Grundy numbers of states $0 \dots 1222$ because we
always win if we have more than $1222$ coins.

Note that our search only proves that $1222$ is the last losing position among
states $0 \dots 10^6$. However, it is known that this also holds for states
$0 \dots 2^{35}$. Nobody knows if there is a losing position after that.

```cpp
#include <iostream>
#include <set>
using namespace std;
const int N = 1222;
int grundy[N + 1];

int main() {
    for (int i = 1; i <= N; i++) {
        set<int> s;
        for (int j = 1; i - j > j; j++) {
            s.insert(grundy[j] ^ grundy[i - j]);
        }
        grundy[i] = 0;
        while (s.count(grundy[i])) {
            grundy[i]++;
        }
    }

    int t;
    cin >> t;
    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        bool win = n > N || grundy[n];
        cout << (win ? "first" : "second") << "\n";
    }
}
```

## References

* [Grundy's game (Wikipedia)](https://en.wikipedia.org/wiki/Grundy%27s_game)
* [A. Flammenkamp: Sprague-Grundy values of Grundy's game](https://wwwhomes.uni-bielefeld.de/achim/grundy.html)