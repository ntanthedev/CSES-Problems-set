# 1628 - Meet in the Middle

A straightforward algorithm which goes through all subsets would run in $O(2^n)$
time. As $2^{40}\approx1.1\cdot10^{12}$, the solution is too slow. We will have
to come up with something a bit more clever, and as the name suggests, the
technique needed is called *meet in the middle*. With meet in the middle, the
time complexity can be reduced to $O(n2^{n/2})$, or even $O(2^{n/2})$.

Meet in the middle is a somewhat abstract technique that can be applied to a
variety of problems in different ways. The general idea, though, is to split the
problem in half, solve both halves separately, and merge the halves together to
produce the final answer. The problem of finding the amount of subsets that sum
to a given constant is a classic example of where this technique can be applied.

To utilize meet in the middle, we will have to divide the array in half. This may
be done by simply selecting the first $\lfloor { \frac n 2 } \rfloor$ numbers
into the first half and the rest into the second.

After this we will calculate and store the sums of each subset, for both halves
separately. This is done in $O(2^{n/2})$ time. What's left is to figure out how
to merge the subset information to calculate the amount of subsets in the
original array that sum to $x$.

Let us first sort both of the subset sum arrays. This takes

$$O(2^{n/2}\log(2^{n/2}))=
O(2^{n/2}\cdot(n/2)\cdot\log 2)=
O(n2^{n/2})$$

time. Now that the arrays are sorted, we will traverse the first array forwards.
Turns out we can maintain a pointer to the second array that always decreases
when we move forwards in the first array. This is because if the element in the
first array grows larger, then the matching element in the second array has to
get smaller in order to still sum to $x$. Thus, the time it takes to solve this
part is linear in the length of the arrays, that is, it takes $O(2^{n/2})$ time.

Note that some subset sums might appear multiple times in the arrays. This means
that, for each element in the first array, there may be more than one matching
element in the second array. We will take this into account by processing all
equal elements at once.

In its entirety, the algorithm takes $O(2^{n/2}+n2^{n/2})=O(n2^{n/2})$ time. The
time complexity could be improved to just $O(2^{n/2})$ if we used hash tables
instead of sorting the arrays.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// Returns a list of all subset sums, in sorted order.
vector<ll> subsets(vector<int> x) {
    int n = x.size();
    vector<ll> ret(1 << n);
    for (int m = 0; m < (1 << n); ++m) {
        for (int j = 0; j < n; ++j) {
            if ((1 << j) & m) ret[m] += x[j];
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    auto a = subsets(vector<int>(t.begin(), t.begin() + n / 2));
    auto b = subsets(vector<int>(t.begin() + n / 2, t.end()));

    ll r = 0;
    int m = a.size(), bi = b.size() - 1;

    for (int i = 0, j = 0; i < m; i = j) {
        while (j < m && a[i] == a[j]) ++j;
        while (bi >= 0 && a[i] + b[bi] > x) --bi;
        while (bi >= 0 && a[i] + b[bi] == x) {
            r += j - i;
            bi--;
        }
    }

    cout << r << '\n';
}
```