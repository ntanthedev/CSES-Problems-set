# 1697 - Giải đấu cờ vua

Một chiến lược tham lam đơn giản có thể giải quyết bài toán này. Một chứng minh ngắn gọn được đưa ra dưới đây. Cách tiếp cận như sau:

Tại mỗi bước, chọn kỳ thủ có số trận chưa xếp lịch nhiều nhất. Sau đó, ghép kỳ thủ này lần lượt với kỳ thủ có số trận chưa xếp lịch nhiều thứ hai, rồi với kỳ thủ có số trận chưa xếp lịch nhiều thứ ba, v.v. cho đến khi kỳ thủ được chọn có tất cả các trận còn lại được xếp lịch. Lặp lại quy trình này cho đến khi mọi kỳ thủ đều được xếp lịch hết các trận đấu.

Nếu tại bất kỳ thời điểm nào không có đủ kỳ thủ để ghép cặp với kỳ thủ có nhiều trận chưa xếp lịch nhất, thì không thể xây dựng một giải đấu thỏa mãn tất cả các kỳ thủ.

Chúng ta sẽ lưu trữ các kỳ thủ cùng với số trận còn lại của họ trong một `priority_queue`, cho phép tìm hiệu quả kỳ thủ có số trận còn lại nhiều nhất. Cách giải này có độ phức tạp thời gian là $O(M \log n)$, trong đó $M$ là tổng các số đã cho.

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    priority_queue<pair<int, int>> nodes;

    for (int i = 1; i <= n; ++i) {
        int deg;
        cin >> deg;
        if (deg > 0) {
            nodes.emplace(deg, i);
        }
    }

    vector<pair<int, int>> ans;

    while (!nodes.empty()) {
        auto [d, s] = nodes.top();
        nodes.pop();
        if (nodes.size() < d) {
            cout << "IMPOSSIBLE" << '\n';
            return 0;
        }
        vector<pair<int, int>> others;
        for (int t = 1; t <= d; ++t) {
            others.push_back(nodes.top());
            nodes.pop();
        }
        for (auto [a, b] : others) {
            ans.emplace_back(s, b);
            if (a > 1) {
                nodes.emplace(a - 1, b);
            }
        }
    }

    cout << ans.size() << '\n';
    for (auto [a, b] : ans) {
        cout << a << ' ' << b << '\n';
    }
}
```

## Chứng minh

Gọi $a$ là một trong những kỳ thủ có số trận mong muốn lớn nhất $x\_a$. Khẳng định là nếu tồn tại một lời giải hoàn chỉnh, thì cũng có thể tạo ra một lời giải trong đó $a$ chỉ được ghép cặp với các kỳ thủ có số trận mong muốn lớn nhất tiếp theo theo thứ tự.

Cụ thể hơn, cho hai kỳ thủ $b, c$ với $x\_b \ge x\_c$, nếu tồn tại một lời giải không chứa trận đấu $(a, b)$ mà chỉ chứa trận đấu với kỳ thủ có số trận mong muốn nhỏ hơn (hoặc bằng), $(a, c)$, thì cũng tồn tại một lời giải thay thế chứa trận đấu $(a, b)$ nhưng không chứa $(a, c)$.

Hóa ra lời giải hiện có với trận đấu $(a, c)$ có thể được biến đổi thành dạng mong muốn.

Vì $x\_b \ge x\_c$, phải tồn tại một kỳ thủ $d \neq a,b,c$ có trận đấu với $b$ nhưng không với $c$. Điều này được đảm bảo ngay cả trong trường hợp $x\_b = x\_c$ vì $c$ có trận đấu với $a$ trong khi $b$ thì không, do đó $b$ phải có thêm một trận với người khác.

Khi đó ta có thể thay thế các trận $(a, c)$ và $(b, d)$ bằng các trận $(a, b)$ và $(c, d)$. Tổng số trận đấu của mỗi kỳ thủ không thay đổi, và không có cặp kỳ thủ nào chơi với nhau hai lần vì các trận $(a, b)$ và $(c, d)$ trước đó không tồn tại.

Sau khi chọn tất cả các trận cho kỳ thủ $a$, ta thu được một bài toán nhỏ hơn cùng dạng, vẫn có thể giải được nếu bài toán gốc cũng vậy.

## Tài liệu tham khảo

* [Wikipedia (Thuật toán Havel–Hakimi)](https://en.wikipedia.org/wiki/Havel%E2%80%93Hakimi_algorithm)
* [Wikipedia (Định lý Erdős–Gallai)](https://en.m.wikipedia.org/wiki/Erd%C5%91s%E2%80%93Gallai_theorem)
