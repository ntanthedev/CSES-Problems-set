# 2187 - Dãy ngoặc II

Bài phân tích này giả định rằng bạn đã biết cách đếm số lượng dãy ngoặc hợp lệ
có độ dài $n$ bằng kỹ thuật đảo ngược tiền tố. Ta dùng ý tưởng gần như tương tự
để giải bài toán này.

Ta duyệt qua tiền tố đã cho có độ dài $k$ và duy trì độ sâu (depth) của dãy. Mỗi
ngoặc mở tăng độ sâu lên một, và mỗi ngoặc đóng giảm độ sâu đi một. Nếu độ sâu
từng trở nên âm hoặc độ sâu cuối cùng lớn hơn $n-k$, không có dãy nào thỏa mãn.

Ngược lại, ta tính số lượng dãy hợp lệ. Gọi $d$ là độ sâu cuối cùng của tiền tố.
Phần còn lại gồm $n-k$ ký tự và số ngoặc mở là

$$l = \frac{n - k - d}{2}$$

do đó tổng số dãy như vậy là

$${n - k \choose l}.$$

Sau đó, số dãy không hợp lệ bằng

$${n - k \choose l + d + 1}$$

vì sau khi đảo ngược tiền tố không hợp lệ nhỏ nhất, số ngoặc mở tăng thêm $d+1$.
Vậy đáp án của bài toán là

$${n - k \choose l} - {n - k \choose l + d + 1}.$$

```cpp
#include <iostream>
using namespace std;
using ll = long long;
const int M = 1000000007;
const int N = 1000000;

int power(int a, int b) {
    if (b == 0) return 1;
    ll u = power(a, b / 2);
    u = u * u % M;
    if (b % 2 == 1) u = u * a % M;
    return u;
}

int inv(int x) {
    return power(x, M - 2);
}

ll fac[N + 1];

int ncr(int a, int b) {
    return fac[a] * inv(fac[b] * fac[a - b] % M) % M;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % M;
    }

    int n;
    cin >> n;
    string s;
    cin >> s;
    int k = s.size();

    int depth = 0;
    bool fail = false;
    for (auto c : s) {
        if (c == '(') depth++;
        if (c == ')') depth--;
        if (depth < 0) fail = true;
    }
    if (depth > n - k) fail = true;

    if (n % 2 == 0 && !fail) {
        int left = (n - k - depth) / 2;
        ll answer = ncr(n - k, left) - ncr(n - k, left + depth + 1);
        answer = (answer % M + M) % M;
        cout << answer << "\n";
    } else {
        cout << "0\n";
    }
}
```
