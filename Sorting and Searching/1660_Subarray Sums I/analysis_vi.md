# 1660 - Subarray Sums I

Vì mỗi phần tử của mảng đều dương, ta có thể sử dụng kỹ thuật hai con trỏ để giải bài toán.

Ta duy trì một đoạn con ban đầu chỉ chứa phần tử đầu tiên của mảng. Ở mỗi bước, đầu tiên ta tăng con trỏ phải miễn là tổng của đoạn con nhỏ hơn $x$. Sau đó, nếu tổng bằng chính xác $x$, ta đã tìm được một nghiệm. Cuối cùng, ta tăng con trỏ trái.

Thuật toán chạy trong $O(n)$ thời gian vì ta tăng cả con trỏ trái và phải $O(n)$ lần.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int left = 0;
    int right = 0;
    int sum = a[0];
    int count = 0;

    while (left < n) {
        while (sum < x && right + 1 < n) {
            right++;
            sum += a[right];
        }
        if (sum == x) {
            count++;
        }
        sum -= a[left];
        left++;
    }

    cout << count << "\n";
}
```
