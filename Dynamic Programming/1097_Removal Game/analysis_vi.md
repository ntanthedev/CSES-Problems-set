# 1097 - Removal Game

Trò chơi này là một dạng trò chơi có tổng bằng không, vì bất kỳ số nào được
một người chọn cũng tương đương với một khoản thua tương ứng cho người kia.
Để làm cho trò chơi hoàn toàn đối xứng, ta định nghĩa điểm số của người chơi
thực hiện nước đi tiếp theo là tổng các phần tử họ chọn trừ đi tổng các phần
tử người kia chọn.

Trong biến thể này, không cần phải theo dõi điểm số của từng người chơi riêng
biệt. Người chơi hiện tại luôn cố gắng tối đa hóa điểm số, và khi chuyển sang
người chơi tiếp theo, tổng điểm số bị đảo dấu, và người kia cũng sẽ cố gắng
tối đa hóa nó.

Để có chiến lược tối ưu, người chơi hiện tại nên chọn nước đi tối đa hóa điểm
số có thể đạt được khi kết thúc trò chơi bất kể nước đi của người kia. Cách
tiếp cận này thường được gọi là minimax. Quy hoạch động là một cách tự nhiên
để cài đặt nó, vì điểm số trong trường hợp tệ nhất mà mỗi nước đi dẫn đến có
thể được tính trước dưới dạng các bài toán con nhỏ hơn.

Định nghĩa hàm $\mathrm{score}(l, r)$ là điểm số tối đa mà người chơi đầu tiên
có thể đạt được, khi trò chơi được chơi trên danh sách $x\_l, x\_{l+1}, \dots,
x\_r$.

Sau một nước đi, trò chơi thu về một trò chơi tương đương với việc bỏ đi số
bên trái hoặc bên phải, và có một chênh lệch điểm số nhất định. Điểm số của
trò chơi nhỏ hơn bị đảo dấu do vai trò bị đảo ngược.

$$\mathrm{score}(l, r) = \max(x\_l - \mathrm{score}(l+1, r), x\_r -
\mathrm{score}(l, r-1))$$

Trong trường hợp cơ sở, khi $l = r$, người chơi đầu tiên phải chọn số duy nhất.

$$\mathrm{score}(l, l) = x\_l$$

Một thứ tự phù hợp để tính các điểm số này bằng quy hoạch động là theo chiều
dài tăng dần, hay $r - l + 1$. Một mảng quy hoạch động một chiều là đủ vì
công thức đệ quy chỉ tham chiếu đến các bài toán con có độ dài trước đó.

Cuối cùng, ta phải chuyển đổi điểm số thu được về dạng yêu cầu của đề bài:
điểm số của người chơi đầu tiên. Gọi $a, b$ lần lượt là điểm số của người
chơi thứ nhất và thứ hai. Kết quả ta thu được là $r = a - b$. Ta cũng biết
tổng tất cả các số trong danh sách, $\mathrm{sum} = a + b$. Cộng hai giá trị
này lại, ta được

$$r + \mathrm{sum} = (a - b) + (a + b) = 2a.$$

Sau đó chia cho hai để có đáp án cần tìm.

Độ phức tạp thời gian của lời giải này là $O(n^2)$ vì mỗi giá trị của hàm
$\mathrm{score}$ được tính trong thời gian hằng số.

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const int N = 5000;
int x[N];
ll score[N];

int main() {
    int n;
    cin >> n;

    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        score[i] = x[i];
        sum += x[i];
    }

    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
            int r = l + len - 1;
            score[l] = max(x[l] - score[l + 1], x[r] - score[l]);
        }
    }

    cout << (sum + score[0]) / 2 << endl;
}
```

## Tài liệu tham khảo

* [Minimax (Wikipedia)](https://en.wikipedia.org/wiki/Minimax)
