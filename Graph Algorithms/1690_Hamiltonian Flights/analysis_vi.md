# 1690 - Các chuyến bay Hamilton

Ta giải bài toán trong thời gian $O(2^n n^2)$ bằng quy hoạch động.
Ta tính, với mỗi thành phố $c$ và tập con $S$ của các thành phố,
số cách ta có thể đến thành phố $c$ từ thành phố $1$
sao cho ta ghé thăm mỗi thành phố trong $S$ đúng một lần.

Ta biểu diễn mỗi tập con các thành phố dưới dạng một mặt nạ bit gồm $n$ bit.
Với mỗi mặt nạ bit như vậy, ta duyệt qua tất cả các cách để chọn
thành phố cuối cùng và thành phố trước đó trên tuyến đường.
Có $O(2^n)$ tập con khả dĩ của các thành phố và
$O(n^2)$ cách để chọn thành phố cuối cùng và thành phố trước đó.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int M = 1000000007;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> count(n, vector<int>(n));

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        count[a][b]++;
    }

    vector<vector<ll>> ways(1 << n, vector<ll>(n));
    ways[1][0] = 1;

    for (int mask = 2; mask < (1 << n); mask++) {
        vector<int> nodes;
        for (int node = 0; node < n; node++) {
            if (mask & (1 << node)) {
                nodes.push_back(node);
            }
        }

        for (auto last : nodes) {
            for (auto prev : nodes) {
                ways[mask][last] +=
                    count[prev][last] * ways[mask ^ (1 << last)][prev];
            }
            ways[mask][last] %= M;
        }
    }

    cout << ways[(1 << n) - 1][n - 1] << "\n";
}
```
