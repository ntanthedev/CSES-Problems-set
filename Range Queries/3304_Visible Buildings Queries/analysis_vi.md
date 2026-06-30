# 3304 - Visible Buildings Queries (Truy vấn Tòa nhà Có thể Nhìn thấy)

Đầu tiên chúng ta tìm chỉ số của tòa nhà cao hơn tiếp theo cho mỗi tòa nhà (hoặc $\infty$ nếu không có tòa nhà nào như vậy). Việc này được thực hiện trong thời gian tuyến tính bằng cách sử dụng một ngăn xếp.

Sau đó, ta tạo một mảng jump, với mỗi tòa nhà, cho biết tòa nhà cao hơn tiếp theo ở bên phải sau $x$ bước, trong đó $x$ là lũy thừa của hai. Vì có $O(\log n)$ lũy thừa của hai có thể, việc tạo mảng này tốn $O(n \log n)$ thời gian.

Cuối cùng, ta có thể trả lời bất kỳ truy vấn nào trong thời gian $O(\log n)$ bằng cách sử dụng mảng jump.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int N = 17;
const int INF = 1000000001;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> heights(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> heights[i];
    }
    heights[n + 1] = INF;

    vector<vector<int>> jump(N, vector<int>(n + 2));
    jump[0][n + 1] = n + 1;

    vector<int> stack;
    stack.push_back(n + 1);
    for (int i = n; i >= 1; i--) {
        while (heights[stack.back()] <= heights[i]) {
            stack.pop_back();
        }
        jump[0][i] = stack.back();
        stack.push_back(i);
    }

    for (int k = 1; k < N; k++) {
        for (int i = 1; i <= n + 1; i++) {
            jump[k][i] = jump[k - 1][jump[k - 1][i]];
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        int pos = a;
        int answer = 1;
        for (int k = N - 1; k >= 0; k--) {
            if (jump[k][pos] <= b) {
                answer += 1 << k;
                pos = jump[k][pos];
            }
        }
        cout << answer << "\n";
    }
}
```
