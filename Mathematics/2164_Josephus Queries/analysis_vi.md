# 2164 - Truy vấn Josephus

Ta có thể chia quá trình loại trẻ thành các vòng, trong đó ta đi qua các đứa trẻ
theo thứ tự tăng dần và loại bỏ mỗi đứa thứ hai. Ví dụ, khi $n=7$, các vòng như
sau:

* Vòng $1$: $[1,\underline{2},3,\underline{4},5,\underline{6},7]$
* Vòng $2$: $[\underline{1},3,\underline{5},7]$
* Vòng $3$: $[\underline{3},7]$
* Vòng $4$: $[\underline{7}]$

Để tìm đứa trẻ thứ $k$ bị loại một cách hiệu quả, ta mô phỏng các vòng bằng một
hàm đệ quy mà mỗi lần gọi tương ứng với một vòng.

Gọi $\textrm{child}(n,k,p)$ là đứa trẻ thứ $k$ bị loại khi có $n$ đứa trẻ và
tính chẵn lẻ của đứa trẻ đầu tiên bị loại là $p$ ($0$ nghĩa là ta loại đứa trẻ
$2$ trước, và $1$ nghĩa là ta loại đứa trẻ $1$ trước).

Số đứa trẻ bị loại trong vòng đầu tiên là $r = \lfloor n + p \rfloor / 2$. Nếu
$k \le r$, ta loại đứa trẻ thứ $k$ trong vòng đầu tiên và trả về số hiệu của đứa
trẻ đó là $2k - p$.

Ngược lại, ta gọi hàm đệ quy: còn $n-r$ đứa trẻ và ta cần tìm đứa trẻ thứ
$(k-r)$ bị loại. Ở đây $u$ là tính chẵn lẻ mới: nếu $n$ chẵn, tính chẵn lẻ giữ
nguyên; nếu $n$ lẻ, tính chẵn lẻ thay đổi. Vì cách đánh số thay đổi trong bài
toán con, ta phải chuyển đổi nó sau lời gọi đệ quy.

Vì ta loại một nửa số trẻ trong mỗi vòng, số vòng là $O(\log n)$ và hàm chạy
trong thời gian $O(\log n)$.

```cpp
#include <iostream>
using namespace std;

int child(int n, int k, int p) {
    int r = (n + p) / 2;
    if (k <= r) return k * 2 - p;
    int u = n % 2 == 0 ? p : 1 - p;
    return child(n - r, k - r, u) * 2 - 1 + p;
}

int main() {
    int q;
    cin >> q;

    for (int qi = 1; qi <= q; qi++) {
        int n, k;
        cin >> n >> k;
        cout << child(n, k, 0) << "\n";
    }
}
```

## Tài liệu tham khảo

* [Josephus problem (Wikipedia)](https://en.wikipedia.org/wiki/Josephus_problem)
