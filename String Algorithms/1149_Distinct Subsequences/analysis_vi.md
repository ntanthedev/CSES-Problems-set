# 1149 - Các xâu con phân biệt

Ta duyệt qua xâu từ trái sang phải và với mỗi ký tự $c$, duy trì
số lượng các xâu con phân biệt có ký tự cuối cùng là $c$.
Điều này có thể được thực hiện hiệu quả bằng quy hoạch động.
Cuối cùng, đáp số của bài toán là tổng của tất cả các giá trị đó.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

const int M = 1000000007;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    map<char, int> count;
    for (int i = 0; i < n; i++) {
        int sum = 1;
        for (int c = 'a'; c <= 'z'; c++) {
            sum += count[c];
            sum %= M;
        }
        count[s[i]] = sum;
    }

    ll ans = 0;
    for (int c = 'a'; c <= 'z'; c++) {
        ans += count[c];
        ans %= M;
    }

    cout << ans << "\n";
}
```

Đây là một cài đặt ngắn gọn hơn sử dụng một biến phụ để
lưu tổng của tất cả các giá trị quy hoạch động.
Sử dụng kỹ thuật này, ta không cần vòng lặp để tính tổng.

```cpp
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

const int M = 1000000007;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    map<char, int> count;
    int total_sum = 0;
    for (int i = 0; i < n; i++) {
        int old = count[s[i]];
        count[s[i]] = total_sum + 1;
        total_sum += count[s[i]] - old;
        total_sum = (total_sum % M + M) % M;
    }

    cout << total_sum << "\n";
}
```
