# 1651 - Truy vấn cập nhật trên đoạn

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, nhiệm vụ của bạn là xử lý $q$ truy vấn thuộc các loại sau:

1. tăng mỗi giá trị trong đoạn $[a,b]$ lên $u$
2. giá trị tại vị trí $k$ là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng phần tử và số lượng truy vấn.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các giá trị của mảng.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa ba số nguyên: "$1$ $a$ $b$ $u$" hoặc "$2$ $k$".

# Kết quả

In ra kết quả của mỗi truy vấn loại 2.

# Giới hạn

* $1 \le n,q \le 2 \cdot 10^5$
* $1 \le x\_i, u \le 10^9$
* $1 \le k \le n$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
8 3
3 2 4 5 1 1 5 3
2 4
1 2 5 1
2 4
```

Kết quả:

```cpp
5
6
```
