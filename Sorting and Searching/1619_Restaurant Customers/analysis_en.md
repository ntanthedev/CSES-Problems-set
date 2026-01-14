# 1619 - Restaurant Customers

We create two events for each customer: an arrival event and a leaving event. Each event is a pair of two values: a time and a change in the number of customers ($1$ for arrival and $-1$ for leaving).

After that, we sort the events by time and go through them. When the events are sorted, it is easy to keep track of the number of customers and maintain the highest number.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> events;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        events.emplace_back(a, 1);
        events.emplace_back(b, -1);
    }
    sort(events.begin(), events.end());

    int count = 0;
    int high = 0;
    for (auto [t, d] : events) {
        count += d;
        high = max(high, count);
    }
    cout << high << "\n";
}
```