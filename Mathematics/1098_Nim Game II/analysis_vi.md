# 1098 - Trò chơi Nim II

Ta tính số Grundy của mỗi đống và sau đó tính tổng xor của các số để xác định người thắng.

Hóa ra các số Grundy tạo thành một chu kỳ $0,1,2,3,0,1,2,3,\dots$, do đó nếu một đống có $x$ que, số Grundy của nó là $x \bmod 4$.

```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            sum ^= (x % 4);
        }
        cout << (sum != 0 ? "first" : "second") << "\n";
    }
}
```

## Tài liệu tham khảo

* [Nim (Wikipedia)](https://en.wikipedia.org/wiki/Nim)
