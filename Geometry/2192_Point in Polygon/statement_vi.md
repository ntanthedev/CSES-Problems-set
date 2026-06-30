# 2192 - Điểm Trong Đa Giác

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một đa giác có $n$ đỉnh và một danh sách $m$ điểm. Nhiệm vụ của bạn là xác định với mỗi điểm xem nó nằm trong, nằm ngoài hay nằm trên biên của đa giác.

Đa giác gồm $n$ đỉnh $(x\_1,y\_1),(x\_2,y\_2),\dots,(x\_n,y\_n)$. Các đỉnh $(x\_i,y\_i)$ và $(x\_{i+1},y\_{i+1})$ kề nhau với $i=1,2,\dots,n-1$, và các đỉnh $(x\_1,y\_1)$ và $(x\_n,y\_n)$ cũng kề nhau.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh của đa giác và số lượng điểm.

Sau đó là $n$ dòng mô tả đa giác. Dòng thứ $i$ chứa hai số nguyên $x\_i$ và $y\_i$.

Bạn có thể giả sử rằng đa giác là đơn, tức là nó không tự cắt.

Cuối cùng, có $m$ dòng mô tả các điểm. Mỗi dòng chứa hai số nguyên $x$ và $y$.

# Kết quả

Với mỗi điểm, in ra "INSIDE", "OUTSIDE" hoặc "BOUNDARY".

# Giới hạn

* $3 \le n,m \le 1000$
* $1 \le m \le 1000$
* $-10^9 \le x\_i, y\_i \le 10^9$
* $-10^9 \le x, y \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 3
1 1
4 2
3 5
1 4
2 3
3 1
1 3
```

Kết quả:

```cpp
INSIDE
OUTSIDE
BOUNDARY
```
