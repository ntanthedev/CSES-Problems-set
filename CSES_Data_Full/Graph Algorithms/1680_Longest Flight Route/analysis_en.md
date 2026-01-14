# 1680 - Longest Flight Route

We solve the problem by dynamic programming in a directed acyclic graph.

We start by formulating the problem recursively. Let's denote the
length (in nodes) of the longest route from city $x$ to city $n$ by $f(x)$.
We also set $f(x) = -\infty$, if there are no routes from $x$ to $n$.

We have two base cases:

* If $x = n$, then $f(x) = 1$ because there are no directed cycles in the
  flight network.
* If $x \not= n$ and there are no flights from $x$, then $f(x) = -\infty$.

Otherwise we will call the function recursively.
Let's denote the direct flight destinations from $x$ by
$d\_1, \dots, d\_k$. Now $f(x) = 1 + \max\_i f(d\_i)$.
We note that because the flight network is acyclic, the recursion is
well-defined. We also associate with the city $x$, the next city in a
longest path by selecting $d\_i$ that maximizes $f(d\_i)$ and storing it in
the `next_city` array.

We then apply dynamic programming to the recursion by storing the calculated
values of $f(x)$ in the `longest` array.

The time complexity of the solution is $O(n + m)$.

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 100001;
const int INF = 1000000000;
vector<int> g[N];

bool ready[N];
int longest[N];
int next_city[N];
int n;

int f(int x) {
    if (ready[x]) return longest[x];
    ready[x] = true;
    longest[x] = -INF;
    if (x == n) {
        return longest[x] = 1;
    }
    for (int y : g[x]) {
        f(y);
        if (longest[y] + 1 > longest[x]) {
            longest[x] = longest[y] + 1;
            next_city[x] = y;
        }
    }
    return longest[x];
}

int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    if (f(1) < 0) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << f(1) << '\n';
    int x = 1;
    while (x != 0) {
        cout << x << ' ';
        x = next_city[x];
    }
    cout << '\n';
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](http://cses.fi/book),
  Chapter 7.4.2