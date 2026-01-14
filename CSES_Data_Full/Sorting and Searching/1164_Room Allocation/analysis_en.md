# 1164 - Room Allocation

We create two events for each customer: an arrival event and a departure event. Then we sort the events by time and process them.

We maintain a data structure that contains all free rooms. When a customer arrives, we give an arbitrary free room for them. However, if there are no free rooms, we increase the number of rooms by one before giving the room. Then, when the customer leaves, their room becomes free again.

In the following code we use a vector to store the list of free rooms and always choose the last room in the vector because it is easy to remove.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> events;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        events.push_back({a, 1, i});
        events.push_back({b, 2, i});
    }

    sort(events.begin(), events.end());

    vector<int> rooms;
    int count = 0;
    vector<int> choice(n + 1);

    for (auto e : events) {
        if (e[1] == 1) {
            if (rooms.empty()) {
                count++;
                rooms.push_back(count);
            }
            choice[e[2]] = rooms.back();
            rooms.pop_back();
        }
        if (e[1] == 2) {
            rooms.push_back(choice[e[2]]);
        }
    }

    cout << count << "\n";
    for (int i = 1; i <= n; i++) {
        cout << choice[i] << " ";
    }
    cout << "\n";
}
```