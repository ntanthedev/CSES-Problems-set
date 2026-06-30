# 1674 - Cấp dưới

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho cấu trúc của một công ty, nhiệm vụ của bạn là tính cho mỗi nhân viên số lượng cấp dưới của họ.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng nhân viên. Các nhân viên được đánh số $1,2,\dots,n$, và nhân viên $1$ là tổng giám đốc của công ty.

Sau đó là $n-1$ số nguyên: với mỗi nhân viên $2,3,\dots,n$, sếp trực tiếp của họ trong công ty.

# Kết quả

In ra $n$ số nguyên: với mỗi nhân viên $1,2,\dots,n$, số lượng cấp dưới của họ.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 1 2 3
```

Kết quả:

```cpp
4 1 1 0 0
```
