# 1077 - Chi phí cửa sổ trượt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Nhiệm vụ của bạn là tính cho mỗi cửa sổ gồm $k$ phần tử, từ trái sang phải, tổng chi phí nhỏ nhất để làm cho tất cả các phần tử bằng nhau.

Bạn có thể tăng hoặc giảm mỗi phần tử với chi phí $x$, trong đó $x$ là chênh lệch giữa giá trị mới và giá trị ban đầu. Tổng chi phí là tổng của các chi phí đó.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: số lượng phần tử và kích thước cửa sổ.

Sau đó là $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung của mảng.

# Kết quả

In ra $n-k+1$ giá trị: các chi phí.

# Giới hạn

* $1 \le k \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8 3
2 4 3 5 8 1 2 1
```

Kết quả:

```cpp
2 2 5 7 7 1
```
