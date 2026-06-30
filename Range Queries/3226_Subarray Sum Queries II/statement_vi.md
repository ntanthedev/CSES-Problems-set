# 3226 - Subarray Sum Queries II (Truy vấn Tổng Đoạn Con II)

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên và $q$ truy vấn. Trong mỗi truy vấn, nhiệm vụ của bạn là tính tổng đoạn con lớn nhất trong đoạn $[a,b]$.

Các đoạn con rỗng (có tổng bằng $0$) được cho phép.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng phần tử và số truy vấn.

Tiếp theo là $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung của mảng.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $a$ và $b$.

# Kết quả

In ra kết quả của mỗi truy vấn.

# Giới hạn

* $1 \le n, q\le 2 \cdot 10^5$
* $-10^9 \le x\_i \le 10^9$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
8 4
2 5 1 -2 3 -1 -7 1
2 4
2 5
6 7
4 8
```

Kết quả:

```cpp
6
7
0
3
```
