# 1074 - Stick Lengths

Trong bài toán này, ta được cho $n$ số $p\_1,p\_2,\dots,p\_n$ và nhiệm vụ là tìm giá trị $x$ để tối thiểu hóa tổng $|x-p\_1|+|x-p\_2|+\dots+|x-p\_n|$.

Hóa ra lời giải tối ưu là chọn $x$ sao cho nó là trung vị của dãy $p\_1,p\_2,\dots,p\_n$. Tại sao? Chúng ta hãy xét hai trường hợp:

Trường hợp 1: $n$ lẻ và trung vị là $m$. Nếu $x<m$ và ta tăng $x$ lên một, giá trị của $|x-p\_i|$ tăng lên một khi $p\_i \le x$ và giảm đi một khi $p\_i>x$. Điều sau xảy ra với hơn một nửa số phần tử, do đó tổng chi phí giảm xuống. Tương tự, nếu $x>m$ và ta giảm $x$ đi một, tổng chi phí cũng giảm. Vì vậy, $x=m$ cho chi phí tối thiểu.

Trường hợp 2: $n$ chẵn và các trung vị là $m\_1$ và $m\_2$ (giả sử $m\_1 \le m\_2$). Nếu $x<m\_1$ hoặc $x>m\_2$, ta có thể dùng lập luận tương tự như Trường hợp 1. Khi đó, nếu $m\_1 \le x < m\_2$ và ta tăng $x$ lên một, hoặc $m\_1 < x \le m\_2$ và ta giảm $x$ đi một, tổng chi phí không đổi. Vì vậy, mọi giá trị $m\_1 \le x \le m\_2$ đều cho chi phí tối thiểu.

Đoạn code sau giải bài toán trong $O(n \log n)$ bằng cách sắp xếp mảng, sau đó trung vị là phần tử ở giữa.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> lengths(n);
    for (int i = 0; i < n; i++) {
        cin >> lengths[i];
    }

    sort(lengths.begin(), lengths.end());
    int target = lengths[n / 2];

    ll cost = 0;
    for (int i = 0; i < n; i++) {
        cost += abs(target - lengths[i]);
    }
    cout << cost << "\n";
}
```

Ta cũng có thể tìm trung vị hiệu quả hơn mà không cần sắp xếp. Đoạn code sau sử dụng hàm `nth_element` trong C++, chạy trong $O(n)$ (trung bình hoặc thậm chí trong trường hợp tệ nhất, tùy thuộc vào cách cài đặt).

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<int> lengths(n);
    for (int i = 0; i < n; i++) {
        cin >> lengths[i];
    }

    nth_element(lengths.begin(), lengths.begin() + n / 2, lengths.end());
    int target = lengths[n / 2];

    ll cost = 0;
    for (int i = 0; i < n; i++) {
        cost += abs(target - lengths[i]);
    }
    cout << cost << "\n";
}
```

## Tài liệu tham khảo

* [Selection algorithm (Wikipedia)](https://en.wikipedia.org/wiki/Selection_algorithm)
