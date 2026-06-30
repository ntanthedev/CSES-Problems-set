# 1728 - Inversion Probability

Ta xét từng cặp chỉ số $(a,b)$ với $a<b$ và tính xác suất $x\_a > x\_b$, tương ứng với một nghịch thế.

Theo tính tuyến tính của kỳ vọng, tổng các xác suất bằng số nghịch thế kỳ vọng.

# Lời giải C++

Dưới đây là lời giải C++ cho bài toán:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    double answer = 0;
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            for (int x_a = 1; x_a <= r[a]; x_a++) {
                for (int x_b = 1; x_b <= min(x_a - 1, r[b]); x_b++) {
                    answer += 1.0 / (r[a] * r[b]);
                }
            }
        }
    }
    cout.precision(6);
    cout << fixed << answer << "\n";
}
```

Tuy nhiên, có những bộ test mà lời giải này thất bại do vấn đề độ chính xác. Nhìn chung, rất khó để tạo một lời giải đúng trong C++.

# Lời giải Python

Trong Python, ta có thể sử dụng lớp `Fraction` để tránh vấn đề độ chính xác:

```cpp
from fractions import Fraction

n = int(input())
r = [int(x) for x in input().split(" ")]

answer = Fraction(0, 1)
for a in range(n):
    for b in range(a + 1, n):
        for x_a in range(1, r[a] + 1):
            for x_b in range(1, min(x_a, r[b] + 1)):
                answer += Fraction(1, r[a] * r[b])

answer = float(round(answer, 6))
print(f"{answer:06f}")
```

Lời giải trên hoạt động đúng nhưng quá chậm. Tuy nhiên, ta có thể tối ưu như sau:

```cpp
from fractions import Fraction

n = int(input())
r = [int(x) for x in input().split(" ")]

answer = Fraction(0, 1)
for a in range(n):
    for b in range(a + 1, n):
        count = 0
        for x_a in range(1, r[a] + 1):
            count += min(x_a - 1, r[b])
        answer += Fraction(count, r[a] * r[b])

answer = float(round(answer, 6))
print(f"{answer:06f}")
```

Lời giải này hoạt động vừa đúng vừa đủ hiệu quả.
