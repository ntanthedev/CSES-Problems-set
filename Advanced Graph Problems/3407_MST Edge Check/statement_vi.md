# 3407 - Kiểm Tra Cạnh MST

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đồ thị vô hướng có trọng số, hãy xác định với mỗi cạnh xem nó có thể được bao gồm trong một cây khung nhỏ nhất hay không.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh và cạnh. Các đỉnh được đánh số $1,2,\dots,n$.

$m$ dòng tiếp theo mô tả các cạnh. Mỗi dòng chứa ba số nguyên $a$, $b$, $w$: có một cạnh giữa hai đỉnh $a$ và $b$ với trọng số $w$.

Bạn có thể giả sử đồ thị liên thông, đơn và mỗi cạnh xuất hiện nhiều nhất một lần trong đồ thị.

# Kết quả

Với mỗi cạnh theo thứ tự nhập vào, in ra `YES` nếu nó có thể được bao gồm trong cây khung nhỏ nhất và `NO` nếu không thể.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le w \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 6
1 2 4
1 3 2
2 4 2
3 4 1
3 5 3
4 5 3
```

Kết quả:

```cpp
NO
YES
YES
YES
YES
YES
```
