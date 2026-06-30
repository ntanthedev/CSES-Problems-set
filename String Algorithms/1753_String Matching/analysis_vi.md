# 1753 - Khớp Xâu

Cho một xâu $s$ độ dài $n$ và một mẫu $p$ độ dài $m$, ta muốn đếm số lần $p$ xuất hiện trong $s$.

Chúng ta thảo luận hai cách giải bài toán trong $O(n+m)$ thời gian.

## Cách 1 (Z-algorithm)

Một cách giải là sử dụng thuật toán Z. Với một xâu cho trước, thuật toán xây dựng mảng Z chứa, với mỗi hậu tố của xâu, độ dài lớn nhất của một tiền tố mà cũng là tiền tố của toàn bộ xâu. Thuật toán Z hoạt động trong thời gian tuyến tính.

Ta tạo một xâu mới $p\$s$ và xây dựng mảng Z của nó bằng thuật toán Z. Sau đó, ta duyệt qua mảng và tìm các vị trí có giá trị bằng $m$. Mỗi vị trí như vậy tương ứng với một lần xuất hiện của $p$ trong $s$.

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
    string s, p;
    cin >> s;
    int n = s.size();
    cin >> p;
    int m = p.size();

    string t = p + "$" + s;
    auto z = z_algo(t);
    int count = 0;
    for (int i = 0; i < n + m + 1; i++) {
        if (z[i] == m) count++;
    }
    cout << count << "\n";
}
```

## Cách 2 (hashing)

Một cách khác là sử dụng hàm băm. Sau khi tiền xử lý xâu, ta có thể tính giá trị băm của bất kỳ xâu con nào trong $O(1)$ thời gian. Do đó, ta có thể kiểm tra tất cả vị trí mà mẫu có thể xuất hiện và so sánh các giá trị băm.

Cảnh báo: mã sử dụng hàm băm có thể thất bại do va chạm (hai xâu khác nhau nhưng có cùng giá trị băm).

Có thể cố tình tìm một đầu vào khiến cho giải pháp dùng hàm băm bị sai. Một số biện pháp đã được thực hiện để bảo vệ giải pháp khỏi điều đó. Hệ số được sử dụng trong thuật toán băm đa thức (polynomial rolling hash) được chọn ngẫu nhiên và bộ sinh số ngẫu nhiên sử dụng số lượng *tick* kể từ [epoch](https://en.wikipedia.org/wiki/Epoch_(computing)) làm hạt giống (seed).

```cpp
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll M = 991831889;
const ll C = uniform_int_distribution<ll>(0.1 * M, 0.9 * M)(rng);

struct HashString {
    int n;
    vector<ll> pows, sums;

    HashString(string s) : n(s.size()), pows(n + 1, 1), sums(n + 1) {
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * C % M;
            sums[i] = (sums[i - 1] * C + s[i - 1]) % M;
        }
    }

    // Trả về giá trị băm của xâu con [l, r)
    ll hash(int l, int r) {
        ll h = sums[r] - sums[l] * pows[r - l];
        return (h % M + M) % M;
    }
};

int main() {
    string s, p;
    cin >> s;
    int n = s.size();
    cin >> p;
    int m = p.size();

    HashString h(s);
    ll target = HashString(p).hash(0, m);

    int count = 0;
    for (int i = 0; i < n - m + 1; i++) {
        if (h.hash(i, i + m) == target) {
            count++;
        }
    }
    cout << count << "\n";
}
```

## Tài liệu tham khảo

* [Wikipedia, Polynomial rolling hash](https://en.wikipedia.org/wiki/Rolling_hash#Polynomial_rolling_hash)
