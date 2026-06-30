# 1092 - Two Sets

Ta có thể tính tổng các số bằng công thức quen thuộc
$$s = 1+2+\dots+n = \frac{n(n+1)}{2}.$$
Nếu $s$ là số lẻ, rõ ràng không thể giải được bài toán. Tuy nhiên, nếu $s$ là số chẵn, ta luôn có thể giải bài toán bằng thuật toán tham lam.

Ta duyệt qua các số từ $n$ đến $1$ và tạo hai tập hợp đều có tổng $s/2$. Ta thêm số $x$ vào tập hợp thứ nhất nếu tổng các số trong tập hợp thứ nhất sau khi thêm $x$ không vượt quá $s/2$. Ngược lại, ta thêm $x$ vào tập hợp thứ hai. Cuối cùng, ta đã xử lý tất cả các số và cả hai tập hợp đều có tổng $s/2$.

Tại sao thuật toán hoạt động? Thực tế, thuật toán có thể tạo ra bất kỳ tổng nào từ $0$ đến $1+2+\dots+n$ bằng cách sử dụng các số $\{1,2,\dots,n\}$ và ta có thể chứng minh điều này bằng quy nạp như sau.

Trường hợp $n=1$: Ta có thể tạo cả hai tổng $0$ và $1$ bằng thuật toán.

Trường hợp $n=k$: Ta muốn tạo tổng $a$ với $0 \le a \le 1+2+\dots+k$ bằng các số $\{1,2,\dots,k\}$. Nếu $a \ge k$, ta dùng $k$ trong tổng và sau đó tạo tổng $a'=a-k$ bằng các số $\{1,2,\dots,k-1\}$. Ngược lại $a<k$, ta tạo tổng $a'=a$ bằng các số $\{1,2,\dots,k-1\}$. Trong cả hai trường hợp $0 \le a' \le 1+2+\dots+k-1$, do đó thuật toán hoạt động đúng.

Vì $s/2$ nằm giữa $0$ và $s$, ta có thể dùng thuật toán để giải bài toán.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    ll s = (ll)n * (n + 1) / 2;

    if (s % 2 == 1) {
        cout << "NO\n";
        return 0;
    }
    s /= 2;

    vector<int> set1, set2;
    for (int x = n; x >= 1; x--) {
        if (s >= x) {
            s -= x;
            set1.push_back(x);
        } else {
            set2.push_back(x);
        }
    }

    cout << "YES\n";
    cout << set1.size() << "\n";
    for (auto x : set1) cout << x << " ";
    cout << "\n";
    cout << set2.size() << "\n";
    for (auto x : set2) cout << x << " ";
    cout << "\n";
}
```
