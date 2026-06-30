# 1749 - Xóa phần tử khỏi danh sách

## Cách tiếp cận thứ nhất: Cây phân đoạn

Chúng ta có thể sử dụng cây phân đoạn để giải bài toán này.
Trong cây, các phần tử còn hoạt động (chưa bị xóa)
được biểu diễn bởi số một và các phần tử không hoạt động (đã xóa) bởi
số không.

Để tìm giá trị đang hoạt động thứ $k$, chúng ta sẽ thực hiện
tìm kiếm nhị phân trên cây.

```cpp
#include <iostream>
using namespace std;

const int TREE_SIZE = 1 << 18;
int tree[TREE_SIZE * 2];

// Thay đổi giá trị tại vị trí i thành x.
void change(int i, int x) {
    i += TREE_SIZE;
    tree[i] = x;
    while (i > 1) {
        i /= 2;
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
}

// Trả về chỉ số của vị trí 'đang hoạt động' thứ k.
int query(int k) {
    int s = 1;
    while (s < TREE_SIZE) {
        // Chỉ số của con trái là s * 2.
        // Chỉ số của con phải là s * 2 + 1.
        if (tree[s * 2] >= k) {
            s = s * 2;
        } else {
            k -= tree[s * 2];
            s = s * 2 + 1;
        }
    }
    return s - TREE_SIZE;
}

const int N = 200001;
int x[N];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
        change(i, 1);
    }

    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        int pos = query(p);
        cout << x[pos] << ' ';
        change(pos, 0);
    }
    cout << '\n';
}
```

### Tài liệu tham khảo về cây phân đoạn

* [CPHB (Sổ tay Lập trình viên Thi đấu)](http://cses.fi/book), Chương 9
* [CP-Algorithms, Cây phân đoạn](https://cp-algorithms.com/data_structures/segment_tree.html)

## Cách tiếp cận thứ hai: Cấu trúc dữ liệu dựa trên chính sách (Policy-based)

Trình biên dịch g++ – trình biên dịch được sử dụng trên CSES – có một số cấu trúc dữ liệu tích hợp sẵn không thuộc thư viện chuẩn C++.
Một trong những cấu trúc dữ liệu này là cây nhị phân, tương tự `std::set`.
Cây tìm kiếm nhị phân này cung cấp một số chức năng bổ sung hữu ích,
bao gồm một hàm để tìm phần tử thứ i trong tập hợp.

Với hàm này, chúng ta có thể giải bài toán mà không cần sử dụng cây phân đoạn.

```cpp
#include <iostream>
using namespace std;

// Các dòng này cần thiết cho cấu trúc dữ liệu dựa trên chính sách.
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 200001;
int x[N];

int main() {
    int n;
    cin >> n;

    indexed_set<int> s;

    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
        s.insert(i);
    }

    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        // Lưu ý rằng hàm `find_by_order` mong đợi
        // một vị trí theo chỉ số 0.
        auto it = s.find_by_order(p - 1);
        int pos = *it;
        cout << x[pos] << ' ';
        s.erase(it);
    }
    cout << '\n';
}
```

Lưu ý rằng những cấu trúc dữ liệu không chính thống này hiếm khi
được sử dụng trong lời giải dự kiến của một bài toán lập trình thi đấu.
Tuy nhiên, chúng đáng để biết vì đôi khi chúng rất hữu ích và có thể được sử dụng để đạt được độ phức tạp thời gian tốt hơn và cài đặt ngắn hơn nhiều.

Cuối cùng, cây tìm kiếm nhị phân dựa trên chính sách có một cạm bẫy đáng chú ý:
không có giải pháp dựa trên chính sách thay thế cho `std::multiset`. Để giải quyết vấn đề này,
có thể lưu `std::pair` trong cây với
phần tử thứ hai của mỗi cặp là một giá trị duy nhất.

### Tài liệu tham khảo về cấu trúc dữ liệu dựa trên chính sách

* [CPHB (Sổ tay Lập trình viên Thi đấu)](http://cses.fi/book), Chương 4
* [Codeforces, *C++ STL: Policy based data structures* bởi adamant](https://codeforces.com/blog/entry/11080)
* [Codeforces, *C++ STL: Policy based data structures. Part 2* bởi adamant](https://codeforces.com/blog/entry/13279)
* [The GNU C++ Library Manual](https://gcc.gnu.org/onlinedocs/libstdc++/manual/policy_data_structures_design.html), Chương 21. Policy-Based Data Structures
