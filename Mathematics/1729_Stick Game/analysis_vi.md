# 1729 - Stick Game

Ta duyệt qua các trạng thái $1,2,\dots,n$ và xác định vị thế của từng trạng thái. Nếu có một nước đi dẫn đến vị thế thua, thì ta đang ở vị thế thắng; ngược lại ta đang ở vị thế thua.

Thuật toán có độ phức tạp $O(nk)$, trong đó $n$ là số lượng que và $k$ là số nước đi.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> move(k);
    for (int i = 0; i < k; i++) {
        cin >> move[i];
    }

    string pos(n + 1, 'L');
    for (int i = 1; i <= n; i++) {
        for (auto m : move) {
            if (i - m >= 0 && pos[i - m] == 'L') {
                pos[i] = 'W';
            }
        }
    }
    cout << pos.substr(1) << "\n";
}
```
