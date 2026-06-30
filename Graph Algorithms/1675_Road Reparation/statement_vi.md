# 1675 - Sửa chữa đường giao thông

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 128 MB

Có $n$ thành phố và $m$ con đường giữa chúng. Thật không may, tình trạng của các con đường quá tồi tệ đến nỗi chúng không thể sử dụng được. Nhiệm vụ của bạn là sửa chữa một số con đường để có đường đi giữa mọi cặp thành phố.

Với mỗi con đường, bạn biết chi phí sửa chữa của nó, và bạn cần tìm một phương án có tổng chi phí nhỏ nhất có thể.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và số lượng con đường. Các thành phố được đánh số $1,2,\dots,n$.

Sau đó là $m$ dòng mô tả các con đường. Mỗi dòng chứa ba số nguyên $a$, $b$ và $c$: có một con đường giữa thành phố $a$ và $b$, và chi phí sửa chữa của nó là $c$. Tất cả các con đường đều là đường hai chiều.

Mỗi con đường nối giữa hai thành phố khác nhau, và có nhiều nhất một con đường giữa hai thành phố bất kỳ.

# Kết quả

In ra một số nguyên: tổng chi phí sửa chữa nhỏ nhất. Tuy nhiên, nếu không có phương án nào, in ra "IMPOSSIBLE".

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le c \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 6
1 2 3
2 3 5
2 4 2
3 4 8
5 1 7
5 4 4
```

Kết quả:

```cpp
14
```
