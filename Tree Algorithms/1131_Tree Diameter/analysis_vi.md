# 1131 - Tree Diameter

Có nhiều cách tiếp cận bài toán này. Trong trang này,
chúng tôi sẽ trình bày hai cách.

## Cách tiếp cận thứ nhất

Cách tiếp cận thứ nhất dựa trên thực tế rằng khi
ta chọn gốc cho cây, đường kính sẽ có một đỉnh duy nhất
nằm "cao hơn" (tức là gần gốc hơn) so với mọi đỉnh khác.

![](95bf2a3f882b1fc0433559f862ce2c4dd93ff6a4f897df2820073396a8529798)

Nhận xét này dẫn đến một lời giải quy hoạch động, trong đó với mỗi đỉnh, ta xây dựng đường đi
dài nhất mà đỉnh hiện tại là đỉnh cao nhất. Đường đi dài nhất trong số các đường đi này chính là đường kính.

Tại mỗi đỉnh, ta sẽ lưu khoảng cách xa nhất từ đỉnh đó đến một lá nào đó trong cây con của nó.
Gọi khoảng cách này tại đỉnh $x$ là $\texttt{dist}(x)$.
Đường đi dài nhất mà đỉnh hiện tại là đỉnh cao nhất sẽ là giá trị lớn nhất
của $\texttt{dist}(a) + \texttt{dist}(b) + 2$, trong đó $a$ và $b$ là
hai đỉnh con phân biệt bất kỳ của đỉnh hiện tại.

Khi cài đặt thuật toán này, ta không thể kiểm tra tất cả các cặp đỉnh con
cho mỗi đỉnh. Thay vào đó, ta có thể lưu khoảng cách lớn nhất
đã thấy cho đến thời điểm hiện tại.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];
int dist[N];
int diameter = 0;

void dfs(int node, int parent) {
    int max_distance = 0;
    for (int child : g[node]) {
        if (child != parent) {
            dfs(child, node);
            diameter = max(diameter, max_distance + dist[child] + 1);
            max_distance = max(max_distance, dist[child] + 1);
        }
    }
    dist[node] = max_distance;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, 1);

    cout << diameter << '\n';
}
```

## Cách tiếp cận thứ hai

Cách tiếp cận thứ hai dựa trên một nhận xét không tầm thường:

Đường kính của một cây có thể được tìm bằng hai lượt DFS.
Đầu tiên, ta bắt đầu từ một đỉnh $a$ bất kỳ và tìm đỉnh xa nhất $b$ từ $a$.
Tương tự, ta tìm đỉnh xa nhất $c$ từ $b$.
Đường đi từ $b$ đến $c$ tương ứng với đường kính của cây.

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;

const int N = 200001;
vector<int> g[N];

// Trả về cặp
// {khoảng cách đến đỉnh xa nhất, nhãn của đỉnh xa nhất}
pair<int, int> dfs(int node, int parent) {
    auto result = pair{0, node};
    for (int child : g[node]) {
        if (child == parent) continue;
        auto ret = dfs(child, node);
        result = max(result, make_pair(ret.first + 1, ret.second));
    }
    return result;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int farthest = dfs(1, 1).second;
    cout << dfs(farthest, farthest).first << '\n';
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên)](http://cses.fi/book), Chương 14
