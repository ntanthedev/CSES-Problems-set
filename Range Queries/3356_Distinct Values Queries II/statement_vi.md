# 3356 - Distinct Values Queries II (Truy vấn Giá trị Phân biệt II)

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, nhiệm vụ của bạn là xử lý $q$ truy vấn thuộc các loại sau:

1. cập nhật giá trị tại vị trí $k$ thành $u$
2. kiểm tra xem mọi giá trị trong đoạn $[a, b]$ có phân biệt hay không

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng giá trị và số truy vấn.

Dòng thứ hai chứa $n$ số nguyên $x\_1, x\_2,\dots, x\_n$: các giá trị của mảng.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa ba số nguyên: hoặc "$1$ $k$ $u$" hoặc "$2$ $a$ $b$".

# Kết quả

Với mỗi truy vấn loại 2, in ra `YES` nếu mọi giá trị trong đoạn đều phân biệt và `NO` nếu ngược lại.

# Giới hạn

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le x\_i, u \le 10^9$
* $1 \le k \le n$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 4
3 2 7 2 8
2 3 5
2 2 5
1 2 9
2 2 5
```

Kết quả:

```cpp
YES
NO
YES
```
