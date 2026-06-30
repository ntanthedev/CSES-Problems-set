# 3109 - K Subset Sums II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Xét tổng của tất cả $\binom{n}{m}$ tập con có đúng $m$ phần tử của mảng đã cho.

Nhiệm vụ của bạn là tìm $k$ tổng tập con nhỏ nhất.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $k$: kích thước của mảng, kích thước của tập con và số lượng tổng tập con $k$.

Dòng tiếp theo chứa $n$ số nguyên $x\_1, x\_2,\dots, x\_n$: nội dung của mảng.

# Kết quả

In ra $k$ số nguyên: $k$ tổng tập con nhỏ nhất theo thứ tự tăng dần.

# Giới hạn

* $1 \le m < n \le 2 \cdot 10^5$
* $1 \le k \le \min\left(\binom{n}{m}, 2 \cdot 10^5\right)$
* $-10^9 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 3 9
-3 1 5 2 0
```

Kết quả:

```cpp
-2 -1 0 2 3 3 4 6 7
```
