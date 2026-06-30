# 2194 - Khoảng cách Euclid nhỏ nhất

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một tập hợp các điểm trên mặt phẳng hai chiều, nhiệm vụ của bạn là tìm khoảng cách Euclid nhỏ nhất giữa hai điểm phân biệt.

Khoảng cách Euclid của hai điểm $(x\_1,y\_1)$ và $(x\_2,y\_2)$ là $\sqrt{(x\_1-x\_2)^2+(y\_1-y\_2)^2}$.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng điểm.

Sau đó là $n$ dòng mô tả các điểm. Mỗi dòng chứa hai số nguyên $x$ và $y$. Bạn có thể giả sử các điểm đều phân biệt.

# Kết quả

In ra một số nguyên: $d^2$ với $d$ là khoảng cách Euclid nhỏ nhất (điều này đảm bảo kết quả là một số nguyên).

# Giới hạn

* $2 \le n \le 2 \cdot 10^5$
* $-10^9 \le x,y \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
2 1
4 4
1 2
6 3
```

Kết quả:

```cpp
2
```
