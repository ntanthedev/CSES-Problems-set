# 2186 - Xâu Con Đặc Biệt

Trong bài phân tích này, ta giả sử mỗi ký tự từ $\texttt{a}$ đến $\texttt{z}$ đều xuất hiện trong xâu. Nếu không phải như vậy, cần thực hiện thêm một số thao tác để bỏ qua các ký tự bị thiếu.

Gọi $C\_{i, c}$ là số lần xuất hiện của ký tự $c$ trong $i$ ký tự đầu tiên. Khi đó, ký tự $c$ xuất hiện trong xâu con gồm các ký tự ở chỉ số $[i, j)$ đúng $C\_{j, c} - C\_{i, c}$ lần.

Để một xâu con là đặc biệt, mọi ký tự cần xuất hiện cùng một số lần. Ta không quan tâm đến giá trị cụ thể đó, do đó ta có thể lưu trạng thái số lần xuất hiện của các ký tự so với một ký tự tham chiếu, gọi là $\texttt{a}$:
$$\begin{align\*}
\big( & C\_{i,\texttt{a}}-C\_{i,\texttt{a}}, \\
& C\_{i,\texttt{b}}-C\_{i,\texttt{a}}, \\
& \dots, \\
& C\_{i,\texttt{z}}-C\_{i,\texttt{a}}
\big),
\end{align\*}$$
Xét một ký tự $x$ bất kỳ. Lưu ý rằng nếu ta thêm cùng một số lần xuất hiện của cả $x$ và ký tự tham chiếu $\texttt{a}$, thì giá trị tương đối không đổi, nghĩa là chỉ cần đếm số lần xuất hiện trước đó của cùng một trạng thái.

Ta sẽ lưu trạng thái hiện tại trong một `array<int, 26>` và các trạng thái trước đó vào một `map`. Độ phức tạp thời gian của một thao tác trên map là $O(\log n \cdot \Sigma)$, trong đó $\Sigma$ là kích thước bảng chữ cái. Độ phức tạp thời gian của toàn bộ lời giải là $O(n \log n \cdot \Sigma)$.

```cpp
#include <array>
#include <iostream>
#include <map>
using namespace std;
using ll = long long;

using A = array<int, 26>;

int main() {
    string s;
    cin >> s;

    bool seen[26]{};
    char reference_char = s[0];

    for (char c : s) seen[c - 'a'] = true;

    map<A, int> m;
    A cur{};
    m[cur] = 1;
    ll ans = 0;

    for (char c : s) {
        if (c == reference_char) {
            for (int i = 0; i < 26; ++i) {
                if (seen[i]) cur[i]--;
            }
        }
        cur[c - 'a']++;
        ans += m[cur];
        m[cur]++;
    }

    cout << ans << '\n';
}
```
