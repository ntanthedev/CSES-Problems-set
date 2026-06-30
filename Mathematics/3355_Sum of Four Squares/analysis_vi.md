# 3355 - Tổng Bốn Bình Phương

Gọi $N=10^7$ là giá trị lớn nhất của $n$.

Đầu tiên ta tìm tất cả các số nguyên từ $0$ đến $N$ có thể biểu diễn thành tổng của hai bình phương. Việc này có thể thực hiện trong $O(N)$ thời gian. Với mỗi số $x=a^2+b^2$ như vậy, ta lưu số thứ nhất $a$ và số thứ hai $b$.

Sau đó, ta có thể tìm nghiệm cho mọi $n$ trong $O(n)$ thời gian bằng cách tìm một số $x$ sao cho cả $x$ và $n-x$ đều có thể biểu diễn thành tổng của hai bình phương. Có thể chứng minh rằng luôn tồn tại nghiệm.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e7;

int main() {
    int t;
    cin >> t;

    vector<bool> can(N + 1);
    vector<int> first(N + 1), second(N + 1);
    for (int a = 0; a * a <= N; a++) {
        for (int b = 0; a * a + b * b <= N; b++) {
            int x = a * a + b * b;
            can[x] = true;
            first[x] = a;
            second[x] = b;
        }
    }

    while (t--) {
        int n;
        cin >> n;
        for (int x = 0; x <= n; x++) {
            if (can[x] && can[n - x]) {
                cout << first[x] << " " << second[x] << " ";
                cout << first[n - x] << " " << second[n - x] << "\n";
                break;
            }
        }
    }
}
```

## Tài liệu tham khảo

* [Định lý bốn bình phương của Lagrange (Wikipedia)](https://en.wikipedia.org/wiki/Lagrange%27s_four-square_theorem)
