# 1070 - Permutations

The case $n=1$ is simple and there are no solutions for $n=2$ and $n=3$. If $n \ge 4$, there is always a solution. The following code uses a construction that also works for $n=4$. Some other constructions require that $n=4$ is handled as a special case.

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << "1\n";
        return 0;
    }
    if (n == 2 || n == 3) {
        cout << "NO SOLUTION\n";
        return 0;
    }
    for (int i = n / 2; i >= 1; i--) {
        cout << i << " " << i + n / 2 << " ";
    }
    if (n % 2 == 1) cout << n << " ";
    cout << "\n";
}
```