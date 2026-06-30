# 1133 - Tree Distances II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một cây gồm $n$ đỉnh.

Nhiệm vụ của bạn là xác định với mỗi đỉnh tổng khoảng cách từ đỉnh đó đến tất cả các đỉnh khác.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng đỉnh. Các đỉnh được đánh số $1,2,\ldots,n$.

Sau đó là $n-1$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh nối giữa đỉnh $a$ và $b$.

# Kết quả

In ra $n$ số nguyên: với mỗi đỉnh $1,2,\ldots,n$, tổng các khoảng cách.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 2
1 3
3 4
3 5
```

Kết quả:

```cpp
6 9 5 8 8
```
