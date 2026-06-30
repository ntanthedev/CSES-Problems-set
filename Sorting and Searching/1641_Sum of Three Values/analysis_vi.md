# 1641 - Tổng Ba Giá Trị

Giả sử ta biết giá trị ngoài cùng bên trái trong tổng là $a\_i$. Khi đó bài toán còn lại là tạo tổng $x-a\_i$ bằng hai giá trị phân biệt trong mảng con $a\_{i+1} \dots a\_n$, đây là bài toán dễ hơn.

Sử dụng ý tưởng này, ta có thể duyệt qua tất cả các cách chọn $a\_i$ và giải bài toán. Tuy nhiên, trước hết ta sắp xếp mảng để có thể giải bài toán con chọn hai giá trị trong thời gian $O(n)$ bằng kỹ thuật hai con trỏ. Thuật toán kết quả chạy trong thời gian $O(n^2)$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<pair<int, int>> v;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        v.emplace_back(a, i);
    }
    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++) {
        int y = x - v[i].first;
        int a = i + 1;
        int b = n - 1;
        while (a < b) {
            int s = v[a].first + v[b].first;
            if (s == y) {
                cout << v[i].second << " ";
                cout << v[a].second << " ";
                cout << v[b].second << "\n";
                return 0;
            } else if (s > y) {
                b--;
            } else {
                a++;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}
```

Bài toán này được gọi là bài toán 3SUM và nó là một bài toán quan trọng vì nhiều bài toán khác có thể quy về nó. Trong một thời gian dài, người ta cho rằng không thể giải 3SUM hiệu quả hơn $O(n^2)$, nhưng vào năm 2014, một thuật toán tốt hơn đã được tìm ra.

## Tài liệu tham khảo

* [3SUM (Wikipedia)](https://en.wikipedia.org/wiki/3SUM)
* King, J.: [A survey of 3SUM-hard problems](http://www.cs.mcgill.ca/~jking/papers/3sumhard.pdf) (2004)
* Grønlund, A., Pettie, S.: Threesomes, degenerates, and love triangles. IEEE 55th Annual Symposium on Foundations of Computer Science (2014) ([bản arXiv](https://arxiv.org/abs/1404.0799))
