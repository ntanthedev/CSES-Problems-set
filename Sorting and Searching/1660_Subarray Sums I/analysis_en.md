# 1660 - Subarray Sums I

Since each array element is positive, we can use the two pointers technique to solve the problem.

We maintain a subarray that initially only contains the first element of the array. On each round, we first increase the right pointer as long as the sum of the subarray is less than $x$. Then, if the sum is exactly $x$, we have found one solution. Finally, we increase the left pointer.

The algorithm works in $O(n)$ time, because we increase both the left and right pointer $O(n)$ times.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int left = 0;
    int right = 0;
    int sum = a[0];
    int count = 0;

    while (left < n) {
        while (sum < x && right + 1 < n) {
            right++;
            sum += a[right];
        }
        if (sum == x) {
            count++;
        }
        sum -= a[left];
        left++;
    }

    cout << count << "\n";
}
```