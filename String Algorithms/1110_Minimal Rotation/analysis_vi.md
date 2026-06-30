# 1110 - Phép xoay nhỏ nhất

Một thủ thuật hữu ích trong bài toán này là trước tiên tạo một xâu mới gồm hai
bản sao của xâu ban đầu. Ví dụ, nếu xâu đầu vào là `acab`, ta tạo xâu
`acabacab`. Sau đó, chỉ cần tìm xâu con có độ dài $n$ nhỏ nhất theo thứ tự
từ điển trong xâu mới.

## Lời giải 1 (vét cạn)

Một lời giải vét cạn đơn giản là duyệt qua xâu và duy trì một
giá trị `pos`: vị trí bắt đầu của xâu con có độ dài $n$ nhỏ nhất tìm được cho
đến thời điểm hiện tại.

Rất tiếc, lời giải này cần $O(n^2)$ thời gian và quá chậm để giải
bài toán một cách hiệu quả.

```cpp
#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    s = s + s;

    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (s.substr(pos, n) > s.substr(i, n)) {
            pos = i;
        }
    }
    cout << s.substr(pos, n) << "\n";
}
```

## Lời giải 2 (băm và tìm kiếm nhị phân)

Ta có thể cải thiện lời giải vét cạn bằng cách sử dụng băm và tìm kiếm nhị phân.

Để so sánh hai xâu con một cách hiệu quả, trước tiên ta tìm độ dài của tiền tố
chung của hai xâu con và sau đó so sánh ký tự tiếp theo sau nó. Sử dụng
băm, ta có thể kiểm tra sự bằng nhau của hai xâu con trong $O(1)$ thời gian. Ta
xác định độ dài của tiền tố chung bằng tìm kiếm nhị phân, do đó ta chỉ cần
kiểm tra sự bằng nhau của $O(\log n)$ tiền tố.

Vì ta kiểm tra $O(n)$ vị trí và mỗi lần so sánh mất $O(\log n)$ thời gian, thuật
toán kết quả hoạt động trong $O(n \log n)$ thời gian.

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

    // Trả về băm của xâu con [l, r)
    ll hash(int l, int r) {
        ll h = sums[r] - sums[l] * pows[r - l];
        return (h % M + M) % M;
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();
    s = s + s;

    HashString h(s);

    auto cmp = [&](int a, int b) {
        int len = 0;
        for (int add = n; add >= 1; add /= 2) {
            while (len + add < n) {
                ll hash1 = h.hash(a, a + len + add);
                ll hash2 = h.hash(b, b + len + add);
                if (hash1 != hash2) break;
                len += add;
            }
        }
        return s[a + len] > s[b + len];
    };

    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (cmp(pos, i)) pos = i;
    }
    cout << s.substr(pos, n) << "\n";
}
```

## Lời giải 3 (phân tích Lyndon)

Ta duy trì hai giá trị: `pos` là vị trí bắt đầu của xâu con nhỏ nhất tìm được
cho đến thời điểm hiện tại, và `cur` là vị trí bắt đầu hiện tại của ta.

Ở mỗi bước, ta xác định một giá trị $k$: độ dài của tiền tố chung của
các xâu con bắt đầu tại vị trí `pos` và `cur` (ta đảm bảo $k$ không vượt quá
$n$). Sau đó ta kiểm tra ký tự tiếp theo sau tiền tố chung để so sánh các
xâu con.

Nếu xâu con tại vị trí `pos` không lớn hơn xâu con tại vị trí
`cur`, ta tăng `cur` lên $k+1$. Ta có thể làm điều đó vì không có hậu tố nào
của tiền tố chung có thể bắt đầu một xâu con nhỏ nhất mới.

Ngược lại, ta biết xâu con bắt đầu tại `cur` nhỏ hơn xâu con bắt đầu tại
`pos`. Để thuật toán hiệu quả, ta luôn tăng
`pos` lên ít nhất $k+1$. Ta có thể làm điều đó vì nếu các tiền tố chung chồng
lấn, chúng tạo thành một sự lặp lại mà ta có thể bỏ qua.

Lời giải hoạt động trong $O(n)$ thời gian vì sau khi khớp $k$ ký tự trong
vòng lặp trong, hoặc `pos` hoặc `cur` luôn tăng lên $k$.

```cpp
#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    s = s + s;

    int pos = 0;
    int cur = 1;
    while (cur < n) {
        int k = 0;
        while (k < n && s[pos + k] == s[cur + k]) k++;
        if (s[pos + k] <= s[cur + k]) {
            cur += k + 1;
        } else {
            pos = max(pos + k + 1, cur);
            cur = pos + 1;
        }
    }

    cout << s.substr(pos, n) << "\n";
}
```

## Tài liệu tham khảo

* [Lexicographically\_minimal\_string\_rotation (Wikipedia)](https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation)
* [Lyndon word (Wikipedia)](https://en.wikipedia.org/wiki/Lyndon_word)
* [Lyndon factorization (CP-Algorithms)](https://cp-algorithms.com/string/lyndon_factorization.html)
