# 2168 - Nested Ranges Check

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho $n$ đoạn, nhiệm vụ của bạn là xác định với mỗi đoạn xem nó có chứa một đoạn khác hay không và có đoạn khác chứa nó hay không.

Đoạn $[a,b]$ chứa đoạn $[c,d]$ nếu $a \le c$ và $d \le b$.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng đoạn.

Sau đó là $n$ dòng mô tả các đoạn. Mỗi dòng chứa hai số nguyên $x$ và $y$: đoạn là $[x,y]$.

Bạn có thể giả sử không có đoạn nào xuất hiện quá một lần trong đầu vào.

# Kết quả

Đầu tiên in ra một dòng mô tả cho mỗi đoạn (theo thứ tự đầu vào) nếu nó chứa một đoạn khác (1) hay không (0).

Sau đó in ra một dòng mô tả cho mỗi đoạn (theo thứ tự đầu vào) nếu có đoạn khác chứa nó (1) hay không (0).

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x < y \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
1 6
2 4
4 8
3 6
```

Kết quả:

```cpp
1 0 0 0
0 1 0 1
```
