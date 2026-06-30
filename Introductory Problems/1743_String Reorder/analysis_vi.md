# 1743 - Sắp xếp lại xâu

Đầu tiên ta hãy phân tích khi nào có thể xây dựng một xâu sao cho không có hai ký tự kề nhau nào giống nhau. Số lần xuất hiện tối đa của một ký tự đạt được khi nó xuất hiện ở mọi vị trí cách đều nhau, bao gồm cả vị trí đầu tiên và cuối cùng. Điều này dẫn đến bất đẳng thức $2k\le n+1$, trong đó $k$ là số lần xuất hiện của ký tự xuất hiện nhiều nhất và $n$ là độ dài xâu. Việc xây dựng là khả thi khi và chỉ khi bất đẳng thức trên được thỏa mãn.

Bây giờ, ta có thể xây dựng đáp án từng ký tự một. Để có xâu có thứ tự từ điển nhỏ nhất, tại mỗi bước ta sẽ chọn ký tự nhỏ nhất một cách tham lam. Điều kiện trên được dùng để kiểm tra xem xâu có thể được hoàn thành bằng cách chọn một ký tự cụ thể hay không.

```cpp
#include <iostream>
using namespace std;

int count[128];

int main() {
    string s;
    cin >> s;

    int n = s.size();

    for (auto c : s) {
        count[(int)c]++;
    }

    auto check = [&](int length) {
        for (int i = 'A'; i <= 'Z'; ++i) {
            if (count[i] * 2 > length + 1) {
                return false;
            }
        }
        return true;
    };

    if (!check(n)) {
        cout << -1 << '\n';
        return 0;
    }

    char prev = '$';
    for (int i = 1; i <= n; ++i) {
        for (int nxt = 'A'; nxt <= 'Z'; ++nxt) {
            if (!count[nxt]) continue;
            if (nxt == prev) continue;
            count[nxt]--;
            if (check(n - i)) {
                cout << (char)nxt;
                prev = nxt;
                break;
            }
            count[nxt]++;
        }
    }
    cout << '\n';
}
```
