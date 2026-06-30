# 3108 - K Subset Sums I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Xét tổng của tất cả $2^n$ tập con của mảng đã cho (bao gồm cả tập con rỗng với tổng bằng 0).

Nhiệm vụ của bạn là tìm $k$ tổng tập con nhỏ nhất.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: kích thước của mảng và số lượng tổng tập con $k$.

Dòng tiếp theo chứa $n$ số nguyên $x\_1, x\_2,\dots, x\_n$: nội dung của mảng.

# Kết quả

In ra $k$ số nguyên: $k$ tổng tập con nhỏ nhất theo thứ tự tăng dần.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le k \le \min(2^n, 2 \cdot 10^5)$
* $-10^9 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 9
1 6 3 -3
```

Kết quả:

```cpp
-3 -2 0 0 1 1 3 3 4
```
