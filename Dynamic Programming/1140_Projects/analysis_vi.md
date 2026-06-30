# 1140 - Projects

Gọi $\mathrm{money}(i)$ là số tiền tối đa có thể thu được khi tham gia dự án
$i$ và có thể tham gia một số dự án khác trước nó. Ta có công thức truy hồi
sau:

$$\mathrm{money}(i) = \max\_{j \le n,\ b\_j < a\_i} \mathrm{money}(j) + p\_i$$

Vì $n$ có thể lớn, ta cần một cách hiệu quả để tìm dự án $j$ có
$\mathrm{money}(j)$ lớn nhất kết thúc trước khi dự án $i$ bắt đầu.
Sắp xếp các dự án theo ngày bắt đầu hoặc ngày kết thúc là chưa đủ,
vì giá trị $\mathrm{money}$ cần được tính dựa trên ngày bắt đầu của một dự án,
nhưng giá trị đó chỉ có sẵn cho các dự án khác sau ngày kết thúc.

Ta có thể sử dụng phương pháp quét đường thẳng (sweep line), trong đó mỗi dự
án được chia thành hai sự kiện: một sự kiện tại ngày bắt đầu và một sự kiện
tại ngày kết thúc. Giá trị $\mathrm{money}(i)$ được tính tại thời điểm $a\_i$
dựa trên giá trị lớn nhất trong số các dự án đã kết thúc. Giá trị lớn nhất
hiện tại được cập nhật khi dự án kết thúc tại thời điểm $b\_i$.

Để đảm bảo các dự án kết thúc vào một ngày nhất định không ảnh hưởng đến các
dự án bắt đầu cùng ngày, các sự kiện bắt đầu được sắp xếp trước các sự kiện
kết thúc nếu chúng xảy ra cùng ngày.

Độ phức tạp thời gian của lời giải này là $O(n \log n)$ vì thao tác sắp xếp
được thực hiện.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

struct Event {
    int time, project;
    bool is_end;
    bool operator<(Event other) const {
        if (time == other.time) return is_end < other.is_end;
        return time < other.time;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    vector<ll> money(n);
    vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b >> p[i];
        events.push_back({a, i, false});
        events.push_back({b, i, true});
        money[i] = 0;
    }

    sort(events.begin(), events.end());

    ll result = 0;
    for (auto [time, project, is_end] : events) {
        if (is_end) {
            result = max(result, money[project]);
        } else {
            money[project] = result + p[project];
        }
    }

    cout << result << endl;
}
```

## Tài liệu tham khảo

* [CPHB (Competitive Programmer's Handbook)](https://cses.fi/book), Chương 30
