# 3314 - Dãy núi

# Lời giải 1 (O(n log n))

Ta xử lý các ngọn núi theo thứ tự độ cao giảm dần và tính độ dài đường đi tối đa kết thúc tại mỗi ngọn núi.

Với mỗi ngọn núi, ta tìm núi cao hơn gần nhất về bên trái và bên phải. Vì các núi được xử lý theo thứ tự độ cao giảm dần, độ dài đường đi tối đa đã được tính cho cả hai núi này. Đường đi dài nhất đến núi hiện tại có thể được tạo bằng cách chọn đường đi dài nhất đến núi bên trái hoặc bên phải và thêm núi hiện tại vào đó.

Có thể có nhiều núi có cùng độ cao, điều này làm cho tình huống phức tạp hơn. Vì lý do này, ta duy trì một danh sách cập nhật bổ sung và áp dụng các cập nhật khi độ cao hiện tại khác với độ cao trước đó.

```cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> heights;
    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        heights.emplace_back(h, i);
    }
    sort(heights.rbegin(), heights.rend());

    map<int, int> counts;
    counts[0] = 0;
    counts[n + 1] = 0;

    int prev_height = 0;
    vector<pair<int, int>> updates;
    int result = 0;

    for (auto [height, pos] : heights) {
        if (height != prev_height) {
            for (auto [pos, count] : updates) {
                counts[pos] = count;
            }
            updates.clear();
            prev_height = height;
        }

        auto it = counts.upper_bound(pos);
        int next_pos = it->first;
        it--;
        int prev_pos = it->first;

        int new_count = max(counts[prev_pos], counts[next_pos]) + 1;
        updates.emplace_back(pos, new_count);
        result = max(result, new_count);
    }

    cout << result << "\n";
}
```

# Lời giải 2 (O(n))

Cũng có thể giải bài toán trong thời gian tuyến tính bằng cách dùng phương pháp khác để xử lý các ngọn núi.

Đầu tiên, ta tìm núi cao hơn gần nhất về bên trái và bên phải cho mỗi ngọn núi, việc này có thể làm trong thời gian tuyến tính bằng cách dùng stack. Sau đó ta tạo một đồ thị xác định thứ tự xử lý các ngọn núi.

Tiếp theo, ta xử lý đồ thị bằng cách sắp xếp tô pô (topological sorting) và tính độ dài đường đi tối đa cho mỗi ngọn núi, áp dụng ý tưởng tương tự như lời giải trước.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1000000001;

int main() {
    int n;
    cin >> n;

    vector<int> heights(n + 2);
    heights[0] = INF;
    heights[n + 1] = INF;
    for (int i = 1; i <= n; i++) {
        cin >> heights[i];
    }

    vector<vector<int>> after(n + 2);

    vector<int> left_stack;
    left_stack.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (heights[i] >= heights[left_stack.back()]) {
            left_stack.pop_back();
        }
        after[left_stack.back()].push_back(i);
        left_stack.push_back(i);
    }

    vector<int> right_stack;
    right_stack.push_back(n + 1);
    for (int i = n; i >= 1; i--) {
        while (heights[i] >= heights[right_stack.back()]) {
            right_stack.pop_back();
        }
        after[right_stack.back()].push_back(i);
        right_stack.push_back(i);
    }

    vector<int> count(n + 2);
    vector<int> result(n + 2);

    vector<int> queue;
    queue.push_back(0);
    queue.push_back(n + 1);

    int answer = 0;
    for (int i = 0; i < queue.size(); i++) {
        int pos = queue[i];
        for (auto next_pos : after[pos]) {
            result[next_pos] = max(result[next_pos], result[pos] + 1);
            answer = max(answer, result[next_pos]);
            count[next_pos]++;
            if (count[next_pos] == 2) {
                queue.push_back(next_pos);
            }
        }
    }
    cout << answer << "\n";
}
```
