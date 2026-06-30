# 1138 - Truy vấn đường đi

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một cây có gốc gồm $n$ đỉnh. Các đỉnh được đánh số $1,2,\ldots,n$, và đỉnh $1$ là gốc. Mỗi đỉnh có một giá trị.

Nhiệm vụ của bạn là xử lý các loại truy vấn sau:

1. thay đổi giá trị của đỉnh $s$ thành $x$
2. tính tổng các giá trị trên đường đi từ gốc đến đỉnh $s$

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng đỉnh và số truy vấn. Các đỉnh được đánh số $1,2,\ldots,n$.

Dòng tiếp theo chứa $n$ số nguyên $v\_1,v\_2,\ldots,v\_n$: giá trị của mỗi đỉnh.

Sau đó là $n-1$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh nối giữa đỉnh $a$ và đỉnh $b$.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi truy vấn có dạng "1 $s$ $x$" hoặc "2 $s$".

# Kết quả

In ra câu trả lời cho mỗi truy vấn loại 2.

# Giới hạn

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le a,b, s \le n$
* $1 \le v\_i, x \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
4 2 5 2 1
1 2
1 3
3 4
3 5
2 4
1 3 2
2 4
```

Kết quả:

```cpp
11
8
```
