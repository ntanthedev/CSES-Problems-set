# 1628 - Meet in the Middle

Một thuật toán đơn giản duyệt qua tất cả các tập con sẽ chạy trong thời gian $O(2^n)$. Vì $2^{40}\approx1.1\cdot10^{12}$, lời giải này quá chậm. Chúng ta cần một giải pháp thông minh hơn, và như tên gọi đã gợi ý, kỹ thuật cần thiết được gọi là *meet in the middle* (gặp nhau ở giữa). Với meet in the middle, độ phức tạp thời gian có thể giảm xuống còn $O(n2^{n/2})$, hoặc thậm chí $O(2^{n/2})$.

Meet in the middle là một kỹ thuật khá trừu tượng có thể được áp dụng cho nhiều bài toán theo nhiều cách khác nhau. Tuy nhiên, ý tưởng chung là chia bài toán làm đôi, giải quyết từng nửa riêng biệt, sau đó hợp nhất các nửa lại để có được kết quả cuối cùng. Bài toán đếm số lượng tập con có tổng bằng một hằng số cho trước là một ví dụ kinh điển về nơi kỹ thuật này có thể được áp dụng.

Để sử dụng meet in the middle, chúng ta sẽ chia mảng làm đôi. Việc này có thể được thực hiện đơn giản bằng cách chọn $\lfloor { \frac n 2 } \rfloor$ số đầu tiên vào nửa đầu và phần còn lại vào nửa sau.

Sau đó, chúng ta sẽ tính toán và lưu trữ tổng của mỗi tập con cho từng nửa riêng biệt. Việc này được thực hiện trong thời gian $O(2^{n/2})$. Vấn đề còn lại là tìm cách hợp nhất thông tin các tập con để tính số lượng tập con trong mảng ban đầu có tổng bằng $x$.

Trước tiên, hãy sắp xếp cả hai mảng tổng tập con. Việc này tốn

$$O(2^{n/2}\log(2^{n/2}))=
O(2^{n/2}\cdot(n/2)\cdot\log 2)=
O(n2^{n/2})$$

thời gian. Bây giờ các mảng đã được sắp xếp, chúng ta sẽ duyệt mảng đầu tiên theo chiều tăng dần. Hóa ra ta có thể duy trì một con trỏ đến mảng thứ hai luôn giảm dần khi ta tiến lên trong mảng đầu tiên. Điều này là vì nếu phần tử trong mảng đầu tiên lớn hơn, thì phần tử tương ứng trong mảng thứ hai phải nhỏ hơn để vẫn có tổng bằng $x$. Do đó, thời gian để giải quyết phần này là tuyến tính theo độ dài của các mảng, tức là tốn $O(2^{n/2})$ thời gian.

Lưu ý rằng một số tổng tập con có thể xuất hiện nhiều lần trong các mảng. Điều này có nghĩa là, với mỗi phần tử trong mảng đầu tiên, có thể có nhiều hơn một phần tử tương ứng trong mảng thứ hai. Chúng ta sẽ tính đến điều này bằng cách xử lý tất cả các phần tử bằng nhau cùng một lúc.

Nhìn chung, thuật toán tốn $O(2^{n/2}+n2^{n/2})=O(n2^{n/2})$ thời gian. Độ phức tạp thời gian có thể được cải thiện xuống chỉ còn $O(2^{n/2})$ nếu chúng ta sử dụng bảng băm thay vì sắp xếp các mảng.

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// Trả về danh sách tất cả các tổng tập con, theo thứ tự đã sắp xếp.
vector<ll> subsets(vector<int> x) {
    int n = x.size();
    vector<ll> ret(1 << n);
    for (int m = 0; m < (1 << n); ++m) {
        for (int j = 0; j < n; ++j) {
            if ((1 << j) & m) ret[m] += x[j];
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    auto a = subsets(vector<int>(t.begin(), t.begin() + n / 2));
    auto b = subsets(vector<int>(t.begin() + n / 2, t.end()));

    ll r = 0;
    int m = a.size(), bi = b.size() - 1;

    for (int i = 0, j = 0; i < m; i = j) {
        while (j < m && a[i] == a[j]) ++j;
        while (bi >= 0 && a[i] + b[bi] > x) --bi;
        while (bi >= 0 && a[i] + b[bi] == x) {
            r += j - i;
            bi--;
        }
    }

    cout << r << '\n';
}
```
