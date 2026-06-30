# 1081 - Ước chung

Đầu tiên ta tạo một vector `count` để lưu số lần xuất hiện của mỗi số từ $1$ đến $N$ trong dữ liệu vào.

Sau đó, ta thực hiện một tìm kiếm theo kiểu sàng Eratosthenes để xác định ước số lớn nhất chia hết ít nhất hai số. Quá trình tìm kiếm mất $O(N \log N)$ thời gian, vì tổng số bước tương ứng với tổng điều hòa

$$N + N/2 + N/3 + \dots = O(N \log N).$$

Do đó, giải pháp chạy trong $O(n + N \log N)$ thời gian.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 1000000;

int main() {
    vector<int> count(N + 1);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        count[x]++;
    }

    for (int i = N; i >= 1; i--) {
        int total = 0;
        for (int j = i; j <= N; j += i) {
            total += count[j];
        }
        if (total >= 2) {
            cout << i << "\n";
            break;
        }
    }
}
```
