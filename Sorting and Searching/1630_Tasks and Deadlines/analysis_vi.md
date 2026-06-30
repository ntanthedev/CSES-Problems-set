# 1630 - Công Việc và Hạn Chót

Chúng ta sắp xếp các công việc theo thời lượng và xử lý chúng theo thứ tự đó. Điều đáng ngạc nhiên là hạn chót của các công việc không hề ảnh hưởng đến việc chọn thứ tự.

Để thấy tại sao thuật toán hoạt động, xét hai công việc $t\_1 = (a\_1,d\_1)$ và $t\_2 = (a\_2,d\_2)$, trong đó $a\_1$ và $a\_2$ là thời lượng còn $d\_1$ và $d\_2$ là hạn chót. Giả sử ta xử lý $t\_2$ ngay sau $t\_1$ và $a\_1 > a\_2$. Nếu ta bắt đầu xử lý $t\_1$ tại thời điểm $x$, tổng phần thưởng cho các công việc sẽ là
$$d\_1-(x+a\_1) + d\_2-(x+a\_1+a\_2) = d\_1+d\_2-2x-2 a\_1 - a\_2.$$
Sau đó, nếu ta đổi thứ tự các công việc và xử lý $t\_2$ trước rồi $t\_1$, tổng phần thưởng sẽ là
$$d\_2-(x+a\_2) + d\_1-(x+a\_1+a\_2) = d\_1+d\_2-2x-a\_1 - 2 a\_2.$$
Vì $a\_1 > a\_2$, ta nhận được nhiều phần thưởng hơn sau khi đổi thứ tự. Do đó, bất cứ khi nào ta có hai công việc liên tiếp và công việc đầu tiên tốn nhiều thời gian hơn công việc thứ hai, ta nên đổi chỗ chúng. Vì lý do này, phương án tối ưu là xử lý các công việc được sắp xếp theo thời lượng.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> tasks;
    for (int i = 1; i <= n; i++) {
        int duration, deadline;
        cin >> duration >> deadline;
        tasks.emplace_back(duration, deadline);
    }
    sort(tasks.begin(), tasks.end());

    ll time = 0;
    ll reward = 0;
    for (auto [duration, deadline] : tasks) {
        time += duration;
        reward += deadline - time;
    }
    cout << reward << "\n";
}
```
