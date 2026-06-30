# 2208 - Another Game

Ta thắng trò chơi nếu có ít nhất một đống có số đồng xu lẻ, và ta thua nếu mọi
đống đều có số đồng xu chẵn.

Ý tưởng là ta luôn chọn các đống có số đồng xu lẻ và bỏ một đồng xu khỏi mỗi
đống đó. Điều này đảm bảo mỗi đống có số đồng xu chẵn khi đối thủ đi tiếp.
Cuối cùng, mọi đống đều rỗng và ta đã thắng.

```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n;
        cin >> n;
        bool win = false;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            if (x % 2 == 1) win = true;
        }
        cout << (win ? "first" : "second") << "\n";
    }
}
```
