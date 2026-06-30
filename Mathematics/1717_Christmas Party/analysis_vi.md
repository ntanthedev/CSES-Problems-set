# 1717 - Tiệc Giáng sinh

Trong bài toán này, nhiệm vụ của chúng ta là tính số mất thứ tự (derangement) của $n$
phần tử, tức là số hoán vị của $n$ phần tử mà không có phần tử nào ở
đúng vị trí ban đầu của nó.

## Cách giải 1

Trước hết ta tính số hoán vị *không phải* là mất thứ tự.
Ta có thể làm điều đó bằng kỹ thuật bao hàm-loại trừ. Sau đó, ta trừ
kết quả khỏi số lượng tất cả các hoán vị.

Ta tính giá trị $f(n,i)$ với $i=1,2,\dots,n$: số hoán vị của
$n$ phần tử mà $i$ phần tử giữ đúng vị trí ban đầu và các phần tử còn lại
ở vị trí bất kỳ. Ta sử dụng công thức

$$f(n,i) = {n \choose i} (n - i)!$$

trong đó ${n \choose i}$ đếm số cách chọn các phần tử giữ đúng
vị trí ban đầu và $(n-i)!$ đếm số cách sắp xếp các
phần tử còn lại. Nếu $i$ lẻ, ta cộng $f(n,i)$ vào kết quả, và nếu $i$ là
chẵn, ta trừ $f(n,i)$ khỏi kết quả.

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
    ll count = 0;
    for (int i = 1; i <= n; i++) {
        ll add = ncr(n, i) * fac[n - i] % M;
        if (i % 2 == 0) add = -add;
        count += add;
    }
    ll answer = ((fac[n] - count) % M + M) % M;
    cout << answer << "\n";
}
```

## Cách giải 2

Ta cũng có thể đếm số mất thứ tự bằng đệ quy như sau:

$$d(n) = (n - 1) (d(n - 2) + d(n - 1))$$

Các trường hợp cơ sở là $d(1)=0$ và $d(2)=1$.

Ta có thể suy ra công thức như sau: Giả sử có $n$ đứa trẻ và một đứa trẻ
cố định $x$. Ta biết rằng đứa trẻ $x$ tặng quà cho một đứa trẻ $y$ nào đó và
có $n-1$ cách để chọn đứa trẻ $y$. Sau đó có hai trường hợp:

* Trường hợp 1: Đứa trẻ $y$ cũng tặng quà cho đứa trẻ $x$. Trong trường hợp
  này ta có thể loại bỏ hai đứa trẻ $x$ và $y$ và có $d(n-2)$ cách phân phối
  quà cho $n-2$ đứa trẻ còn lại.
* Trường hợp 2: Đứa trẻ $y$ tặng quà cho một đứa trẻ khác. Bây giờ hãy xét
  một cách phân phối quà bất kỳ cho $n-1$ đứa trẻ không có $x$. Có $d(n-1)$
  cách phân phối như vậy, và có một cách duy nhất để điều chỉnh mỗi cách phân
  phối sao cho đứa trẻ $x$ được bao gồm: đứa trẻ $x$ tặng quà cho đứa trẻ $y$
  và sau đó đứa trẻ mà ban đầu tặng quà cho $y$ sẽ tặng nó cho $x$.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<ll> count(n + 1);
    count[1] = 0;
    count[2] = 1;
    for (int i = 3; i <= n; i++) {
        count[i] = (i - 1) * (count[i - 2] + count[i - 1]) % M;
    }
    cout << count[n] << "\n";
}
```

## Tài liệu tham khảo

* [Mất thứ tự (Wikipedia)](https://en.wikipedia.org/wiki/Derangement)
