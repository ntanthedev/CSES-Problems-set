# 3225 - Mảng hậu tố nghịch đảo

Ta có thể sử dụng một giải thuật tham lam để xây dựng một xâu tương ứng với mảng hậu tố.

Ta duyệt qua mảng hậu tố từ trái sang phải.
Gọi $\textrm{sa}[i]$ là giá trị thứ $i$ của mảng hậu tố.
Với $i=1,2,\dots,n$, ta gán ký tự nhỏ nhất có thể cho vị trí $\textrm{sa}[i]$ trong xâu.

Giả sử ta muốn gán một ký tự cho vị trí $\textrm{sa}[i]$
và ta đã gán ký tự $x$ cho vị trí $\textrm{sa}[i-1]$.
Nếu hậu tố bắt đầu tại vị trí $\textrm{sa}[i-1]+1$ nhỏ hơn
hậu tố bắt đầu tại vị trí $\textrm{sa}[i]+1$,
ta gán ký tự $x$ cho vị trí $\textrm{sa}[i]$.
Ngược lại, ta gán ký tự $x+1$ cho vị trí $\textrm{sa}[i]$.

Nếu ta dùng hết ký tự, thì không thể xây dựng được xâu.

Chú ý rằng giải thuật này tạo ra xâu nhỏ nhất theo thứ tự từ điển
tương ứng với mảng hậu tố.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> suffix_array(n + 1);
    vector<int> order(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> suffix_array[i];
        order[suffix_array[i]] = i;
    }

    vector<char> result(n + 1);
    result[suffix_array[1]] = 'a';
    char current_char = 'a';
    for (int i = 2; i <= n; i++) {
        if (order[suffix_array[i - 1] + 1] > order[suffix_array[i] + 1]) {
            current_char++;
        }
        if (current_char > 'z') {
            cout << "-1\n";
            return 0;
        }
        result[suffix_array[i]] = current_char;
    }

    for (int i = 1; i <= n; i++) {
        cout << result[i];
    }
    cout << "\n";
}
```
