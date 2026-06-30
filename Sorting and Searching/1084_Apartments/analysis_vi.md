# 1084 - Apartments

Ta có thể giải bài toán bằng thuật toán tham lam duyệt qua nguyện vọng của các người nộp đơn theo thứ tự tăng dần và đưa cho mỗi người nộp đơn căn hộ nhỏ nhất thỏa mãn nguyện vọng (nếu có căn hộ như vậy).

Một cách tốt để cài đặt thuật toán là sắp xếp cả nguyện vọng lẫn kích thước căn hộ, sau đó duyệt qua các nguyện vọng. Ta cũng duy trì một con trỏ để tìm hiệu quả căn hộ nhỏ nhất cho một nguyện vọng.

Thuật toán hoạt động đúng vì ta luôn có thể an toàn chọn nguyện vọng nhỏ nhất có thể đáp ứng và đưa ra căn hộ nhỏ nhất. Ta không thể đạt được lời giải tốt hơn bằng cách bỏ qua nguyện vọng nhỏ nhất hoặc đưa một căn hộ lớn hơn cho nguyện vọng đó.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> wishes(n);
    for (int i = 0; i < n; i++) {
        cin >> wishes[i];
    }
    sort(wishes.begin(), wishes.end());

    vector<int> sizes(m);
    for (int i = 0; i < m; i++) {
        cin >> sizes[i];
    }
    sort(sizes.begin(), sizes.end());

    int count = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < m && sizes[j] < wishes[i] - k) {
            j++;
        }
        if (j < m && sizes[j] <= wishes[i] + k) {
            count++;
            j++;
        }
    }
    cout << count << "\n";
}
```
