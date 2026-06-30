# 3406 - Tổng Số Tam Giác

Có thể chứng minh rằng mọi số nguyên dương đều có thể biểu diễn thành tổng của tối đa ba số tam giác. Do đó, kết quả luôn là $1$, $2$ hoặc $3$.

Đầu tiên, ta tiền tính toán danh sách tất cả các số tam giác từ $1 \dots 10^{12}$. Danh sách chứa khoảng $1.4 \cdot 10^6$ số.

Kết quả là $1$ nếu danh sách chứa $n$. Ngược lại, kết quả là $2$ nếu danh sách chứa hai số $a$ và $b$ có tổng bằng $n$, điều này có thể kiểm tra bằng kỹ thuật hai con trỏ. Nếu không, ta biết kết quả là $3$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int t;
    cin >> t;

    vector<ll> triangles;
    ll triangle = 0;
    for (int i = 1;; i++) {
        triangle += i;
        if (triangle > 1e12) break;
        triangles.push_back(triangle);
    }

    while (t--) {
        ll n;
        cin >> n;

        if (find(triangles.begin(), triangles.end(), n) != triangles.end()) {
            cout << "1\n";
            continue;
        }

        bool found = false;

        int right = triangles.size() - 1;
        for (int left = 0; left <= right; left++) {
            while (right > 0 && triangles[left] + triangles[right] > n) {
                right--;
            }
            if (triangles[left] + triangles[right] == n) {
                cout << "2\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "3\n";
        }
    }
}
```

## Tài liệu tham khảo

* [Định lý số đa giác của Fermat (Wikipedia)](https://en.wikipedia.org/wiki/Fermat_polygonal_number_theorem)
