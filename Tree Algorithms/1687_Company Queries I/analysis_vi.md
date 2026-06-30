# 1687 - Truy vấn công ty I

## Cách tiếp cận thứ nhất

Bài toán này có thể được giải bằng một kỹ thuật gọi là *binary lifting*.

Với mỗi đỉnh, ta sẽ tính toán trước câu trả lời cho các bước nhảy có độ dài $2^k$, với $2^k\le n$.
Lớp bước nhảy tiếp theo có thể được xây dựng trong thời gian tuyến tính từ lớp trước đó.
Ví dụ, để tính bước nhảy độ dài hai, ta thực hiện hai bước nhảy liên tiếp độ dài một.

Có $O(\log n)$ bước nhảy như vậy cho mỗi đỉnh,
điều này có nghĩa là việc tính toán trước tốn $O(n \log n)$ thời gian và bộ nhớ.

Khi trả lời truy vấn, biểu diễn nhị phân của $k$ cho ta biết cần thực hiện những bước nhảy nào.
Việc trả lời một truy vấn đơn lẻ tốn $O(\log(n))$ thời gian, nghĩa là
trả lời tất cả các truy vấn tốn tổng cộng $O(q\log n)$ thời gian.

```cpp
#include <iostream>
using namespace std;

const int N = 200001;

int jmp[N][20];

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 2; i <= n; ++i) {
        cin >> jmp[i][0];
    }

    for (int j = 0; (1 << j) <= n; ++j) {
        for (int i = 1; i <= n; ++i) {
            jmp[i][j + 1] = jmp[jmp[i][j]][j];
        }
    }

    for (int qi = 0; qi < q; ++qi) {
        int x, k;
        cin >> x >> k;

        for (int j = 19; j >= 0; --j) {
            if (k >> j & 1) {
                x = jmp[x][j];
            }
        }

        cout << (x ? x : -1) << '\n';
    }
}
```

## Cách tiếp cận thứ hai

Để đạt được độ phức tạp bộ nhớ tốt hơn, ta có thể sử dụng heavy-light decomposition.
Tuy nhiên, ở đây tôi muốn trình bày một giải pháp khác, sử dụng
một kỹ thuật ít được biết đến hơn đôi khi được gọi là *jump pointers*.

Kỹ thuật này lần đầu tiên được giới thiệu trong một bài báo năm 1983 của Eugene W. Myers có tựa đề
*An applicative random-access stack*. Năm 2020, nó được phổ biến trong
cộng đồng lập trình thi đấu bởi người dùng *Codeforces* Urbanowicz qua
bài viết "Binary Lifting, No Memory Wasted" của anh ấy.

Độ phức tạp bộ nhớ được cải thiện $O(n)$ đến từ thực tế là
ta chỉ lưu một bước nhảy cho mỗi đỉnh thay vì $O(\log n)$ bước nhảy.
Các bước nhảy này được xây dựng theo một cách đặc biệt. Hy vọng bạn có thể nhận ra
mô hình tổng quát từ hình ảnh sau.

![](333be7d0375a2686f8b85fe4fe5974aefcbb44b12e89661512b9b8e81fb1462d)

Ý tưởng là tạo một bước nhảy dài hơn khi hai bước nhảy liên tiếp từ đỉnh cha có cùng độ dài.
Thực hiện theo cách này, các bước nhảy sẽ có độ dài $1, 3, 7\dots$ tức là $2^n-1$.
Bản chất mũ của độ dài các bước nhảy làm cho độ phức tạp thời gian trả lời truy vấn trở thành logarit.
Chứng minh đầy đủ có thể được tìm thấy trong bài báo.

Một cài đặt sử dụng kỹ thuật *jump pointers* có thể được tìm thấy bên dưới.
Với mỗi đỉnh, ta cần lưu:

* độ sâu của đỉnh
* đỉnh cha của đỉnh
* đỉnh mà ta đáp đến khi nhảy từ đỉnh hiện tại
* kích thước của bước nhảy.

Khi trả lời một truy vấn, ta nên tham lam lấy bước nhảy dài nhất có thể mà không nhảy quá đích đến của chúng ta.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;

int parent[N];
int depth[N];
int jump[N];
int jump_size[N];
vector<int> g[N];

void dfs(int node) {
    for (int child : g[node]) {
        depth[child] = depth[node] + 1;
        parent[child] = node;
        jump[child] = node;
        jump_size[child] = 1;
        if (jump[node] && jump[jump[node]] &&
            jump_size[node] == jump_size[jump[node]]) {
            jump[child] = jump[jump[node]];
            jump_size[child] = jump_size[node] * 2 + 1;
        }
        dfs(child);
    }
}

int make_jumps(int x, int k) {
    if (depth[x] < k) {
        return -1;
    }
    while (k) {
        if (jump_size[x] <= k) {
            k -= jump_size[x];
            x = jump[x];
        } else {
            k--;
            x = parent[x];
        }
    }
    return x;
}

int main() {
    int n, q;

    cin >> n >> q;

    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(1);

    for (int qi = 0; qi < q; ++qi) {
        int x, k;
        cin >> x >> k;

        cout << make_jumps(x, k) << '\n';
    }
}
```

Bạn có thể tìm hiểu thêm về kỹ thuật này và các ứng dụng khác nhau của nó từ bài viết
hoặc bài báo gốc, cả hai đều được liên kết bên dưới.

### Ghi chú phụ

Bài báo gốc chỉ chứng minh rằng thuật toán hoạt động cho mảng một chiều – không phải cây.
Trong trường hợp cây, mô hình bước nhảy sẽ lan rộng ra các lá và hoạt động giống hệt
như đối với mảng.

### Đọc thêm

* [Eugene W. Myers,
  *An applicative random-access stack*,
  Information Processing Letters,
  Volume 17, Issue 5,
  1983.](https://www.sciencedirect.com/science/article/abs/pii/0020019083901060)
* [Codeforces, "Binary Lifting, No Memory Wasted" By Urbanowicz](https://codeforces.com/blog/entry/74847)
