# 2220 - Counting Numbers

Let us first simplify the problem to only one variable. Define a function
$\mathrm{count}(x)$ to equal the amount of integers on the interval $[0, x]$
that have no two adjacent equal digits. The answer can then be found by
computing $\mathrm{count}(b) - \mathrm{count}(a - 1)$.

We will compute the function by recursively choosing one digit of the integer at
a time. The parameters of the recursive function, or the context needed to
compute the total amount of integers that can still be chosen, are:

* $i$: The position of the next digit, starting from $0$ at the most significant
  digit in $x$.
* $\mathrm{prev}$: The previous digit chosen (if applicable).
* $\mathrm{equal}$: Whether all previously chosen digits are equal to the
  respective digits in $x$. This should be known so that no integers greater
  than $x$ are counted. After the first nonequal digit, there is no limit to the
  rest of the digits that can be chosen.
* $\mathrm{empty}$: Whether there has been no nonzero digit chosen yet, meaning
  that the prefix is empty. Any amount of zeros can be adjacent to each other
  before the proper start of the integer.

We then try each option for the next digit, $0,\dots,9$, check that the total
integer does not exceed $x$, and ensure that the digit is not the same as the
previous one. The parameters are updated appropriately and we can then recurse
to the next digit and add the result to the total.

The case $i=n$, where $n$ is the amount of digits in $x$, means that we have
successfully set all digits and found one valid integer.

The results of the function are memoized in a lookup table. There are at most
$(n + 1) \cdot 10 \cdot 2 \cdot 2$ different combinations of parameters to the
function, so the time complexity when using an `std::map` for the lookup table
is $O(\log x \log \log x)$.

```cpp
#include <array>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

string s;
map<array<int, 4>, ll> lookup;

ll recurse(int i, int prev, bool equal, bool empty) {
    if (i == (int)s.size()) return 1;

    array<int, 4> params{i, prev, equal, empty};
    if (lookup.count(params)) return lookup[params];

    ll result = 0;
    for (int d = 0; d < 10; ++d) {
        if (equal && d > s[i] - '0') break;
        if (!empty && d == prev) continue;
        result += recurse(i + 1, d, equal && d == s[i] - '0', empty && d == 0);
    }

    lookup[params] = result;
    return result;
}

ll count(ll x) {
    if (x < 0) return 0;
    s = to_string(x);
    lookup.clear();
    return recurse(0, 0, true, true);
}

int main() {
    ll a, b;
    cin >> a >> b;
    cout << count(b) - count(a - 1) << endl;
}
```