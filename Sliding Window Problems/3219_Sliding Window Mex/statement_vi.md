# 3219 - Mex cửa sổ trượt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Nhiệm vụ của bạn là tính mex của mỗi cửa sổ gồm $k$ phần tử, từ trái sang phải.

Mex là số nguyên không âm nhỏ nhất không xuất hiện trong mảng. Ví dụ, mex của $[3,1,4,3,0,5]$ là $2$.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: số lượng phần tử và kích thước cửa sổ.

Sau đó là $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung của mảng.

# Kết quả

In ra $n-k+1$ giá trị: các giá trị mex.

# Giới hạn

* $1 \le k \le n \le 2 \cdot 10^5$
* $0 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8 3
1 2 1 0 5 1 1 0
```

Kết quả:

```cpp
0 3 2 2 0 2
```
