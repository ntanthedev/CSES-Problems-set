# 1732 - Tìm đường biên

Ta trình bày hai cách giải bài toán trong $O(n)$ thời gian.

## Lời giải 1 (thuật toán Z)

Đầu tiên ta xây dựng mảng Z cho xâu bằng thuật toán Z. Sau đó, ta duyệt qua tất cả các hậu tố của xâu. Nếu một hậu tố cũng là tiền tố của xâu, ta đã tìm thấy một đường biên. Ta có thể kiểm tra điều đó bằng mảng Z: một hậu tố tại vị trí $i$ là một đường biên chính xác khi giá trị của mảng là $n-i$.

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
    for (int i = n - 1; i > 0; i--) {
        if (z[i] == n - i) {
            cout << n - i << " ";
        }
    }
    cout << "\n";
}
```

## Lời giải 2 (băm)

Ta cũng có thể giải bài toán bằng băm. Vì ta có thể tính giá trị băm của bất kỳ xâu con nào trong $O(1)$ thời gian, ta chỉ cần duyệt qua mọi tiền tố và kiểm tra xem nó có bằng hậu tố có cùng độ dài hay không.

Cảnh báo: một đoạn mã sử dụng băm có thể thất bại do va chạm (hai xâu khác nhau nhưng có cùng giá trị băm).

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
    for (int i = 0; i < n - 1; i++) {
        if (h.hash(0, i) == h.hash(n - i - 1, n - 1)) {
            cout << i + 1 << " ";
        }
    }
    cout << "\n";
}
```
