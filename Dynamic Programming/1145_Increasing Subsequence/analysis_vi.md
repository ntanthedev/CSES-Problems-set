# 1145 - Increasing Subsequence

Một cách tiếp cận trực tiếp cho bài toán này sử dụng quy hoạch động là thử
thêm một phần tử vào dãy con tăng dài nhất kết thúc tại mỗi phần tử trước đó.
Hàm $\mathrm{LIS}(i)$ mô tả dãy con tăng dài nhất kết thúc tại vị trí $i$.
Công thức truy hồi là

$$\mathrm{LIS}(i) =
\min\_{j < i,\ x\_j < x\_i} \mathrm{LIS}(j) + 1,$$

ngoài ra quy định $\mathrm{LIS}(i) = 1$ nếu không có phần tử nhỏ hơn nào ở
trước.

Kiểm tra từng phần tử trước đó bằng một vòng lặp tạo ra thuật toán $O(n^2)$,
quá chậm.

Ứng viên tốt nhất có thể được tìm nhanh hơn với một cấu trúc dữ liệu nào đó
lưu trữ tất cả các phần tử trước đó và các giá trị $\mathrm{LIS}$ tương ứng,
và cho phép truy vấn $\mathrm{LIS}$ lớn nhất trong số các phần tử nhỏ hơn một
giá trị cho trước (tức là $x\_i$).

Cả hai lời giải được trình bày dưới đây đều cải thiện độ phức tạp thời gian
lên $O(n \log n)$.

## Lời giải 1 (cây phân đoạn)

Cây phân đoạn (segment tree) hoặc cây Fenwick là những lựa chọn tốt để cài đặt
các yêu cầu nêu trên. Nén tọa độ (coordinate compression) được thực hiện trước
tiên trên các giá trị $x\_i$ để phù hợp với kích thước cây tĩnh.

Lưu ý rằng hàm truy vấn `get_max` luôn trả về 0 khi không có phần tử nhỏ hơn
nào ở trước, kể cả với `get_max(0, -1)`.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

void update(int i, int x) {
    i += TREE_SIZE;
    tree[i] = max(tree[i], x);
    while (i > 1) {
        i /= 2;
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

int get_max(int l, int r) {
    int res = 0;
    l += TREE_SIZE;
    r += TREE_SIZE;
    while (l <= r) {
        if (l % 2 == 1) res = max(res, tree[l++]);
        if (r % 2 == 0) res = max(res, tree[r--]);
        l /= 2;
        r /= 2;
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> sorted(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sorted[i] = x[i];
    }

    sort(sorted.begin(), sorted.end());

    for (int i = 0; i < n; ++i) {
        x[i] = lower_bound(sorted.begin(), sorted.end(), x[i]) - sorted.begin();
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        int len = get_max(0, x[i] - 1) + 1;
        update(x[i], len);
        result = max(result, len);
    }

    cout << result << endl;
}
```

## Lời giải 2 (mảng tăng dần)

Các tính chất của giá trị $\mathrm{LIS}$ có thể được sử dụng để thiết kế một
lời giải đơn giản hơn chỉ với một mảng và tìm kiếm nhị phân.

Mảng $\mathrm{best}$ được duy trì sao cho $\mathrm{best}[v]$ chứa phần tử
$x\_i$ nhỏ nhất có $\mathrm{LIS}(i) = v$. Không có giá trị $\mathrm{LIS}$ nào
lớn hơn $n$, vì vậy mảng này chỉ cần kích thước $n + 1$.

Tính đến giá trị $\mathrm{LIS}$ lớn nhất đã gặp, mảng $\mathrm{best}$ là tăng
dần. Điều này là do để một phần tử $x\_i$ nào đó có $\mathrm{LIS}(i) = v > 1$,
phải tồn tại một phần tử nhỏ hơn $x\_j$ ở trước, $j < i$ sao cho
$\mathrm{LIS}(j) = v-1$. Do đó $\mathrm{best}[v-1]$ không vượt quá $x\_j$.

Vì mảng tăng dần, tìm kiếm nhị phân có thể được dùng để tìm giá trị
$\mathrm{LIS}$ lớn nhất $v$ mà vẫn có phần tử tương ứng
$\mathrm{best}[v] = x\_j$ nhỏ hơn $x\_i$.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) cin >> x[i];

    vector<int> best(n + 1);
    best[0] = 0;
    int result = 0;
    for (int i = 0; i < n; ++i) {
        int len = lower_bound(best.begin(), best.begin() + result + 1, x[i]) -
                  best.begin();
        if (len > result) {
            result = len;
            best[len] = x[i];
        } else {
            best[len] = min(best[len], x[i]);
        }
    }

    cout << result << endl;
}
```

## Tài liệu tham khảo

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chương 7,
  Dãy con tăng dài nhất
* [CP-Algorithms, Dãy con tăng dài nhất](https://cp-algorithms.com/sequences/longest_increasing_subsequence.html)
