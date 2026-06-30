# 1755 - Palindrome Reorder

Gọi $\textrm{count}(c)$ là số lần xuất hiện của chữ cái $c$ trong xâu. Ta có thể tạo một palindrome nếu $\textrm{count}(c)$ lẻ với nhiều nhất một chữ cái $c$.

Để tạo palindrome, đầu tiên ta duyệt từ A đến Z và thêm $\lfloor \textrm{count}(c)/2 \rfloor$ bản sao của mỗi chữ cái $c$ vào xâu. Sau đó, nếu có chữ cái nào xuất hiện với số lần lẻ, ta thêm nó làm chữ cái trung tâm. Cuối cùng, ta duyệt từ Z đến A và thêm $\lfloor \textrm{count}(c)/2 \rfloor$ bản sao của mỗi chữ cái $c$ vào xâu.

```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;

    map<char, int> count;
    for (auto c : s) {
        count[c]++;
    }

    int odds = 0;
    char center;
    for (char c = 'A'; c <= 'Z'; c++) {
        if (count[c] % 2 == 1) {
            odds++;
            center = c;
        }
    }

    if (odds > 1) {
        cout << "NO SOLUTION\n";
    } else {
        for (char c = 'A'; c <= 'Z'; c++) {
            cout << string(count[c] / 2, c);
        }
        if (odds) {
            cout << center;
        }
        for (char c = 'Z'; c >= 'A'; c--) {
            cout << string(count[c] / 2, c);
        }
        cout << "\n";
    }
}
```
