# 2185 - Bội số nguyên tố

Ta giải bài toán bằng kỹ thuật bao hàm-loại trừ (inclusion-exclusion).

Ta duyệt qua mọi tập con khác rỗng của $\{a\_1,a\_2,\dots,a\_k\}$. Số lượng số
nguyên từ $1$ đến $n$ chia hết cho tất cả các số nguyên tố trong tập con đã chọn
bằng $x=\lfloor n/p \rfloor$, trong đó $p$ là tích các số nguyên tố trong tập
con đó.

Nếu tập con có số lẻ số nguyên tố, ta tăng đáp án lên $x$, ngược lại ta giảm
đáp án đi $x$. Sau khi xử lý tất cả các tập con, ta đã đếm được các số chia hết
cho ít nhất một số nguyên tố.

Lưu ý rằng $p$ có thể là số rất lớn và có thể bị tràn, do đó ta phải đảm bảo
code hoạt động trong trường hợp này.

Thuật toán chạy trong thời gian $O(2^k k)$ vì nó duyệt qua $O(2^k)$ tập con và
xử lý mỗi tập con trong $O(k)$ thời gian.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ll n;
    int k;
    cin >> n >> k;

    vector<ll> primes(k);
    for (int i = 0; i < k; i++) {
        cin >> primes[i];
    }

    ll answer = 0;
    for (int b = 1; b < (1 << k); b++) {
        ll prod = 1;
        bool fail = false;

        for (int i = 0; i < k; i++) {
            if (b & (1 << i)) {
                if (primes[i] > n / prod) fail = true;
                prod *= primes[i];
            }
        }

        if (fail) continue;

        ll add = n / prod;
        if (__builtin_parity(b) == 0) add = -add;
        answer += add;
    }

    cout << answer << "\n";
}
```
