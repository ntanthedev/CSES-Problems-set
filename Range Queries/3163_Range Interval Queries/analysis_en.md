# 3163 - Range Interval Queries

# Solution 1 ($O(n \log n + q \log^2 n)$)

We create a segment tree where each node contains a sorted list of values in the corresponding subtree. We can create the tree in $O(n \log n)$ time using a merge sort like technique.

After that, we can process each query in $O(\log^2 n)$ time by using binary search to calculate the number of values in each segment tree node.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1 << 18;

vector<int> tree[2 * N];

int query(int a, int b, int c, int d) {
    a += N;
    b += N;

    int count = 0;

    while (a <= b) {
        if (a % 2 == 1) {
            count += upper_bound(tree[a].begin(), tree[a].end(), d) -
                     lower_bound(tree[a].begin(), tree[a].end(), c);
            a++;
        }
        if (b % 2 == 0) {
            count += upper_bound(tree[b].begin(), tree[b].end(), d) -
                     lower_bound(tree[b].begin(), tree[b].end(), c);
            b--;
        }
        a /= 2;
        b /= 2;
    }

    return count;
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        tree[N + i] = {x};
    }

    for (int i = N - 1; i >= 1; i--) {
        merge(tree[2 * i].begin(), tree[2 * i].end(), tree[2 * i + 1].begin(),
              tree[2 * i + 1].end(), back_inserter(tree[i]));
    }

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        cout << query(a, b, c, d) << "\n";
    }
}
```

# Solution 2 ($O((n+q) \log n)$)

We create a list of events that includes one event for each array element and two events for each query. We also maintain a segment tree to calculate sums.

The events are created as follows:

* Event $1$: Begin a query with value range $[c,d]$ (processing time $c$)
* Event $2$: Process array value $x$ (processing time $x$)
* Event $3$: End a query with value range $[c,d]$ (processing time $d$)

After creating the events, we sort them and go through them in increasing order of processing times.
If two events have the same processing time, we process them in the order of their event type.

Consider a query where the array range is $[a,b]$ and we want to calculate the number of values between $[c,d]$. We first calculate the number of values between $[1,c-1]$ using the segment tree (event type $1$). Then we process all array values between $[c,d]$ and add them to the segment tree (event type $2$). Finally we calculate the number of values between $[1,d]$ using the segment tree (event type $3$).

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1 << 18;

int tree[2 * N];

void set_val(int pos) {
    pos += N;
    tree[pos] = 1;

    for (pos /= 2; pos >= 1; pos /= 2) {
        tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
    }
}

int get_sum(int a, int b) {
    a += N;
    b += N;

    int sum = 0;
    while (a <= b) {
        if (a % 2 == 1) {
            sum += tree[a++];
        }
        if (b % 2 == 0) {
            sum += tree[b--];
        }
        a /= 2;
        b /= 2;
    }
    return sum;
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> events;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        events.push_back({x, 2, i});
    }

    for (int i = 1; i <= q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        events.push_back({c, 1, a, b, i});
        events.push_back({d, 3, a, b, i});
    }

    sort(events.begin(), events.end());

    vector<int> result(q + 1);

    for (auto event : events) {
        if (event[1] == 1) {
            int sum = get_sum(event[2], event[3]);
            result[event[4]] -= sum;
        }

        if (event[1] == 2) {
            set_val(event[2]);
        }

        if (event[1] == 3) {
            int sum = get_sum(event[2], event[3]);
            result[event[4]] += sum;
        }
    }

    for (int i = 1; i <= q; i++) {
        cout << result[i] << "\n";
    }
}
```