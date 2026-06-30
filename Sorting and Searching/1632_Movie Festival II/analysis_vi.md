# 1632 - Liên Hoan Phim II

Chúng ta đã giải quyết một trường hợp đặc biệt của bài toán khi $k=1$, tức là câu lạc bộ phim chỉ có một thành viên. Trong trường hợp đó, ta có thể sắp xếp các bộ phim theo thời gian kết thúc, duyệt qua các bộ phim và luôn chọn bộ phim tiếp theo có thể xem được. Hóa ra ta có thể sử dụng ý tưởng tương tự cho bài toán này.

Chúng ta sử dụng một multiset `times` lưu thời gian sớm nhất mà mỗi thành viên câu lạc bộ có thể bắt đầu xem bộ phim tiếp theo. Ban đầu mỗi thời gian là $0$. Sau đó, với mỗi bộ phim, ta tìm một thành viên có thể xem bộ phim đó. Nếu có nhiều lựa chọn, ta chọn thành viên vừa kết thúc bộ phim trước đó gần nhất. Nếu không có ai có thể xem bộ phim, ta bỏ qua bộ phim đó.

Số thao tác cho mỗi bộ phim là cố định $O(\log n)$, do đó thuật toán chạy trong thời gian $O(n \log n)$.

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> events;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        events.emplace_back(b, a);
    }
    sort(events.begin(), events.end());

    multiset<int> times;
    for (int i = 1; i <= k; i++) {
        times.insert(0);
    }

    int answer = 0;
    for (auto [b, a] : events) {
        auto it = times.upper_bound(a);
        if (it == times.begin()) continue;
        answer++;
        it--;
        times.erase(it);
        times.insert(b);
    }

    cout << answer << "\n";
}
```
