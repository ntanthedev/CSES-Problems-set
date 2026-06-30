# 1090 - Ferris Wheel

Ta có thể giải bài toán bằng thuật toán tham lam: ở mỗi bước, đặt đứa trẻ nặng nhất vào một gondola. Nếu đứa trẻ nhẹ nhất cũng có thể đặt vào cùng gondola đó, ta làm điều đó và gondola sẽ có hai đứa trẻ. Ngược lại, đứa trẻ nặng nhất sẽ ở một mình trong gondola.

Thuật toán có thể được cài đặt bằng cách sắp xếp các trọng lượng và sau đó duy trì hai con trỏ tới đứa trẻ nhẹ nhất và nặng nhất. Sử dụng các con trỏ, ta luôn có thể tìm hiệu quả đứa trẻ nhẹ nhất và nặng nhất.

Thuật toán hoạt động đúng vì dù sao ta cũng phải đặt đứa trẻ nặng nhất vào một gondola, nên ta có thể bắt đầu với đứa trẻ đó. Việc chọn đứa trẻ nhẹ nhất để ở cùng gondola cũng là tối ưu. Nếu ta "dành" đứa trẻ nhẹ nhất cho một gondola khác, điều này sẽ không bao giờ tạo ra lời giải tốt hơn.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    sort(weights.begin(), weights.end());

    int count = 0;
    int i = 0;
    int j = n - 1;
    while (i <= j) {
        if (i < j && weights[i] + weights[j] <= x) {
            count++;
            i++;
            j--;
        } else {
            count++;
            j--;
        }
    }
    cout << count << "\n";
}
```

Lưu ý rằng ta cũng có thể sử dụng một phương pháp tham lam khác để chọn đứa trẻ thứ hai: thay vì chọn đứa trẻ nhẹ nhất, ta có thể chọn đứa trẻ nặng nhất phù hợp với gondola. Có thể dễ dàng hơn để thấy tại sao phương pháp này hoạt động, nhưng nó sẽ phức tạp hơn để cài đặt.
