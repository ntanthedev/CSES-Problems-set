# 2166 - Truy vấn tổng tiền tố

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, nhiệm vụ của bạn là xử lý $q$ truy vấn thuộc các loại sau:

1. cập nhật giá trị tại vị trí $k$ thành $u$
2. tổng tiền tố lớn nhất trong đoạn $[a,b]$ là bao nhiêu?

Cho phép các tiền tố rỗng (có tổng bằng 0).

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng giá trị và số lượng truy vấn.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các giá trị của mảng.

Cuối cùng, có $q$ dòng mô tả các truy vấn. Mỗi dòng chứa ba số nguyên: "1 $k$ $u$" hoặc "2 $a$ $b$".

# Kết quả

In ra kết quả của mỗi truy vấn loại 2.

# Giới hạn

* $1 \le n,q \le 2 \cdot 10^5$
* $-10^9 \le x\_i, u \le 10^9$
* $1 \le k \le n$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
8 4
1 2 -1 3 1 -5 1 4
2 2 6
1 4 -2
2 2 6
2 3 4
```

Kết quả:

```cpp
5
2
0
```
