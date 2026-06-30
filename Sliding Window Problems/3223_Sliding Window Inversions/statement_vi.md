# 3223 - Trượt Cửa Sổ Nghịch Thế

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Nhiệm vụ của bạn là tính số lượng nghịch thế trong từng cửa sổ gồm $k$ phần tử, từ trái sang phải.

Một nghịch thế là một cặp phần tử mà phần tử bên trái lớn hơn phần tử bên phải.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: số lượng phần tử và kích thước cửa sổ.

Sau đó là $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung của mảng.

# Kết quả

In ra $n-k+1$ giá trị: số lượng nghịch thế.

# Giới hạn

* $1 \le k \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Input:

```cpp
8 3
1 2 3 2 5 2 4 4
```

Output:

```cpp
0 1 1 1 2 0
```
