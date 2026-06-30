# 3399 - Raab Game I

Nếu $a+b>n$, không có lời giải vì tổng số điểm không thể vượt quá số lượt chơi.

Nếu chỉ có đúng một người chơi có $0$ điểm, không có lời giải vì không thể xảy ra trường hợp người chơi kia thắng một số vòng trong khi tất cả các vòng còn lại đều hòa.

Ngược lại, ta luôn có thể xây dựng một lời giải như sau:

* Người chơi thứ nhất luôn chơi $1,2,\dots,n$
* Người chơi thứ hai lần lượt chơi $a+1,a+2,\dots,a+b$, sau đó $1,2,\dots,a$ và cuối cùng là $a+b+1,a+b+2,\dots,n$.

Trong cách xây dựng này, người chơi thứ nhất thua $b$ lần rồi thắng $a$ lần. Sau các vòng này, có $n-a-b$ vòng hòa.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, a, b;
        cin >> n >> a >> b;

        if (a + b > n) {
            cout << "NO\n";
            continue;
        }

        if ((a == 0 || b == 0) && a + b != 0) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << "\n";
        for (int i = 1; i <= b; i++) {
            cout << a + i << " ";
        }
        for (int i = 1; i <= a; i++) {
            cout << i << " ";
        }
        for (int i = a + b + 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << "\n";
    }
}
```
