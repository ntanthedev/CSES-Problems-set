# 2165 - Tower of Hanoi

The following solution uses a recursive function that moves $n$ disks from stack $a$ to stack $b$ using stack $c$. The function assumes that all disks in stacks $b$ and $c$ are larger than the $n$ disks in stack $a$ which will be moved.

If $n=1$, the function just moves a disk from stack $a$ to stack $b$. Otherwise, the function recursively moves $n-1$ disks from stack $a$ to stack $c$, then one disk from stack $a$ to stack $b$ and finally $n-1$ disks from stack $c$ to stack $b$.

Using the function, we can solve the problem by moving $n$ disks from the left stack to the right stack using the middle stack. The total number of moves will be $2^n-1$ which is the optimal solution.

Why is the solution optimal? Since we have to move the largest disk from the left stack to the right stack, we have to move all other disks to the middle stack so that the right stack is empty and we can move the largest disk. After that, we have to move all other disks from the middle stack to the right stack.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> moves;

void move(int n, int a, int b, int c) {
    if (n == 1) {
        moves.emplace_back(a, b);
    } else {
        move(n - 1, a, c, b);
        move(1, a, b, c);
        move(n - 1, c, b, a);
    }
}

int main() {
    int n;
    cin >> n;
    move(n, 1, 3, 2);
    cout << moves.size() << "\n";
    for (auto [a, b] : moves) {
        cout << a << " " << b << "\n";
    }
}
```

## References

* [Tower of Hanoi (Wikipedia)](https://en.wikipedia.org/wiki/Tower_of_Hanoi)