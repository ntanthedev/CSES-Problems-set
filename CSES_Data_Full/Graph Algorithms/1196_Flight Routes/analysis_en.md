# 1196 - Flight Routes

We start by presenting a slow algorithm to the problem
and then modify it to make it faster.

We first try to solve the problem by going through all possible routes in the
map in the order of increased length. This may be done by maintaining a
priority queue of routes, containing the length and the last city of each
route. We will always take the shortest route $r$ from the queue and
add all possible routes from $r$ extended by one flight back into the queue.
Now the $k$ shortest routes from $1$ to $n$ are
the $k$ first routes that we take from the queue and that end at $n$. (Note
that as there might be multiple routes from $1$ to $n$ with the same length,
the $k$ shortest routes might not be uniquely defined.)

Let $x$ be any city. Let's also call a route good if it was extended from the
first $k$ routes reaching $x$ (without the extension visiting $x$ again
after this) and bad if the route is not good but still
visits $x$. To make the solution faster, we note that we can ignore
(i.e. take the routes from the queue without adding the extensions back)
all bad routes and still find some $k$ shortest routes from $1$ to $n$.
To prove this, let's start with a set $K$ of some $k$ shortest
routes from $1$ to $n$ and let's assume there is a route $r \in K$ that is bad.
We then crete new routes $s\_1, \dots, s\_k$ from $r$ where $s\_i$
is created by replacing the prefix of $r$ until the last occurrence of $x$
with the $i$th route reaching $x$. All of the $s\_i$ are now good and at most
as long as $r$. Moreover, we can select $s\_i \not \in K$ and replace $r$
with it. By repeating this procedure, we will be left
with $k$ shortest routes, none of which is bad.
Therefore ignoring bad routes does not prevent us from
finding some $k$ shortest routes from $1$ to $n$.

The complexity of the solution is $O(n + km \log km)$.

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;
template <typename T>
using reverse_priority_queue = priority_queue<T, vector<T>, greater<T>>;
const int N = 100001;
const int K = 10;
vector<pair<int, int>> g[N];
int visited[N];
ll dist[K];

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
    }

    reverse_priority_queue<pair<ll, int>> q;
    q.emplace(0, 1);

    while (!q.empty()) {
        auto [d, x] = q.top();
        q.pop();
        if (visited[x] >= k) {
            continue;
        }
        if (x == n) {
            dist[visited[x]] = d;
        }
        ++visited[x];
        for (auto [y, len] : g[x]) {
            q.emplace(d + len, y);
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << dist[i] << ' ';
    }
    cout << '\n';
}
```