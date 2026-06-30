# 3190 - Tách giá trị phân biệt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên. Nhiệm vụ của bạn là đếm số cách tách mảng thành các đoạn liên tiếp sao cho mỗi đoạn đều gồm các giá trị phân biệt.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng.

Dòng tiếp theo chứa $n$ số nguyên $x\_1, x\_2,\dots, x\_n$: nội dung của mảng.

# Kết quả

In ra một số nguyên: kết quả của bài toán modulo $10^9 + 7$.

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
6
```

*Giải thích*: Có sáu cách tách hợp lệ:

* $[1], [2], [1], [3]$
* $[1], [2], [1, 3]$
* $[1], [2, 1], [3]$
* $[1], [2, 1, 3]$
* $[1, 2], [1], [3]$
* $[1, 2], [1, 3]$
