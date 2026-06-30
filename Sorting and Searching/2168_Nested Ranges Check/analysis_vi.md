# 2168 - Nested Ranges Check

Ta có thể giải bài toán này bằng cách sắp xếp các đoạn một cách thông minh, và hóa ra cả hai bài toán con đều có thể giải bằng cùng một ý tưởng.

Trước hết hãy tập trung vào bài toán con đầu tiên: tìm các đoạn chứa một đoạn khác. Ta sắp xếp các đoạn theo thứ tự tăng dần của đầu mút phải, và thứ tự phụ là giảm dần của đầu mút trái. Sau đó ta duyệt qua các đoạn và duy trì một giá trị $p$: vị trí xa nhất bên phải của một đầu mút trái. Một đoạn $[x,y]$ chứa một đoạn khác khi và chỉ khi $p \ge x$.

Tiếp theo xét bài toán con thứ hai: tìm các đoạn được chứa trong đoạn khác. Lần này ta sắp xếp các đoạn theo thứ tự tăng dần của đầu mút trái, và thứ tự phụ là giảm dần của đầu mút phải. Ta duy trì một giá trị $p$ lưu vị trí xa nhất bên phải của một đầu mút phải, và một đoạn khác chứa đoạn $[x,y]$ khi và chỉ khi $y \le p$.

Trong đoạn mã sau, ta sử dụng hàm `solve` cho cả hai bài toán con. Có một mẹo cài đặt nhỏ: ta sử dụng đầu mút âm để dễ dàng sắp xếp theo thứ tự phụ giảm dần.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;

void solve(vector<vector<int>> ranges) {
    vector<int> check(n + 1);

    int pos = 0;
    for (auto r : ranges) {
        if (pos >= -r[1]) {
            check[r[2]] = 1;
        }
        pos = max(pos, -r[1]);
    }

    for (int i = 1; i <= n; i++) {
        cout << check[i] << " ";
    }
    cout << "\n";
}

int main() {
    cin >> n;

    vector<vector<int>> ranges1;
    vector<vector<int>> ranges2;

    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        ranges1.push_back({y, -x, i});
        ranges2.push_back({x, -y, i});
    }

    sort(ranges1.begin(), ranges1.end());
    sort(ranges2.begin(), ranges2.end());

    solve(ranges1);
    solve(ranges2);
}
```
