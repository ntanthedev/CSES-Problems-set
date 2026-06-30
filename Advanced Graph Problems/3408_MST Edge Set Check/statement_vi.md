# 3408 - Kiểm Tra Tập Cạnh MST

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đồ thị vô hướng có trọng số và các tập cạnh, hãy xác định với mỗi tập xem các cạnh có thể được bao gồm trong một cây khung nhỏ nhất hay không.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $q$: số lượng đỉnh, cạnh và tập cạnh. Các đỉnh được đánh số $1,2,\dots,n$.

$m$ dòng tiếp theo mô tả các cạnh. Mỗi dòng chứa ba số nguyên $a$, $b$, $w$: có một cạnh giữa hai đỉnh $a$ và $b$ với trọng số $w$. Các cạnh được đánh số $1,2,\dots,m$ theo thứ tự nhập vào.

$2q$ dòng tiếp theo mô tả các tập cạnh. Với mỗi tập, dòng đầu tiên chứa kích thước của nó và dòng thứ hai chứa các cạnh của nó. Tổng số cạnh trong tất cả các tập không vượt quá $m$.

Bạn có thể giả sử đồ thị liên thông, đơn và mỗi cạnh xuất hiện nhiều nhất một lần trong đồ thị.

# Kết quả

Với mỗi tập cạnh, in ra `YES` nếu các cạnh có thể được bao gồm trong cây khung nhỏ nhất và `NO` nếu không thể.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m, q \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le w \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 6 4
1 2 4
1 3 2
2 4 2
3 4 1
3 5 3
4 5 3
3
2 3 4
1
1
2
2 6
2
5 6
```

Kết quả:

```cpp
YES
NO
YES
NO
```
