# 1087 - Dãy Con Ngắn Nhất

Chúng tôi sẽ trình bày một thuật toán tham lam và một phiên bản đơn giản hóa khác của cùng một thuật toán.

Bắt đầu bằng cách tạo một mảng hai chiều. Điền mảng này cho mỗi ký tự và vị trí với vị trí tiếp theo mà ký tự đó xuất hiện trong xâu. Với mảng này, chúng ta có thể kiểm tra xem một dãy con có xuất hiện trong xâu hay không. Điều này có thể được thực hiện bằng cách duyệt qua dãy con từng ký tự một và nhảy đến lần xuất hiện tiếp theo của ký tự đó. Nếu tại bất kỳ điểm nào không có lần xuất hiện như vậy, thì xâu đó không phải là dãy con của xâu ban đầu.

Nếu xâu ban đầu chứa tất cả bốn ký tự, câu trả lời sẽ luôn có một tiền tố là dãy con của xâu. Một tiền tố có độ dài tối ưu có thể được tìm bằng thuật toán tham lam, tức là chúng ta luôn thêm ký tự có lần xuất hiện tiếp theo có chỉ số lớn nhất. Luôn tối ưu khi nhảy xa nhất có thể vì các mảng lần xuất hiện là tăng dần. Bất cứ khi nào một trong các ký tự không có lần xuất hiện tiếp theo, chúng ta thêm ký tự đó vào xâu và có câu trả lời.

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e6;
const int INF = 1e9;

int nxt[N + 1][4];

int main() {
    string s;
    cin >> s;

    int n = s.size();

    for (int j = 0; j < 4; ++j) {
        nxt[n][j] = INF;
    }

    for (int i = n; i > 0; --i) {
        for (int j = 0; j < 4; ++j) {
            nxt[i - 1][j] = nxt[i][j];
        }
        int idx = string("ACGT").find(s[i - 1]);
        nxt[i - 1][idx] = i;
    }

    int i = 0;
    string ans;
    while (i < INF) {
        int c = max_element(nxt[i], nxt[i] + 4) - nxt[i];
        ans += "ACGT"[c];
        i = nxt[i][c];
    }

    cout << ans << '\n';
}
```

Giải pháp này có thể được đơn giản hóa rất nhiều. Hãy nhớ rằng, tại bất kỳ thời điểm nào, ký tự tiếp theo được chọn sẽ là ký tự có lần xuất hiện tiếp theo có chỉ số lớn nhất. Ký tự này có thể được tìm bằng cách duy trì một tập hợp các ký tự đã thấy. Bất cứ khi nào chúng ta đã thấy ba ký tự và gặp ký tự thứ tư, chúng ta biết ký tự thứ tư là ký tự có khoảng cách lớn nhất từ chỉ số của ký tự được chọn cuối cùng.

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    string s;
    cin >> s;

    string ans;
    set<char> seen;

    for (char c : s) {
        seen.insert(c);
        if (seen.size() == 4) {
            ans += c;
            seen.clear();
        }
    }

    for (char c : "ACGT") {
        if (!seen.count(c)) {
            ans += c;
            break;
        }
    }

    cout << ans << '\n';
}
```
