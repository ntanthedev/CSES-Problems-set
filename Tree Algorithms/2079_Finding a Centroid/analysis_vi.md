# 2079 - Tìm tâm

## Cách tiếp cận thứ nhất

Bài toán trở nên dễ giải hơn khi ta chọn gốc của cây một cách tùy ý. Sau
đó, ta tính kích thước cây con của mỗi đỉnh và kích thước cây con lớn nhất
trong số các đỉnh con của mỗi đỉnh.

Các mảng `sz` và `max_child` lưu kích thước
cây con của mỗi đỉnh và kích thước cây con lớn nhất trong số các đỉnh con của mỗi
đỉnh.

Khi ta loại bỏ một đỉnh khỏi cây, một số thành phần riêng biệt sẽ
còn lại. Trong suốt phân tích này, ta sẽ gọi thành phần tương ứng với
đỉnh cha của một đỉnh là *thành phần của đỉnh cha* của đỉnh đó.

Lưu ý rằng thành phần của đỉnh cha có thể là thành phần lớn nhất trong số các thành phần còn lại.
Mảng `max_child` không tính đến trường hợp này và do đó, nó cần
được kiểm tra riêng. Kích thước của thành phần của đỉnh cha bằng
$n-$`sz`$[i]$ với mọi đỉnh $i$ vì mỗi trong số $n$ đỉnh của cây là một phần
của cây con của $i$ hoặc thành phần của đỉnh cha.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int sz[N], max_child[N];

void dfs(int node, int parent) {
    sz[node] = 1;
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs(child, node);
        sz[node] += sz[child];
        max_child[node] = max(max_child[node], sz[child]);
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    for (int i = 1; i <= n; ++i) {
        if (max(max_child[i], n - sz[i]) <= n / 2) {
            cout << i << '\n';
            break;
        }
    }
}
```

## Cách tiếp cận thứ hai

Có một cách tiếp cận đệ quy cho bài toán này, trong đó ta theo dõi
kích thước của thành phần của đỉnh cha khi ta duyệt cây.

Cách tiếp cận này hữu ích trong trường hợp ta không biết chính xác tập hợp các đỉnh
mà cây bao gồm, như đôi khi xảy ra khi xây dựng
phân tích tâm (centroid decomposition) của cây.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int sz[N], max_child[N];
int n;

void dfs(int node, int parent) {
    sz[node] = 1;
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs(child, node);
        sz[node] += sz[child];
        max_child[node] = max(max_child[node], sz[child]);
    }
}

int centroid(int node, int parent, int above) {
    if (max(above, max_child[node]) <= n / 2) {
        return node;
    }
    for (int child : g[node]) {
        if (child == parent) continue;
        int ans = centroid(child, node, above + sz[node] - sz[child]);
        if (ans != -1) return ans;
    }
    return -1;
}

int main() {
    cin >> n;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    cout << centroid(1, -1, 0) << '\n';
}
```

## Cách tiếp cận thứ ba

Lời giải trước đó có thể được cải thiện hơn nữa. Hóa ra một cách tiếp cận tham lam
hoạt động.

Đầu tiên, ta chọn gốc cho cây. Sau đó, bắt đầu từ gốc, ta đệ quy di chuyển đến một
đỉnh con có kích thước cây con lớn hơn $\left \lfloor{\frac n 2}\right \rfloor$.
Khi ta đến một đỉnh không có đỉnh con nào như vậy, đỉnh đó là tâm của
cây.

### Chứng minh cho thuật toán

Vì kích thước của cây con hiện tại giảm sau mỗi lần di chuyển, quá trình duyệt sẽ
cuối cùng đến một đỉnh không có đỉnh con nào có kích thước cây con lớn hơn $\left
\lfloor{\frac n 2}\right \rfloor$. Ta chỉ cần chứng minh rằng đỉnh được tìm thấy là,
thực sự, một tâm của cây.

Ta biết rằng không có đỉnh con nào của đỉnh được chọn có kích thước cây con quá
lớn, điều này có nghĩa là trường hợp duy nhất mà đỉnh được chọn không phải là tâm
là khi kích thước của thành phần đỉnh cha quá lớn.

![](6dc9d2874f0ad14006e9b43a6f0bfefe30d702bc57b82cfd39e932b3d2c20917)

Nếu quá trình duyệt chỉ gồm một đỉnh, thì gốc là đỉnh tâm vì
nó không có đỉnh cha. Ngược lại, hãy phân tích bước cuối cùng của quá trình
tìm kiếm, di chuyển từ đỉnh trước đó đến đỉnh cuối cùng (trong hình từ $2$
đến $4$).

Gọi kích thước cây con của đỉnh cuối cùng ($4$ trong hình) là $S$. Khi đó,
kích thước của thành phần đỉnh cha có kích thước là $n-S$. Theo định nghĩa, ta biết rằng
$S>\left \lfloor{\frac n 2}\right \rfloor$. Từ các thông tin này, ta
có thể suy ra rằng

$$S>\left \lfloor{\frac n 2}\right \rfloor \iff n-S < n -
\left \lfloor{\frac n 2}\right \rfloor
\implies
n-S\le\left \lfloor{\frac n 2}\right \rfloor.\ \square$$

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int sz[N];
int n;

void dfs(int node, int parent) {
    sz[node] = 1;
    for (int child : g[node]) {
        if (child == parent) continue;
        dfs(child, node);
        sz[node] += sz[child];
    }
}

int centroid(int node, int parent) {
    for (int child : g[node]) {
        if (child != parent && sz[child] > n / 2) {
            return centroid(child, node);
        }
    }
    return node;
}

int main() {
    cin >> n;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    cout << centroid(1, -1) << '\n';
}
```
