# 2431 - Truy vấn chữ số

Ta xét các khối số mà mỗi số có cùng độ dài:

* $[1,9]$ (độ dài $1$)
* $[10,99]$ (độ dài $2$)
* $[100,999]$ (độ dài $3$)
* ...

Đầu tiên ta xác định khối chứa vị trí $k$. Trong code, khoảng của khối là $[a,b]$ và độ dài của mỗi số trong khối là $c$. Sau đó, ta tính số $x$ chứa chữ số cần tìm và cuối cùng lấy chữ số đó.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int digit(ll k) {
    k--;
    ll a = 1;
    ll b = 9;
    int c = 1;
    while (k >= (b - a + 1) * c) {
        k -= (b - a + 1) * c;
        a = a * 10;
        b = b * 10 + 9;
        c++;
    }
    ll x = a + k / c;
    return to_string(x)[k % c] - '0';
}

int main() {
    int q;
    cin >> q;
    for (int qi = 0; qi < q; ++qi) {
        ll k;
        cin >> k;
        cout << digit(k) << "\n";
    }
}
```
