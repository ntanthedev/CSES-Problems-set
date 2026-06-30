# 2165 - Tháp Hà Nội

Lời giải sau sử dụng một hàm đệ quy di chuyển $n$ đĩa từ cọc $a$ sang cọc $b$ sử dụng cọc $c$. Hàm giả định rằng tất cả các đĩa trong cọc $b$ và $c$ đều lớn hơn $n$ đĩa trong cọc $a$ sẽ được di chuyển.

Nếu $n=1$, hàm chỉ di chuyển một đĩa từ cọc $a$ sang cọc $b$. Ngược lại, hàm đệ quy di chuyển $n-1$ đĩa từ cọc $a$ sang cọc $c$, sau đó một đĩa từ cọc $a$ sang cọc $b$ và cuối cùng $n-1$ đĩa từ cọc $c$ sang cọc $b$.

Sử dụng hàm này, ta có thể giải bài toán bằng cách di chuyển $n$ đĩa từ cọc trái sang cọc phải sử dụng cọc giữa. Tổng số lần di chuyển sẽ là $2^n-1$, đây là lời giải tối ưu.

Tại sao lời giải này là tối ưu? Vì để di chuyển đĩa lớn nhất từ cọc trái sang cọc phải, ta phải di chuyển tất cả các đĩa khác sang cọc giữa để cọc phải trống và ta có thể di chuyển đĩa lớn nhất. Sau đó, ta phải di chuyển tất cả các đĩa khác từ cọc giữa sang cọc phải.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> moves;

void move(int n, int a, int b, int c) {
    if (n == 1) {
        moves.emplace_back(a, b);
    } else {
        move(n - 1, a, c, b);
        move(1, a, b, c);
        move(n - 1, c, b, a);
    }
}

int main() {
    int n;
    cin >> n;
    move(n, 1, 3, 2);
    cout << moves.size() << "\n";
    for (auto [a, b] : moves) {
        cout << a << " " << b << "\n";
    }
}
```

## Tài liệu tham khảo

* [Tower of Hanoi (Wikipedia)](https://en.wikipedia.org/wiki/Tower_of_Hanoi)
