# 1666 - Building Roads

Trong bài toán này, chúng ta được yêu cầu thêm các cạnh vào đồ thị sao cho số
thành phần liên thông trong đồ thị bằng một.

Chúng ta bắt đầu bằng cách tìm các thành phần liên thông trong tình huống ban đầu.
Điều này có thể được thực hiện bằng cách duyệt từng thành phố một. Nếu thành phố hiện tại $x$
chưa được gán vào một thành phần nào, chúng ta tạo một thành phần mới $c$
và chạy tìm kiếm theo chiều sâu từ $x$, gán mọi thành phố gặp được vào
thành phần $c$.

Xây một con đường từ một thành phần đến thành phần khác sẽ hợp nhất các thành phần này và
giảm số lượng thành phần đi một. Do đó nếu có $p$ thành phần,
chúng ta cần xây $p-1$ con đường.

Lưu ý rằng từ góc độ hợp nhất các thành phần, không quan trọng chúng ta chọn
thành phố chính xác nào từ mỗi thành phần. Chúng ta quyết định luôn chọn
thành phố có chỉ số nhỏ nhất và lưu các chỉ số vào vector
`roots`.

Tuy nhiên, có nhiều cách để xây dựng các con đường. Coi mỗi thành phần như một đỉnh, bất kỳ
cây nào cũng đều hợp lệ. Chúng ta hợp nhất các thành phần bằng cách xây các con đường
giữa mỗi cặp thành phố liên tiếp trong vector `roots`.

Việc tìm các thành phần liên thông tốn $O(n + m)$ thời gian. Thêm các con đường mới tốn
$O(n)$ thời gian vì có tối đa $n$ thành phần ban đầu.

Do đó tổng độ phức tạp thời gian là $O(n + m)$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 100001;
vector<int> graph[N];
int component[N];

void mark_component(int x, int id) {
    if (component[x]) return;
    component[x] = id;
    for (int y : graph[x]) {
        mark_component(y, id);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int count = 0;
    vector<int> roots;
    for (int i = 1; i <= n; ++i) {
        if (component[i] == 0) {
            mark_component(i, ++count);
            roots.push_back(i);
        }
    }

    cout << count - 1 << '\n';
    for (int i = 0; i + 1 < roots.size(); ++i) {
        cout << roots[i] << ' ' << roots[i + 1] << '\n';
    }
}
```
