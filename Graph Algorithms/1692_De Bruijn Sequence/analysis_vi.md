# 1692 - Dãy De Bruijn

Hóa ra ta luôn có thể tạo ra một xâu chứa mỗi xâu con phân biệt có độ dài $n$ đúng một lần. Độ dài của một xâu như vậy là $2^n + n - 1$.

Bài toán này có thể được giải bằng cách xây dựng một đồ thị có hướng trong đó mỗi đỉnh tương ứng với một xâu con có độ dài $n-1$ và mỗi cạnh chứa ký tự tiếp theo cần được thêm vào xâu. Một đường đi Euler trong đồ thị này tương ứng với một dãy De Bruijn tối ưu.

Tuy nhiên, có một cách dễ hơn để xây dựng xâu. Đoạn mã sau đây xây dựng xâu bằng cách quay lui đệ quy. Mỗi xâu con có độ dài $n$ được lưu dưới dạng mặt nạ bit của $n$ bit. Cách tiếp cận này chạy rất nhanh với $1 \le n \le 15$.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> result;
vector<int> seen;

void search(int pos, int part, int n) {
    if (pos == (1 << n) + n - 1) {
        for (int i = 0; i < pos; i++) {
            cout << result[i];
        }
        cout << "\n";
        exit(0);
    }

    part = (part << 1) & ((1 << n) - 1);

    for (int i = 0; i < 2; i++) {
        if (!seen[part]) {
            seen[part] = true;
            result[pos] = i;
            search(pos + 1, part, n);
            seen[part] = false;
        }
        part++;
    }
}

int main() {
    int n;
    cin >> n;

    seen.resize(1 << n);
    seen[0] = true;

    result.resize((1 << n) + n - 1);
    search(n, 0, n);
}
```

## Tài liệu tham khảo

* [CPHB (Sổ tay Lập trình viên)](https://cses.fi/book), Chương 19
