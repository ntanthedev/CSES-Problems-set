# 1630 - Tasks and Deadlines

We sort the tasks by duration and process them in that order. Surprisingly, the deadlines of the tasks do not matter at all when choosing the order.

To see why the algorithm works, consider two tasks $t\_1 = (a\_1,d\_1)$ and $t\_2 = (a\_2,d\_2)$, where $a\_1$ and $a\_2$ are durations and $d\_1$ and $d\_2$ are deadlines. Suppose that we process $t\_2$ directly after $t\_1$ and $a\_1 > a\_2$. If we start to process $t\_1$ at time $x$, the total reward for the tasks will be
$$d\_1-(x+a\_1) + d\_2-(x+a\_1+a\_2) = d\_1+d\_2-2x-2 a\_1 - a\_2.$$
Then, if we swap the order of the tasks and process first $t\_2$ and then $t\_1$, the total reward will be
$$d\_2-(x+a\_2) + d\_1-(x+a\_1+a\_2) = d\_1+d\_2-2x-a\_1 - 2 a\_2.$$
Since $a\_1 > a\_2$, we get more reward after swapping the tasks. Thus, whenever we have two tasks one after another and the first task takes more time than the second tasks, we should swap them. For this reason the optimal solution is to process the tasks sorted by duration.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> tasks;
    for (int i = 1; i <= n; i++) {
        int duration, deadline;
        cin >> duration >> deadline;
        tasks.emplace_back(duration, deadline);
    }
    sort(tasks.begin(), tasks.end());

    ll time = 0;
    ll reward = 0;
    for (auto [duration, deadline] : tasks) {
        time += duration;
        reward += deadline - time;
    }
    cout << reward << "\n";
}
```