# 1076 - Trung vị cửa sổ trượt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Nhiệm vụ của bạn là tính trung vị của mỗi cửa sổ gồm $k$ phần tử, từ trái sang phải.

Trung vị là phần tử ở giữa khi các phần tử được sắp xếp. Nếu số lượng phần tử là chẵn, có hai trung vị khả dĩ và ta coi trung vị là phần tử nhỏ hơn trong hai phần tử đó.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: số lượng phần tử và kích thước cửa sổ.

Sau đó là $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung của mảng.

# Kết quả

In ra $n-k+1$ giá trị: các trung vị.

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
3 4 5 5 2 1
```
