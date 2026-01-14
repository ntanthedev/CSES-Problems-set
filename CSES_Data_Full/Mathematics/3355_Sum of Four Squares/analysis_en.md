# 3355 - Sum of Four Squares

Let $N=10^7$ denote the maximum value of $n$.

We first find all integers between $0$ and $N$ that can be expressed as a sum of two squares. This can be done in $O(N)$ time. For each such integer $x=a^2+b^2$, we store the first number $a$ and the second number $b$.

After that, we can find a solution for any $n$ in $O(n)$ time by finding a number $x$ such that both $x$ and $n-x$ can be expressed as a sum of two squares. It can be shown that there is always a solution.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e7;

int main() {
    int t;
    cin >> t;

    vector<bool> can(N + 1);
    vector<int> first(N + 1), second(N + 1);
    for (int a = 0; a * a <= N; a++) {
        for (int b = 0; a * a + b * b <= N; b++) {
            int x = a * a + b * b;
            can[x] = true;
            first[x] = a;
            second[x] = b;
        }
    }

    while (t--) {
        int n;
        cin >> n;
        for (int x = 0; x <= n; x++) {
            if (can[x] && can[n - x]) {
                cout << first[x] << " " << second[x] << " ";
                cout << first[n - x] << " " << second[n - x] << "\n";
                break;
            }
        }
    }
}
```

## References

* [Lagrange's four-square theorem (Wikipedia)](https://en.wikipedia.org/wiki/Lagrange%27s_four-square_theorem)