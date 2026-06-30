# 1652 - Truy vấn khu rừng

Bài toán này có thể được giải bằng một mảng tổng tiền tố 2D.

Gọi $S(P)$ là diện tích từ góc trên cùng bên trái đến điểm $P$.
Khi đó câu trả lời cho một truy vấn có thể được tính bằng công thức
$S((x\_2,y\_2))-S((x\_2,y\_1))-S((x\_1,y\_2))+S((x\_1,y\_1))$.

![](4f086ef2cc9dabf5e98299464950e70760e0b903251c03539a488c698c9d2c3e)

Chú ý cách các đoạn là nửa mở trong hình vẽ và trong cài đặt.
Trong hình vẽ, điều này có thể thấy ở chỗ tọa độ $y\_2$ và $x\_2$ trỏ đến
đáy của ô vuông và cạnh phải của ô vuông, tương ứng.

```cpp
#include <iostream>
using namespace std;

const int N = 1001;
int sums[N][N];

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;

        for (int j = 0; j < n; ++j) {
            sums[i + 1][j + 1] = sums[i + 1][j] + sums[i][j + 1] - sums[i][j];
            sums[i + 1][j + 1] += (row[j] == '*');
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        // Chuyển đoạn về chỉ số 0 và nửa mở.
        y1--;
        x1--;
        // Chúng ta đang truy vấn đoạn [y1, y2) x [x1, x2).
        int ans = sums[y2][x2] - sums[y1][x2] - sums[y2][x1] + sums[y1][x1];
        cout << ans << '\n';
    }
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên Thi đấu)](http://cses.fi/book), Chương 9
* [Codeforces, *Video về tổng tiền tố, mảng hiệu và sức mạnh của khoảng nửa mở* bởi peltorator](https://codeforces.com/blog/entry/88474)
