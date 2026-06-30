# 1112 - Xâu con bắt buộc

## Lời giải 1

Giả sử ta đọc các ký tự của một xâu lần lượt và phải phát hiện khi nào
$m$ ký tự cuối cùng tạo thành mẫu. Để làm điều đó, ta phải ghi nhớ
tiền tố dài nhất của mẫu mà cũng là hậu tố của xâu hiện tại.

Ví dụ, nếu mẫu là `ABABC` và ta đã đọc xâu `CAABAB`, thì
tiền tố là `ABAB` (độ dài $4$). Xét điều gì có thể xảy ra khi ta đọc ký tự
tiếp theo:

* Nếu ta đọc `A`, tiền tố trở thành `ABA` (độ dài $3$).
* Nếu ta đọc `B`, tiền tố trở thành rỗng (độ dài $0$).
* Nếu ta đọc `C`, tiền tố trở thành `ABABC` (độ dài $5$).
* Nếu ta đọc bất kỳ ký tự nào khác, tiền tố trở thành rỗng (độ dài $0$).

Ta định nghĩa một hàm chuyển tiếp $\textrm{step}[i][c]$: nếu độ dài của
tiền tố là $i$ và ta đọc ký tự $c$, thì độ dài của tiền tố sau đó là bao
nhiêu? Ví dụ, trong tình huống trên $\textrm{step}[4][\textrm{A}]=3$,
$\textrm{step}[4][B]=0$, và $\textrm{step}[4][\textrm{C}]=5$. Ta cũng định nghĩa
$\textrm{step}[m][c]=m$ cho mọi ký tự $c$ vì trong trường hợp đó mẫu là một
xâu con của xâu, bất kể những ký tự nào sẽ đến sau đó.

Sau đó, ta sử dụng quy hoạch động để giải bài toán. Ta tính các giá trị
$\textrm{ways}[i][j]$: có bao nhiêu cách để tạo một xâu có độ dài $i$
kết thúc với một tiền tố có độ dài $j$ (hoặc chứa toàn bộ mẫu nếu
$j=m$)?

Đáp số của bài toán là $\textrm{ways}[n][m]$, và thuật toán hoạt động trong
$O(nmk)$ thời gian với $k$ là kích thước bảng chữ cái.

```cpp
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

int step[101][128];
ll ways[1001][101];

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int m = s.size();

    for (int i = 0; i < m; i++) {
        for (int c = 'A'; c <= 'Z'; c++) {
            string u = s.substr(0, i) + (char)c;
            while (s.substr(0, u.size()) != u) {
                u = u.substr(1);
            }
            step[i][c] = u.size();
        }
    }
    for (int c = 'A'; c <= 'Z'; c++) {
        step[m][c] = m;
    }

    ways[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int c = 'A'; c <= 'Z'; c++) {
                ways[i + 1][step[j][c]] += ways[i][j];
                ways[i + 1][step[j][c]] %= M;
            }
        }
    }

    cout << ways[n][m] << '\n';
}
```

## Lời giải 2: hàm tiền tố

Việc xây dựng máy trạng thái hữu hạn có thể được tăng tốc bằng cách sử dụng
hàm tiền tố. Nó cho phép ta xây dựng các chuyển tiếp trong $O(nk)$ thời gian.

Hàm tiền tố $\pi(i)$ của một xâu được định nghĩa như sau: mỗi $\pi(i)$
chỉ độ dài lớn nhất của một xâu con kết thúc tại vị trí $i$ và là một tiền tố
thực sự của xâu. Hàm tiền tố có thể quen thuộc từ thuật toán KMP.

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int M = 1000000007;

// Trả về các giá trị của hàm tiền tố cho xâu s.
// Hàm tiền tố pi(i) được định nghĩa như sau: mỗi pi(i) chỉ
// độ dài lớn nhất của một xâu con kết thúc tại vị trí i và là một tiền tố
// thực sự của xâu.
vector<int> prefix_function(string &s) {
    const int n = (int)s.size();
    vector<int> r(n);
    for (int i = 1; i < n; ++i) {
        int j = r[i - 1];
        while (j > 0 && s[i] != s[j]) j = r[j - 1];
        r[i] = j + (s[i] == s[j]);
    }
    return r;
}

int step[101][128];
ll ways[1001][101];

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int m = s.size();
    auto links = prefix_function(s);

    for (int i = 0; i < m; i++) {
        for (int c = 'A'; c <= 'Z'; c++) {
            if (s[i] == c) {
                step[i][c] = i + 1;
            } else if (i > 0) {
                step[i][c] = step[links[i - 1]][c];
            }
        }
    }
    for (int c = 'A'; c <= 'Z'; c++) {
        step[m][c] = m;
    }

    ways[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int c = 'A'; c <= 'Z'; c++) {
                ways[i + 1][step[j][c]] += ways[i][j];
                ways[i + 1][step[j][c]] %= M;
            }
        }
    }

    cout << ways[n][m] << '\n';
}
```

## Tài liệu tham khảo

* [Wikipedia (Knuth–Morris–Pratt algorithm)](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)
