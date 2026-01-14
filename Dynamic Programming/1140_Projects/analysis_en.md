# 1140 - Projects

Let $\mathrm{money}(i)$ denote the maximum amount of money that can be
obtained by attending project $i$ and possibly some other projects before it.
We can use the following recurrence:

$$\mathrm{money}(i) = \max\_{j \le n,\ b\_j < a\_i} \mathrm{money}(j) + p\_i$$

Since $n$ can be large, we need an efficient way to find the project $j$ with
the greatest $\mathrm{money}(j)$ ending before project $i$ starts.
Sorting the projects by either the start or end dates is not sufficient,
because the $\mathrm{money}$ value needs to be computed based on the start date
of a project, but the value only becomes available to other projects
after the end date.

We can use a sweep line approach, where each project is split into two
events: one at the start date and one at the end date. The value
$\mathrm{money}(i)$ is computed at time $a\_i$ according to the maximum value
among projects that have already ended. The current maximum value is
updated once the project ends at time $b\_i$.

To ensure that projects ending on a certain date do not influence projects
starting at the same date, start events are sorted before end events if they
occur on the same date.

The time complexity of this solution is $O(n \log n)$ because of the sort
performed.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct Event {
    int time, project;
    bool is_end;
    bool operator<(Event other) const {
        if (time == other.time) return is_end < other.is_end;
        return time < other.time;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    vector<ll> money(n);
    vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b >> p[i];
        events.push_back({a, i, false});
        events.push_back({b, i, true});
        money[i] = 0;
    }

    sort(events.begin(), events.end());

    ll result = 0;
    for (auto [time, project, is_end] : events) {
        if (is_end) {
            result = max(result, money[project]);
        } else {
            money[project] = result + p[project];
        }
    }

    cout << result << endl;
}
```

## References

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chapter 30