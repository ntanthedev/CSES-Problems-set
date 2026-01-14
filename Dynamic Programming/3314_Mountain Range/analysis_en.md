# 3314 - Mountain Range

# Solution 1 (O(n log n))

We process the mountains in order of decreasing height and calculate the maximum length of a route that ends at each mountain.

For each mountain, we find the nearest higher mountain to the left and to the right. Since the mountains are processed in order of decreasing height, the maximum route length has already been calculated for both of these mountains. The longest route to the current mountain can be created by choosing the longest route to the left or right mountain and adding the current mountain to it.

There may be several mountains with the same height which makes the situation more complex. For this reason, we maintain an additional list of updates and apply the updates whenever the current height differs from the previous height.

```cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> heights;
    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        heights.emplace_back(h, i);
    }
    sort(heights.rbegin(), heights.rend());

    map<int, int> counts;
    counts[0] = 0;
    counts[n + 1] = 0;

    int prev_height = 0;
    vector<pair<int, int>> updates;
    int result = 0;

    for (auto [height, pos] : heights) {
        if (height != prev_height) {
            for (auto [pos, count] : updates) {
                counts[pos] = count;
            }
            updates.clear();
            prev_height = height;
        }

        auto it = counts.upper_bound(pos);
        int next_pos = it->first;
        it--;
        int prev_pos = it->first;

        int new_count = max(counts[prev_pos], counts[next_pos]) + 1;
        updates.emplace_back(pos, new_count);
        result = max(result, new_count);
    }

    cout << result << "\n";
}
```

# Solution 2 (O(n))

It is also possible to solve the problem in linear time by using a different method for processing the mountains.

First, we find the nearest higher mountain to the left and to the right for each mountain, which can be done in linear time using stacks. We then create a graph that determines the order in which the mountains should be processed.

Next, we process the graph using topological sorting and calculate the maximum route length for each mountain, applying the same idea as in the previous solution.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1000000001;

int main() {
    int n;
    cin >> n;

    vector<int> heights(n + 2);
    heights[0] = INF;
    heights[n + 1] = INF;
    for (int i = 1; i <= n; i++) {
        cin >> heights[i];
    }

    vector<vector<int>> after(n + 2);

    vector<int> left_stack;
    left_stack.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (heights[i] >= heights[left_stack.back()]) {
            left_stack.pop_back();
        }
        after[left_stack.back()].push_back(i);
        left_stack.push_back(i);
    }

    vector<int> right_stack;
    right_stack.push_back(n + 1);
    for (int i = n; i >= 1; i--) {
        while (heights[i] >= heights[right_stack.back()]) {
            right_stack.pop_back();
        }
        after[right_stack.back()].push_back(i);
        right_stack.push_back(i);
    }

    vector<int> count(n + 2);
    vector<int> result(n + 2);

    vector<int> queue;
    queue.push_back(0);
    queue.push_back(n + 1);

    int answer = 0;
    for (int i = 0; i < queue.size(); i++) {
        int pos = queue[i];
        for (auto next_pos : after[pos]) {
            result[next_pos] = max(result[next_pos], result[pos] + 1);
            answer = max(answer, result[next_pos]);
            count[next_pos]++;
            if (count[next_pos] == 2) {
                queue.push_back(next_pos);
            }
        }
    }
    cout << answer << "\n";
}
```