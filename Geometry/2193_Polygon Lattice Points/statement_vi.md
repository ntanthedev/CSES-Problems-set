# 2193 - Điểm Nguyên Trong Đa Giác

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đa giác, nhiệm vụ của bạn là đếm số lượng điểm nguyên nằm trong đa giác và trên biên của nó. Điểm nguyên là điểm có tọa độ là số nguyên.

Đa giác gồm $n$ đỉnh $(x\_1,y\_1),(x\_2,y\_2),\dots,(x\_n,y\_n)$. Các đỉnh $(x\_i,y\_i)$ và $(x\_{i+1},y\_{i+1})$ kề nhau với $i=1,2,\dots,n-1$, và các đỉnh $(x\_1,y\_1)$ và $(x\_n,y\_n)$ cũng kề nhau.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng đỉnh.

Sau đó là $n$ dòng mô tả các đỉnh. Dòng thứ $i$ chứa hai số nguyên $x\_i$ và $y\_i$.

Bạn có thể giả sử rằng đa giác là đơn, tức là nó không tự cắt.

# Kết quả

In ra hai số nguyên: số lượng điểm nguyên bên trong đa giác và trên biên của nó.

# Giới hạn

* $3 \le n \le 10^5$
* $-10^9 \le x\_i, y\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
1 1
5 3
3 5
1 4
```

Kết quả:

```cpp
6 8
```
