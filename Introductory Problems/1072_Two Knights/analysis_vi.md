# 1072 - Hai quân mã

Sẽ dễ dàng hơn nếu tính số cách hai quân mã có thể tấn công lẫn nhau, sau đó trừ số này khỏi tổng số cách đặt chúng lên bàn cờ.

Để tìm quy luật, trước hết hãy tập trung vào bàn cờ $8 \times 8$ và đếm, với mỗi ô, số cách một quân mã đặt ở ô đó có thể tấn công một quân mã khác. Hóa ra có một quy luật rõ ràng:

```cpp
2 3 4 4 4 4 3 2
3 4 6 6 6 6 4 3
4 6 8 8 8 8 6 4
4 6 8 8 8 8 6 4
4 6 8 8 8 8 6 4
4 6 8 8 8 8 6 4
3 4 6 6 6 6 4 3
2 3 4 4 4 4 3 2
```

Sử dụng quy luật này, ta có thể giải bài toán một cách hiệu quả như sau. Đầu tiên ta đếm tổng số cách đặt hai quân mã lên bàn cờ. Sau đó, ta trừ đi số cách chúng có thể tấn công lẫn nhau. Cuối cùng, ta chia kết quả cho hai để chỉ đếm các tổ hợp phân biệt.

Lưu ý rằng lời giải kỳ diệu vẫn hoạt động với $n < 4$ mặc dù nó giả định rằng có $n-4$ hàng và cột ở các lớp bên trong.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

ll f(ll n) {
    ll r = n * n * (n * n - 1);
    r -= 4 * 2;
    r -= 8 * 3;
    r -= 4 * 4;
    r -= (n - 4) * 4 * 4;
    r -= (n - 4) * 4 * 6;
    r -= (n - 4) * (n - 4) * 8;
    return r / 2;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << f(i) << "\n";
    }
}
```

Điều này tương ứng với công thức $(n^4 - 9n^2 + 24n - 16) / 2$ cho phép ta tạo ra một lời giải ngắn hơn:

```cpp
#include <iostream>
using namespace std;
using ll = long long;

ll f(ll n) {
    return (n * n * n * n - 9 * n * n + 24 * n - 16) / 2;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << f(i) << "\n";
    }
}
```

## Tài liệu tham khảo

* [OEIS A172132](https://oeis.org/A172132): Số cách đặt 2 quân mã không tấn công nhau trên bàn cờ n × n
