# 2417 - Đếm Cặp Nguyên Tố Cùng Nhau

## Cách 1

Thay vì tính số cặp nguyên tố cùng nhau, ta tính số cặp *không* nguyên tố cùng nhau, tức là chúng có ước chung.

Ta duyệt qua các số và tạo một vector `factors` cho mỗi số. Vector này chứa tất cả các ước nguyên tố phân biệt của số đó. Sau đó ta duyệt qua tất cả tập con của vector, tương ứng với tất cả các số phân biệt có thể tạo ra từ các ước nguyên tố đó.

Ta sử dụng kỹ thuật bù trừ để tính kết quả. Tại vị trí $i$, ta tính số cặp mà $j<i$ và $\gcd(x[i],x[j]) > 1$. Để làm điều này, ta tạo một vector `total` chứa số lần mỗi tổ hợp ước nguyên tố đã xuất hiện trong các số trước đó.

Cuối cùng, ta lấy tổng số cặp $n(n-1)/2$ trừ đi kết quả thu được.

Cách giải này chạy trong $O(n (\sqrt N + 2^K K))$ thời gian, trong đó $N$ là chặn trên của các số đầu vào và $K$ là chặn trên của số lượng ước nguyên tố phân biệt. Ở đây $N=10^6$ và $K=7$ vì $2 \cdot 3 \cdot 5 \cdot 7 \cdot 11 \cdot 13 \cdot 15 = 450450$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1000000;

int main() {
    vector<int> total(N + 1);

    int n;
    cin >> n;
    ll answer = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        vector<int> factors;
        for (int f = 2; f * f <= x; f++) {
            if (x % f == 0) {
                factors.push_back(f);
                while (x % f == 0) x /= f;
            }
        }
        if (x != 1) factors.push_back(x);

        int k = factors.size();
        for (int b = 1; b < (1 << k); b++) {
            int prod = 1;
            for (int i = 0; i < k; i++) {
                if (b & (1 << i)) prod *= factors[i];
            }

            int add = total[prod];
            if (__builtin_parity(b) == 0) add = -add;
            answer += add;
            total[prod]++;
        }
    }

    cout << (n * ll(n - 1) / 2) - answer << "\n";
}
```

## Cách 2

Một cách khác để giải bài toán là sử dụng kỹ thuật nghịch đảo Möbius. Ta muốn tính tổng

$$\sum\_{i=1}^n \sum\_{j=1}^n [\gcd(x\_i,x\_j) = 1]$$

trong đó ký hiệu $[\dots]$ có nghĩa là giá trị của biểu thức bằng $1$ nếu điều kiện đúng và $0$ nếu ngược lại. Tổng này tương ứng với

$$\sum\_{i=1}^n \sum\_{j=1}^n \sum\_{d \mid \gcd(x\_i,x\_j)} \mu(d)$$

trong đó $\mu(d)$ là hàm Möbius. Vì ta muốn $d$ chia $\gcd(x\_i,x\_j)$, điều này có nghĩa là $d$ phải chia cả $x\_i$ và $x\_j$, và ta có thể dùng ký hiệu chỉ dẫn để chọn các giá trị $d$ được tính:

$$\sum\_{i=1}^n \sum\_{j=1}^n \sum\_{d=1}^N \mu(d) [d \mid x\_i] [d \mid x\_j]$$

Ở đây $N$ là chặn trên của các giá trị đầu vào.

Sau đó, ta sắp xếp lại tổng như sau:

$$\sum\_{d=1}^N (\mu(d) (\sum\_{i=1}^n [d \mid x\_i]) (\sum\_{i=1}^n [d \mid x\_i]))$$

Chú ý rằng hai tổng cuối độc lập với nhau nên ta có thể dùng biến $i$ trong cả hai tổng và tính chúng riêng biệt.

Ta tiền tính toán tất cả các giá trị $\mu(d)$ và $\sum\_{i=1}^n [d \mid x\_i]$ bằng kỹ thuật sàng Eratosthenes, sau đó ta có thể tính kết quả một cách hiệu quả. Cuối cùng, ta loại bỏ số cặp có phần tử ở cùng vị trí và chia kết quả cho hai để mỗi cặp chỉ được đếm một lần.

Cách giải này chạy trong $O(n + N \log N)$ thời gian.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1000000;

int main() {
    vector<int> mu(N + 1, 1);
    vector<int> skip(N + 1);
    for (int d = 2; d <= N; d++) {
        if (skip[d]) continue;
        for (int i = d; i <= N; i += d) {
            skip[i] = 1;
            if (i % (d * d) == 0) mu[i] = 0;
            mu[i] = -mu[i];
        }
    }

    int n;
    cin >> n;
    vector<int> count(N + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        count[x]++;
    }

    vector<int> div(N + 1);
    for (int d = 1; d <= N; d++) {
        for (int i = d; i <= N; i += d) {
            div[d] += count[i];
        }
    }

    ll answer = 0;
    for (int d = 1; d <= N; d++) {
        answer += mu[d] * (ll)div[d] * div[d];
    }
    cout << (answer - count[1]) / 2 << "\n";
}
```
