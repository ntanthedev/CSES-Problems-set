# 1084 - Apartments

We can solve the problem using a greedy algorithm that goes through the wishes of the applicants in increasing order and gives each applicant the smallest apartment that satisfies the wish (if there is such an apartment available).

A good way to implement the algorithm is to first sort both the wishes and the sizes and then go through the wishes. We also maintain a pointer that is used to efficiently find the smallest apartment for a wish.

The algorithm works because it is always safe to choose the smallest wish for which we can give an apartment and then give the smallest apartment. We could not get a better solution by skipping the smallest wish or giving a larger apartment for the wish.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> wishes(n);
    for (int i = 0; i < n; i++) {
        cin >> wishes[i];
    }
    sort(wishes.begin(), wishes.end());

    vector<int> sizes(m);
    for (int i = 0; i < m; i++) {
        cin >> sizes[i];
    }
    sort(sizes.begin(), sizes.end());

    int count = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < m && sizes[j] < wishes[i] - k) {
            j++;
        }
        if (j < m && sizes[j] <= wishes[i] + k) {
            count++;
            j++;
        }
    }
    cout << count << "\n";
}
```