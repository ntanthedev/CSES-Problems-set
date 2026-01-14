# 1202 - Investigation

In this task we are asked to answer various questions about the
minimum-price routes from city $1$ to city $n$. The first of the questions
("what is the minimum price of such a route?") can be answered simply
by Dijkstra's algorithm. The other questions can all be answered
using dynamic programming. Let's only consider the question
"how many minimum-price routes are there?" as all of the three questions
can be solved in a very similar way.

We start by running Dijkstra's algoritm from the city $n$ in a reversed graph.
We store the minimum route prices from each city to $n$ in the $\mathrm{price}$
array.

Let's then formulate the problem recursively. We will denote with
$\mathrm{n\\_min\\_price}(x)$ the number of minimum price routes from $x$ to $n$.

We have two base cases:

* If $x = n$, then $\mathrm{n\\_min\\_price}(x) = 1$ because all the flights
  have positive cost.
* If $x \not= n$ and there are no routes from $x$ to $n$, then
  $\mathrm{n\\_min\\_price}(x) = 0$.

Otherwise we can define the value recursively. Let's consider all flights
from $x$ that are part of a minimum-price route from $x$ to $n$
and denote the end cities of these flights by $y\_1, \dots, y\_k$ (in other words,
for every $y\_i$ it must hold that $\mathrm{price}[x] = \mathrm{price}[y\_i] + p$ where
$p$ is the price of the flight). Now the number of minimum-price routes from $x$
to $n$ starting with the flight corresponding to $y\_i$ is
$\mathrm{n\\_min\\_price}(y\_i)$ so the total number of minimum-price routes is

$$\mathrm{n\\_min\\_price}(x) = \sum\_i \mathrm{n\\_min\\_price}(y\_i).$$

The recursion is well-defined because for every node $x$, the inequality
$\mathrm{price}[x] > \mathrm{price}[y\_i]$ holds.

We then apply dynamic programming to the recursion by memoizing the calculated
values of the function.

The time complexity of the solution is $O(n + m \log m)$.

```cpp
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
using ll = long long;
template <typename T>
using reverse_priority_queue = priority_queue<T, vector<T>, greater<T>>;

const int N = 100001;
const int MOD = 1000000007;
const ll INF = 1e18;

vector<pair<int, int>> g[N];
vector<pair<int, int>> rev_g[N];
ll price[N];
int n;

bool ready[N];
ll n_min_price[N];
ll min_flights[N];
ll max_flights[N];

void f(int x) {
    if (ready[x]) return;
    ready[x] = true;
    if (x == n) {
        n_min_price[x] = 1;
        min_flights[x] = 0;
        max_flights[x] = 0;
        return;
    }
    n_min_price[x] = 0;
    min_flights[x] = INF;
    max_flights[x] = -INF;
    for (auto [y, len] : g[x]) {
        if (price[x] == price[y] + len) {
            f(y);
            n_min_price[x] = (n_min_price[x] + n_min_price[y]) % MOD;
            min_flights[x] = min(min_flights[x], min_flights[y] + 1);
            max_flights[x] = max(max_flights[x], max_flights[y] + 1);
        }
    }
}

int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
        rev_g[b].emplace_back(a, c);
    }

    fill(price, price + n + 1, INF);

    reverse_priority_queue<pair<ll, int>> queue;
    queue.emplace(0, n);
    price[n] = 0;

    while (!queue.empty()) {
        auto [d, x] = queue.top();
        queue.pop();
        if (d > price[x]) continue;
        for (auto [y, len] : rev_g[x]) {
            ll new_d = d + len;
            if (new_d < price[y]) {
                price[y] = new_d;
                queue.emplace(new_d, y);
            }
        }
    }

    f(1);

    cout << price[1] << ' ' << n_min_price[1] << ' ';
    cout << min_flights[1] << ' ' << max_flights[1] << '\n';
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book),
  Chapter 7.4.2