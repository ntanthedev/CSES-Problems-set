# 3302 - Subsets with Fixed Average

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Nhiệm vụ của bạn là đếm số tập con khác rỗng của mảng đã cho có giá trị trung bình bằng $a$.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $a$: kích thước của mảng và giá trị trung bình mục tiêu.

Dòng tiếp theo chứa $n$ số nguyên $x\_1, x\_2,\dots, x\_n$: nội dung của mảng.

# Kết quả

In ra một số nguyên: số tập con khác rỗng có giá trị trung bình bằng $a$, lấy modulo $10^9 + 7$.

# Giới hạn

* $1 \le n \le 500$
* $1 \le a \le 500$
* $1 \le x\_i \le 500$

# Ví dụ

Dữ liệu vào:

```cpp
5 2
1 1 2 3 4
```

Kết quả:

```cpp
7
```
