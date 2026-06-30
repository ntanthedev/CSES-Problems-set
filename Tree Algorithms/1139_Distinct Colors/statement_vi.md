# 1139 - Màu sắc phân biệt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một cây có gốc gồm $n$ đỉnh. Các đỉnh được đánh số $1,2,\ldots,n$, và đỉnh $1$ là gốc. Mỗi đỉnh có một màu sắc.

Nhiệm vụ của bạn là xác định cho mỗi đỉnh số lượng màu sắc phân biệt trong cây con của đỉnh đó.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng đỉnh. Các đỉnh được đánh số $1,2,\ldots,n$.

Dòng tiếp theo gồm $n$ số nguyên $c\_1,c\_2,\ldots,c\_n$: màu sắc của mỗi đỉnh.

Sau đó là $n-1$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh nối giữa đỉnh $a$ và đỉnh $b$.

# Kết quả

In ra $n$ số nguyên: với mỗi đỉnh $1,2,\ldots,n$, số lượng màu sắc phân biệt.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le c\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5
2 3 2 2 1
1 2
1 3
3 4
3 5
```

Kết quả:

```cpp
3 1 2 1 1
```
