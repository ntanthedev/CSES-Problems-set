# 3192 - K Subset Xors

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Xét phép xor của tất cả $2^n$ tập con của mảng (bao gồm cả tập rỗng với xor bằng 0).

Nhiệm vụ của bạn là tìm $k$ giá trị xor của tập con nhỏ nhất.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: kích thước của mảng và số lượng xor của tập con $k$.

Dòng tiếp theo chứa $n$ số nguyên $x\_1, x\_2,\dots, x\_n$: các phần tử của mảng.

# Kết quả

In ra $k$ số nguyên: $k$ giá trị xor của tập con nhỏ nhất theo thứ tự tăng dần.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le k \le \min(2^n, 2 \cdot 10^5)$
* $0 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 9
3 5 14 8
```

Kết quả:

```cpp
0 0 3 3 5 5 6 6 8
```
