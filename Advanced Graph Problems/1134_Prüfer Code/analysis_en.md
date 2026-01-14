# 1134 - Prüfer Code

The Prüfer code corresponds to a rooting of the tree where the root is the $n$th
node if we say that the parent of a node is its only neighbor when the node is
deleted. Now, let us call the number of immediate children of each node the
node's *degree*.

If a node's degree is zero, it has no children and thus is a candidate for
deletion. If we store the candidates in a `priority_queue`, the smallest index
in the queue corresponds to the node deleted next. After this, all that is left
to do is to maintain the degrees and the queue between the deletions.

```cpp
#include <iostream>
#include <queue>
using namespace std;

const int N = 200001;
int code[N];
int degree[N];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n - 2; ++i) {
        cin >> code[i];
        degree[code[i]]++;
    }

    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 0) {
            leaves.push(i);
        }
    }

    for (int i = 1; i <= n - 2; ++i) {
        cout << code[i] << ' ' << leaves.top() << '\n';
        leaves.pop();
        degree[code[i]]--;
        if (degree[code[i]] == 0) {
            leaves.push(code[i]);
        }
    }

    cout << leaves.top() << ' ' << n << endl;
}
```

## References

* [Prüfer sequence (Wikipedia)](https://en.wikipedia.org/wiki/Pr%C3%BCfer_sequence)