# 3420 - Distinct Values Subarrays

We calculate the number of valid subarrays that end at each array position. The sum of these values is the answer to the problem.

The variable `left_pos` stores the left position of a valid subarray. When we encounter a number that has appeared before in the array, we update this variable if necessary.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    map<int, int> last_pos;
    int left_pos = 1;
    ll count = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        left_pos = max(left_pos, last_pos[x] + 1);
        count += i - left_pos + 1;
        last_pos[x] = i;
    }

    cout << count << "\n";
}
```