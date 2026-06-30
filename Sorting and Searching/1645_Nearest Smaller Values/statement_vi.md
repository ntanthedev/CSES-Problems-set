# 1645 - Nearest Smaller Values

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, nhiệm vụ của bạn là tìm với mỗi vị trí trong mảng vị trí gần nhất bên trái có giá trị nhỏ hơn.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: kích thước của mảng.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các giá trị của mảng.

# Kết quả

In ra $n$ số nguyên: với mỗi vị trí trong mảng, vị trí gần nhất có giá trị nhỏ hơn. Nếu không có vị trí như vậy, in ra $0$.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8
2 5 1 4 8 3 2 5
```

Kết quả:

```cpp
0 1 0 3 4 3 3 7
```
