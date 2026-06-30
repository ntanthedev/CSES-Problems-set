# 3161 - Tập con GCD

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Nhiệm vụ của bạn là tính số lượng tập con khác rỗng có ước chung lớn nhất của các phần tử bằng $k$ với mỗi $k = 1,\dots, n$.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: kích thước của mảng.

Dòng tiếp theo chứa $n$ số nguyên $x\_1, x\_2,\dots, x\_n$: các phần tử của mảng.

# Kết quả

In ra $n$ số nguyên như đã mô tả ở trên theo modulo $10^9 + 7$.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
5 4 4 2 3
```

Kết quả:

```cpp
22 4 1 3 1
```
