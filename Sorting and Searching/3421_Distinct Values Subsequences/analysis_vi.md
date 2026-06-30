# 3421 - Dãy Con Các Giá Trị Phân Biệt

Nếu một số $x$ xuất hiện $c$ lần trong mảng, ta có thể chọn một trong các lần xuất hiện đó để đưa vào dãy con hoặc không chọn số đó chút nào. Do đó, có $c+1$ cách khả dĩ để chọn cách số $x$ xuất hiện trong dãy con.

Dùng ý tưởng này, ta có thể xử lý từng số riêng biệt và tính đáp án. Cuối cùng, ta cần trừ đi 1 khỏi đáp án vì ta không muốn tính dãy con rỗng.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;
const int M = 1000000007;

int main() {
    int n;
    cin >> n;

    map<int, int> counts;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        counts[x]++;
    }

    ll answer = 1;
    for (auto [value, count] : counts) {
        answer *= (count + 1);
        answer %= M;
    }
    answer = (answer - 1 + M) % M;
    cout << answer << "\n";
}
```
