# 2216 - Collecting Numbers

If number $x$ is before number $x-1$ in the array, we have to start a new round after collecting number $x-1$.

Using this observation, we can check all pairs of consecutive numbers and count the number of new rounds needed. This can be done efficiently by storing the position of each number in a vector.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pos[x] = i;
    }

    int rounds = 1;
    for (int i = 2; i <= n; i++) {
        if (pos[i] < pos[i - 1]) rounds++;
    }
    cout << rounds << "\n";
}
```