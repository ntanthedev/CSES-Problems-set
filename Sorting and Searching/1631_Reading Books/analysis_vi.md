# 1631 - Đọc Sách

Nếu có một cuốn sách dài và thời gian đọc cuốn sách đó lớn hơn tổng thời gian đọc tất cả các cuốn sách còn lại, thì đáp án là $2x$ trong đó $x$ là thời gian cần để đọc cuốn sách đó. Trong trường hợp này, Kotivalo có thể đọc cuốn sách dài trước trong khi Justiina đọc tất cả các cuốn sách còn lại. Sau đó, họ đổi vai trò cho nhau.

Ngược lại, đáp án là tổng tất cả thời gian đọc $t\_1+t\_2+\dots+t\_n$. Trong trường hợp này, Kotivalo có thể đọc tất cả các cuốn sách được sắp xếp theo thời gian đọc từ dài nhất đến ngắn nhất. Justiina làm gần như tương tự nhưng bắt đầu với cuốn sách dài thứ hai và đọc cuốn sách dài nhất sau cùng. Điều này đảm bảo rằng họ không bao giờ đọc cùng một cuốn sách tại cùng một thời điểm.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    ll total = 0;
    ll longest = 0;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        total += x;
        longest = max(longest, x);
    }

    cout << max(total, 2 * longest) << "\n";
}
```
