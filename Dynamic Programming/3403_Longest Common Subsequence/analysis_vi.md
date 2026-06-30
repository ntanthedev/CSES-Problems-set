# 3403 - Dãy con chung dài nhất

Ta sử dụng quy hoạch động để tính độ dài dãy con chung dài nhất cho tất cả các cặp tiền tố của hai mảng đã cho.

Gọi $\textrm{lcs}[i][j]$ là độ dài dãy con chung dài nhất của các dãy $[a\_1,a\_2,\dots,a\_i]$ và $[b\_1,b\_2,\dots,b\_j]$. Nếu $a\_i=b\_j$, thì $\textrm{lcs}[i][j] = \textrm{lcs}[i-1][j-1]+1$ vì các phần tử cuối của hai dãy có thể được ghép cặp. Ngược lại, $\textrm{lcs}[i][j] = \max(\textrm{lcs}[i-1][j], \textrm{lcs}[i][j-1])$, tương ứng với việc bỏ phần tử cuối của dãy thứ nhất hoặc dãy thứ hai.

Cuối cùng, $\textrm{lcs}[n][m]$ cho độ dài dãy con chung dài nhất và ta có thể xây dựng một ví dụ của dãy con đó bằng cách truy vết đường đi tính toán quy hoạch động.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    vector<vector<int>> lcs(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] == b[j]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }

    cout << lcs[n][m] << "\n";

    vector<int> result;
    while (lcs[n][m] > 0) {
        if (a[n] == b[m]) {
            result.push_back(a[n]);
            n--;
            m--;
        } else if (lcs[n - 1][m] == lcs[n][m]) {
            n--;
        } else {
            m--;
        }
    }

    reverse(result.begin(), result.end());
    for (auto x : result) {
        cout << x << " ";
    }
    cout << "\n";
}
```

## Tài liệu tham khảo

* [Dãy con chung dài nhất (Wikipedia)](https://en.wikipedia.org/wiki/Longest_common_subsequence)
