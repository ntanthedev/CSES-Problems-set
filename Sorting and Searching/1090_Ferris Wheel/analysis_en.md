# 1090 - Ferris Wheel

We can solve the problem using a greedy algorithm that on each step places the heaviest child in a gondola. If the lightest child can also placed in the same gondola, this is done and the gondola will have two children. Otherwise the heaviest child will be alone in the gondola.

The algorithm can be implemented by first sorting the weights and then maintaining two pointers to the lightest and heaviest child. Using the pointers, we can always efficiently find the lightest and heaviest child.

The algorithm works because we must anyway place the heaviest child in a gondola, so we can start with that child. It is also optimal to choose the lightest child to be in the same gondola. If we would "save" the lightest child for another gondola, this would never produce a better solution.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    sort(weights.begin(), weights.end());

    int count = 0;
    int i = 0;
    int j = n - 1;
    while (i <= j) {
        if (i < j && weights[i] + weights[j] <= x) {
            count++;
            i++;
            j--;
        } else {
            count++;
            j--;
        }
    }
    cout << count << "\n";
}
```

Note that we could also use another greedy method for choosing the second child: instead of choosing the lightest child, we could also choose the heaviest child that fits in the gondola. It could be easier to see why this method works, but it would be more complex to implement.