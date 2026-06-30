# 1713 - Đếm ước số

## Cách giải 1

Hàm `count` sau đây trả về số lượng ước số của $x$. Nó kiểm tra
mọi số nguyên $k$ từ $1$ đến $\sqrt x$. Nếu $x$ chia hết cho $k$, ta đã tìm
thấy một ước số. Ngoài ra, nếu $k \neq x/k$, ta tìm thấy thêm một ước số nữa
là $x/k$.

Cách giải này chạy trong $O(n \sqrt N)$ với $N$ là cận trên của $x$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int count(int x) {
    int c = 0;
    for (int k = 1; k * k <= x; k++) {
        if (x % k) continue;
        c++;
        if (k != x / k) c++;
    }
    return c;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cout << count(x) << "\n";
    }
}
```

## Cách giải 2

Cách giải này hoạt động tương tự như sàng Eratosthenes. Nó
tạo ra một vector `count` chứa số lượng ước số cho mỗi
số $x$ từ $1$ đến $N$.

Việc tạo vector này tốn $O(N \log N)$ thời gian vì tổng số bước
bị chặn bởi tổng điều hòa

$$N + N/2 + N/3 + \dots = O(N \log N).$$

Do đó, cách giải này chạy trong $O(N \log N + n)$ thời gian.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 1000000;

int main() {
    vector<int> count(N + 1);
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            count[j]++;
        }
    }

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cout << count[x] << "\n";
    }
}
```
