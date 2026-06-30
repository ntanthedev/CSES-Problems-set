# 2206 - Truy vấn tiệm pizza

Bài toán này hơi khó giải hơn một chút
với cây phân đoạn thông thường.

Chúng ta hãy xem xét các mức giá
trong trường hợp của một vài chỉ số đầu tiên.

Các mức giá cho vị trí đầu tiên sẽ như thế này
$$p\_0+0,\ p\_1+1,\ p\_2+2,\ p\_3+3\ldots$$
và các mức giá cho vị trí thứ hai như thế này
$$p\_0+1,\ p\_1+0,\ p\_2+1,\ p\_3+2\ldots$$

Như có thể thấy từ các ví dụ,
các mức giá cho tòa nhà thứ hai
trông gần như giống hệt với các mức giá
cho tòa nhà thứ nhất.
Thực tế, từ tòa nhà thứ hai trở đi,
tất cả các mức giá chỉ khác nhau
đúng một đơn vị.

Được thúc đẩy bởi những quan sát này,
một ý tưởng về cây phân đoạn nơi
chỉ số của mỗi phần tử được
cộng vào giá trị của nó xuất hiện trong đầu.

Các cây phân đoạn này sẽ cần
được xây dựng riêng cho cả hai
hướng. Hóa ra cách này hiệu quả.

Trong các lời giải đính kèm, hai
cây phân đoạn được sử dụng –
$\texttt{left\\_tree}$
và
$\texttt{right\\_tree}$.

Vào
$\texttt{left\\_tree}$
chúng ta sẽ lưu trữ,
tại mỗi vị trí $i$,
giá trị $p\_i-i$
và
vào
$\texttt{right\\_tree}$
chúng ta sẽ lưu trữ,
tại mỗi vị trí $i$,
giá trị $p\_i+i$.
Sau đó, chúng ta có thể trả lời các truy vấn
bằng cách lấy các giá trị nhỏ nhất
riêng rẽ, dịch chuyển chúng
theo chỉ số hiện tại
và trả về giá trị nhỏ hơn trong hai giá trị đó.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = (int)1e9;

struct Tree {
    int tree_size;
    vector<int> t;
    Tree(int n) {
        tree_size = 1;
        while (tree_size < n) {
            tree_size *= 2;
        }
        t.resize(tree_size * 2);
    }
    // Thay đổi giá trị tại vị trí k thành x.
    void change(int k, int x) {
        k += tree_size;
        t[k] = x;
        while (k > 1) {
            k /= 2;
            t[k] = min(t[k * 2], t[k * 2 + 1]);
        }
    }
    // Trả về giá trị nhỏ nhất trong đoạn [l, r]
    int query(int l, int r) {
        int ans = INF;
        l += tree_size;
        r += tree_size;
        while (l <= r) {
            if (l % 2 == 1) ans = min(ans, t[l++]);
            if (r % 2 == 0) ans = min(ans, t[r--]);
            l /= 2;
            r /= 2;
        }
        return ans;
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    Tree left_tree(n), right_tree(n);

    vector<int> p(n);

    auto update = [&](int i) {
        left_tree.change(i, p[i] - i);
        right_tree.change(i, p[i] + i);
    };

    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        update(i);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t;
        cin >> t;
        if (t == 1) {
            int i;
            cin >> i;
            i--;
            cin >> p[i];
            update(i);
        } else {
            int i;
            cin >> i;
            i--;
            int left_ans = left_tree.query(0, i) + i;
            int right_ans = right_tree.query(i, n - 1) - i;
            cout << min(left_ans, right_ans) << '\n';
        }
    }
}
```
