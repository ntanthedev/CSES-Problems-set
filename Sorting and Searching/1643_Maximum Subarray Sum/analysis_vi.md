# 1643 - Tổng Đoạn Con Lớn Nhất

Chúng ta duyệt qua mảng và duy trì hai giá trị:

* `sum`: tổng đoạn con lớn nhất kết thúc tại vị trí hiện tại
* `best`: tổng đoạn con lớn nhất đã thấy từ trước đến nay

Giả sử giá trị tại vị trí $i$ là $x$ và ta muốn tính tổng đoạn con lớn nhất kết thúc tại vị trí $i$. Ta có thể thực hiện điều này một cách hiệu quả khi biết tổng đoạn con lớn nhất kết thúc tại vị trí $i-1$ trước đó: hoặc ta cộng $x$ vào tổng trước đó, hoặc chỉ tạo một tổng chỉ gồm $x$.

Lưu ý rằng đề bài yêu cầu đoạn con không rỗng, do đó ta phải nhớ rằng tổng lớn nhất cũng có thể là số âm.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    ll sum = -1e9;
    ll best = -1e9;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        sum = max(sum + x, x);
        best = max(best, sum);
    }
    cout << best << "\n";
}
```

## Tài liệu tham khảo

* [Bài toán đoạn con lớn nhất (Wikipedia)](https://en.wikipedia.org/wiki/Maximum_subarray_problem)
