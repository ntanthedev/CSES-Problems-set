# 1702 - Duyệt Cây

Chúng ta sẽ tạo một hàm đệ quy để duyệt từng cây con và đưa ra thứ tự
hậu thứ tự của cây.

Chúng ta sẽ duy trì hai đoạn trong suốt quá trình tìm kiếm: đoạn của cây con
hiện tại trong mảng tiền thứ tự và đoạn của cây con hiện tại trong mảng
trung thứ tự. Từ thông tin này, chúng ta có thể suy ra các đoạn của cây con
của các nút con. Chúng ta biết rằng đỉnh gốc của cây con là đỉnh đầu tiên
trong mảng tiền thứ tự. Đỉnh gốc cũng chia mảng trung thứ tự của cây con thành hai
phần: một phần cho mỗi nút con. Do đó, nếu chúng ta biết vị trí của đỉnh gốc trong
mảng trung thứ tự, chúng ta có thể tính được kích thước của các cây con. Thông tin
này là đủ để cập nhật các đoạn.

Một chi tiết cài đặt đáng chú ý là chúng ta cần mảng `inorder_pos`
để tìm vị trí của đỉnh gốc trong mảng trung thứ tự một cách hiệu quả. Lời
giải có độ phức tạp thời gian là $O(n)$.

```cpp
#include <iostream>
using namespace std;

const int N = 100001;
int preorder[N], inorder[N];
int inorder_pos[N];

// [l_p, r_p] là đoạn của cây con hiện tại trong mảng `preorder`.
// [l_i, r_i] là đoạn của cây con hiện tại trong mảng `inorder`.
void postorder(int l_p, int r_p, int l_i, int r_i) {
    if (r_p < l_p) return;
    int root = preorder[l_p];
    int root_pos = inorder_pos[root];
    int left_sz = root_pos - l_i;
    postorder(l_p + 1, l_p + left_sz, l_i, root_pos - 1);
    postorder(l_p + left_sz + 1, r_p, root_pos + 1, r_i);
    cout << root << ' ';
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> preorder[i];
    }

    for (int i = 1; i <= n; ++i) {
        cin >> inorder[i];
        inorder_pos[inorder[i]] = i;
    }

    postorder(1, n, 1, n);
    cout << '\n';
}
```
