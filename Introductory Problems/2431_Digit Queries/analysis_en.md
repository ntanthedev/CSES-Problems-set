# 2431 - Digit Queries

We consider blocks of numbers where each number has the same length:

* $[1,9]$ (length $1$)
* $[10,99]$ (length $2$)
* $[100,999]$ (length $3$)
* ...

First we locate the block where position $k$ belongs to. In the code the range of the block is $[a,b]$ and the length of each number inside the block is $c$. After that, we calculate the number $x$ that contains the digit and finally fetch the digit.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int digit(ll k) {
    k--;
    ll a = 1;
    ll b = 9;
    int c = 1;
    while (k >= (b - a + 1) * c) {
        k -= (b - a + 1) * c;
        a = a * 10;
        b = b * 10 + 9;
        c++;
    }
    ll x = a + k / c;
    return to_string(x)[k % c] - '0';
}

int main() {
    int q;
    cin >> q;
    for (int qi = 0; qi < q; ++qi) {
        ll k;
        cin >> k;
        cout << digit(k) << "\n";
    }
}
```