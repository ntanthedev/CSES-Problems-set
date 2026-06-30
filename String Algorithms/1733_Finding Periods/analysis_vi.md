# 1733 - Tìm Chu Kỳ

Chúng ta thảo luận hai cách giải bài toán trong $O(n)$ thời gian.

## Cách 1 (Z-algorithm)

Xây dựng mảng Z cho xâu bằng thuật toán Z. Sau đó, ta duyệt qua tất cả vị trí của xâu. Nếu hậu tố tại vị trí $i$ cũng là một tiền tố của xâu, ta có thể kết luận $i$ là một độ dài chu kỳ của xâu. Ngoài ra, $n$ luôn là một độ dài chu kỳ của xâu.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> z_algo(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(z[i - l], r - i));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main() {
    string s;
    cin >> s;
    int n = s.size();

    auto z = z_algo(s);
    for (int i = 1; i < n; i++) {
        if (z[i] == n - i) {
            cout << i << " ";
        }
    }
    cout << n << "\n";
}
```

## Cách 2 (hashing)

Ta cũng có thể giải bài toán bằng hàm băm. Vì ta có thể tính giá trị băm của bất kỳ xâu con nào trong $O(1)$ thời gian, ta có thể duyệt qua xâu và kiểm tra các hậu tố như trong Cách 1.

Cảnh báo: mã sử dụng hàm băm có thể thất bại do va chạm (hai xâu khác nhau nhưng có cùng giá trị băm).

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct HashString {
    const ll A = 31;
    const ll B = 991831889;

    vector<ll> pows, sums;

    HashString(string s) {
        int n = s.size();
        pows.resize(n + 1);
        pows[0] = 1;
        sums.resize(n + 1);
        sums[0] = 0;
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * A % B;
            sums[i] = (sums[i - 1] * A + s[i - 1]) % B;
        }
    }

    ll hash(int a, int b) {
        ll h = sums[b + 1] - sums[a] * pows[b - a + 1];
        return (h % B + B) % B;
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();

    HashString h(s);
    for (int i = 1; i < n; i++) {
        if (h.hash(i, n - 1) == h.hash(0, n - i - 1)) {
            cout << i << " ";
        }
    }
    cout << n << "\n";
}
```
