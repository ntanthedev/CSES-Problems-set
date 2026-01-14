# 3399 - Raab Game I

If $a+b>n$, there is no solution because the total number of points cannot exceed the number of turns.

If exactly one player has $0$ points, there is no solution because it is not possible for the other player to win some rounds while all other rounds result in ties.

Otherwise, we can always construct a solution as follows:

* The first player always plays $1,2,\dots,n$
* The second player first plays $a+1,a+2,\dots,a+b$, then $1,2,\dots,a$ and finally $a+b+1,a+b+2,\dots,n$.

In this construction, the first player first loses $b$ times and then wins $a$ times. After these rounds, there are $n-a-b$ ties.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, a, b;
        cin >> n >> a >> b;

        if (a + b > n) {
            cout << "NO\n";
            continue;
        }

        if ((a == 0 || b == 0) && a + b != 0) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << "\n";
        for (int i = 1; i <= b; i++) {
            cout << a + i << " ";
        }
        for (int i = 1; i <= a; i++) {
            cout << i << " ";
        }
        for (int i = a + b + 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << "\n";
    }
}
```