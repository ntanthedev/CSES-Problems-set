# 3420 - Mảng Con Các Giá Trị Phân Biệt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, đếm số lượng mảng con mà mỗi phần tử là phân biệt.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: kích thước mảng.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

# Kết quả

In ra số lượng mảng con với các phần tử phân biệt.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
1 2 1 3
```

Kết quả:

```cpp
8
```

*Giải thích*: Các mảng con là $[1]$ (hai lần), $[2]$, $[3]$, $[1,2]$, $[1,3]$, $[2,1]$ và $[2,1,3]$.
