# 1632 - Movie Festival II

We have already solved a special case of the problem where $k=1$, i.e., the movie club has only one member. In this case we can sort the movies by ending time, go through the movies and always choose the next movie we can watch. It turns out that we can use the same idea also in this problem.

We use a multiset `times` that stores the earliest time each club member can begin to watch the next movie. Initially each time is $0$. Then at each movie we find a club member who can watch the movie. If there are several possibilities, we choose the member who has most recently finished the previous movie. If nobody can watch the movie, then we skip the movie.

There will be a fixed number of $O(\log n)$ operations for each movie, so the algorithm works in $O(n \log n)$ time.

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> events;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        events.emplace_back(b, a);
    }
    sort(events.begin(), events.end());

    multiset<int> times;
    for (int i = 1; i <= k; i++) {
        times.insert(0);
    }

    int answer = 0;
    for (auto [b, a] : events) {
        auto it = times.upper_bound(a);
        if (it == times.begin()) continue;
        answer++;
        it--;
        times.erase(it);
        times.insert(b);
    }

    cout << answer << "\n";
}
```