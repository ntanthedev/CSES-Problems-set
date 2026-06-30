# 2428 - Mảng Con Các Giá Trị Phân Biệt II

Ta duyệt mảng từ trái sang phải và tại mỗi vị trí $i$ tính số lượng mảng con hợp lệ kết thúc tại vị trí $i$.

Ta duy trì một cấu trúc dữ liệu `rank` chứa các cặp dạng $(p, x)$: ta đã thấy phần tử $x$ lần cuối tại vị trí $p$. Ta cũng dùng một cấu trúc dữ liệu `prev` lưu vị trí trước đó của mỗi phần tử. Ta đảm bảo `rank` có tối đa $k+1$ cặp và nếu nó có nhiều hơn, ta xóa cặp có $p$ nhỏ nhất.

Nếu `rank` có tối đa $k$ cặp, thì tất cả các mảng con kết thúc tại vị trí $i$ đều hợp lệ. Ngược lại, `rank` có $k+1$ cặp và cặp đầu tiên cho ta vị trí cuối cùng không thuộc về một mảng con hợp lệ.

Ta có thể cập nhật cả hai cấu trúc dữ liệu trong thời gian $O(\log n)$, do đó thuật toán chạy trong $O(n \log n)$.

```cpp
#include <iostream>
#include <map>
#include <set>
using namespace std;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;

    map<int, int> prev;
    set<pair<int, int>> rank;
    ll count = 0;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        rank.erase({prev[x], x});
        rank.insert({i, x});
        prev[x] = i;

        if (rank.size() > k + 1) {
            rank.erase(rank.begin());
        }

        if (rank.size() <= k) {
            count += i;
        } else {
            count += i - rank.begin()->first;
        }
    }

    cout << count << "\n";
}
```
