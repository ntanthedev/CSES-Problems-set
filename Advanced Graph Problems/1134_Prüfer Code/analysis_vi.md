# 1134 - Mã Prüfer

Mã Prüfer tương ứng với việc chọn gốc cho cây trong đó gốc là đỉnh thứ $n$
nếu ta coi cha của một đỉnh là đỉnh kề duy nhất của nó khi đỉnh đó bị xóa.
Bây giờ, gọi số lượng con trực tiếp của mỗi đỉnh là *bậc* của đỉnh đó.

Nếu bậc của một đỉnh bằng không, nó không có con và do đó là ứng viên để
xóa. Nếu ta lưu các ứng viên trong một `priority_queue`, chỉ số nhỏ nhất
trong hàng đợi tương ứng với đỉnh bị xóa tiếp theo. Sau đó, việc còn lại chỉ
là duy trì bậc và hàng đợi giữa các lần xóa.

```cpp
#include <iostream>
#include <queue>
using namespace std;

const int N = 200001;
int code[N];
int degree[N];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n - 2; ++i) {
        cin >> code[i];
        degree[code[i]]++;
    }

    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 0) {
            leaves.push(i);
        }
    }

    for (int i = 1; i <= n - 2; ++i) {
        cout << code[i] << ' ' << leaves.top() << '\n';
        leaves.pop();
        degree[code[i]]--;
        if (degree[code[i]] == 0) {
            leaves.push(code[i]);
        }
    }

    cout << leaves.top() << ' ' << n << endl;
}
```

## Tài liệu tham khảo

* [Prüfer sequence (Wikipedia)](https://en.wikipedia.org/wiki/Pr%C3%BCfer_sequence)
