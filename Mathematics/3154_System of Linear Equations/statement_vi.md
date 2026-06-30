# 3154 - Hệ Phương Trình Tuyến Tính

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho $n\cdot(m+1)$ hệ số $a\_{i,j}$ và $b\_i$ tạo thành $n$ phương trình tuyến tính sau:

* $a\_{1,1}x\_1 + a\_{1,2}x\_2 + \dots + a\_{1,m}x\_m = b\_1 \pmod {10^9 + 7}$
* $a\_{2,1}x\_1 + a\_{2,2}x\_2 + \dots + a\_{2,m}x\_m = b\_2 \pmod {10^9 + 7}$
* $\dots$
* $a\_{n,1}x\_1 + a\_{n,2}x\_2 + \dots + a\_{n,m}x\_m = b\_n \pmod {10^9 + 7}$

Nhiệm vụ của bạn là tìm $m$ số nguyên $x\_1, x\_2, \dots, x\_m$ thỏa mãn các phương trình đã cho.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số phương trình và số biến.

$n$ dòng tiếp theo, mỗi dòng chứa $m+1$ số nguyên $a\_{i,1}, a\_{i,2}, \dots, a\_{i,m}, b\_i$: các hệ số của phương trình thứ $i$.

# Kết quả

In ra $m$ số nguyên $x\_1, x\_2,\dots, x\_m$: giá trị của các biến thỏa mãn các phương trình. Các giá trị cũng phải thỏa mãn $0 \le x\_i < 10^9 + 7$. Bạn có thể in ra bất kỳ nghiệm nào hợp lệ. Nếu không có nghiệm, chỉ in ra $-1$.

# Giới hạn

* $1 \le n, m \le 500$
* $0 \le a\_{i,j}, b\_i < 10^9 + 7$

# Ví dụ

Dữ liệu vào:

```cpp
3 3
2 0 1 7
1 2 0 0
1 3 1 2
```

Kết quả:

```cpp
2 1000000006 3
```
