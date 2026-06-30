# 3397 - Thứ Tự Hoán Vị

# Nhiệm vụ thứ nhất

Cho $n$ và $k$, nhiệm vụ của ta là tìm $p(n,k)$, tức là hoán vị thứ $k$ (theo thứ tự từ điển) của $1 \dots n$.

Nếu $k$ nằm giữa $1$ và $(n-1)!$, số đầu tiên là $1$. Nếu $k$ nằm giữa $(n-1)!+1$ và $2(n-1)!$, số đầu tiên là $2$. Tổng quát, số đầu tiên là
$$\left\lfloor \frac{k-1}{(n-1)!} \right\rfloor + 1.$$

Ta có thể tìm lần lượt từng số bằng cùng ý tưởng. Sau mỗi bước, ta loại số đã chọn khỏi danh sách các số khả dụng.

# Nhiệm vụ thứ hai

Cho $n$ và $p(n,k)$, nhiệm vụ của ta là tìm $k$.

Ban đầu $k=1$. Nếu số đầu tiên là $1$, ta không thay đổi $k$. Nếu số đầu tiên là $2$, ta tăng $k$ lên $(n-1)!$. Nếu số đầu tiên là $3$, ta tăng $k$ lên $2(n-1)!$. Tổng quát, nếu số đầu tiên là $x$, ta tăng $k$ lên
$$(x-1)(n-1)!.$$

Ta có thể xử lý từng số một và tăng giá trị $k$ bằng cùng ý tưởng. Sau mỗi bước, ta loại $x$ khỏi danh sách các số.

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;
const int N = 20;

int main() {
    int t;
    cin >> t;

    vector<ll> fact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i;
    }

    while (t--) {
        int op;
        cin >> op;

        int n;
        cin >> n;

        ll f = fact[n];
        vector<int> numbers(n);
        iota(numbers.begin(), numbers.end(), 1);

        if (op == 1) {
            ll k;
            cin >> k;
            k--;
            for (int i = 0; i < n; i++) {
                f /= n - i;
                cout << numbers[k / f] << " ";
                numbers.erase(numbers.begin() + (k / f));
                k %= f;
            }
            cout << "\n";
        }

        if (op == 2) {
            ll k = 1;
            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                f /= n - i;
                auto it = find(numbers.begin(), numbers.end(), x);
                k += (it - numbers.begin()) * f;
                numbers.erase(it);
            }
            cout << k << "\n";
        }
    }
}
```
