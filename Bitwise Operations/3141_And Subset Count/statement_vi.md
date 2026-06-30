# 3141 - Đếm tập con AND

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Nhiệm vụ của bạn là tính số lượng tập con khác rỗng có *phép AND bit* của các phần tử bằng $k$ với mỗi $k = 0, 1,\dots, n$.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng.

Dòng tiếp theo chứa $n$ số nguyên $a\_1, a\_2,\dots, a\_n$: các phần tử của mảng.

# Kết quả

In ra $n + 1$ số nguyên như mô tả ở trên theo modulo $10^9 + 7$.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $0 \le a\_i \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4
3 1 3 4
```

Kết quả:

```cpp
7 4 0 3 1
```
