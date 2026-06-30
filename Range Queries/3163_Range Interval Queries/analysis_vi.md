# 3163 - Range Interval Queries (Truy vấn Khoảng Trên Đoạn)

# Giải pháp 1 ($O(n \log n + q \log^2 n)$)

Chúng ta tạo một cây phân đoạn mà mỗi nút chứa một danh sách đã được sắp xếp các giá trị trong cây con tương ứng. Ta có thể xây dựng cây trong thời gian $O(n \log n)$ bằng kỹ thuật tương tự merge sort.

Sau đó, ta có thể xử lý mỗi truy vấn trong thời gian $O(\log^2 n)$ bằng cách sử dụng tìm kiếm nhị phân để đếm số lượng giá trị trong mỗi nút của cây phân đoạn.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1 << 18;

vector<int> tree[2 * N];

int query(int a, int b, int c, int d) {
    a += N;
    b += N;

    int count = 0;

    while (a <= b) {
        if (a % 2 == 1) {
            count += upper_bound(tree[a].begin(), tree[a].end(), d) -
                     lower_bound(tree[a].begin(), tree[a].end(), c);
            a++;
        }
        if (b % 2 == 0) {
            count += upper_bound(tree[b].begin(), tree[b].end(), d) -
                     lower_bound(tree[b].begin(), tree[b].end(), c);
            b--;
        }
        a /= 2;
        b /= 2;
    }

    return count;
}

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        tree[N + i] = {x};
    }

    for (int i = N - 1; i >= 1; i--) {
        merge(tree[2 * i].begin(), tree[2 * i].end(), tree[2 * i + 1].begin(),
              tree[2 * i + 1].end(), back_inserter(tree[i]));
    }

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        cout << query(a, b, c, d) << "\n";
    }
}
```

# Giải pháp 2 ($O((n+q) \log n)$)

Chúng ta tạo một danh sách sự kiện bao gồm một sự kiện cho mỗi phần tử mảng và hai sự kiện cho mỗi truy vấn. Ta cũng duy trì một cây phân đoạn để tính tổng.

Các sự kiện được tạo như sau:

* Sự kiện $1$: Bắt đầu một truy vấn với khoảng giá trị $[c,d]$ (thời gian xử lý $c$)
* Sự kiện $2$: Xử lý giá trị mảng $x$ (thời gian xử lý $x$)
* Sự kiện $3$: Kết thúc một truy vấn với khoảng giá trị $[c,d]$ (thời gian xử lý $d$)

Sau khi tạo các sự kiện, ta sắp xếp chúng và duyệt theo thứ tự thời gian xử lý tăng dần.
Nếu hai sự kiện có cùng thời gian xử lý, ta xử lý chúng theo thứ tự loại sự kiện.

Xét một truy vấn với khoảng mảng $[a,b]$ và ta muốn đếm số lượng giá trị trong đoạn $[c,d]$. Đầu tiên ta tính số lượng giá trị trong đoạn $[1,c-1]$ bằng cây phân đoạn (sự kiện loại $1$). Sau đó ta xử lý tất cả các giá trị mảng trong đoạn $[c,d]$ và thêm chúng vào cây phân đoạn (sự kiện loại $2$). Cuối cùng ta tính số lượng giá trị trong đoạn $[1,d]$ bằng cây phân đoạn (sự kiện loại $3$).

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1 << 18;

int tree[2 * N];

void set_val(int pos) {
    pos += N;
    tree[pos] = 1;

    for (pos /= 2; pos >= 1; pos /= 2) {
        tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
    }
}

int get_sum(int a, int b) {
    a += N;
    b += N;

    int sum = 0;
    while (a <= b) {
        if (a % 2 == 1) {
            sum += tree[a++];
        }
        if (b % 2 == 0) {
            sum += tree[b--];
        }
        a /= 2;
        b /= 2;
    }
    return sum;
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> events;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        events.push_back({x, 2, i});
    }

    for (int i = 1; i <= q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        events.push_back({c, 1, a, b, i});
        events.push_back({d, 3, a, b, i});
    }

    sort(events.begin(), events.end());

    vector<int> result(q + 1);

    for (auto event : events) {
        if (event[1] == 1) {
            int sum = get_sum(event[2], event[3]);
            result[event[4]] -= sum;
        }

        if (event[1] == 2) {
            set_val(event[2]);
        }

        if (event[1] == 3) {
            int sum = get_sum(event[2], event[3]);
            result[event[4]] += sum;
        }
    }

    for (int i = 1; i <= q; i++) {
        cout << result[i] << "\n";
    }
}
```
