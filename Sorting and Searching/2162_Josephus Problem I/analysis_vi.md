# 2162 - Josephus Problem I

Ta tạo một vector ban đầu gồm các số $1,2,\dots,n$. Sau đó ta duyệt qua vector và mô phỏng bài toán. Ta thêm mỗi số ở vị trí chẵn vào cuối vector và in ra mỗi số ở vị trí lẻ.

Ta sẽ xử lý tổng cộng $n+n/2+n/4+\dots = O(n)$ số, do đó thuật toán chạy trong $O(n)$ thời gian.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }

    for (int i = 0; i < v.size(); i++) {
        if (i % 2 == 0) {
            v.push_back(v[i]);
        } else {
            cout << v[i] << " ";
        }
    }
    cout << "\n";
}
```

## Tài liệu tham khảo

* [Josephus problem (Wikipedia)](https://en.wikipedia.org/wiki/Josephus_problem)
