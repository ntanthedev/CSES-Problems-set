# 1644 - Tổng Đoạn Con Lớn Nhất II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, nhiệm vụ của bạn là tìm tổng lớn nhất của các giá trị trong một đoạn con liên tiếp có độ dài nằm giữa $a$ và $b$.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $a$ và $b$: kích thước của mảng, độ dài tối thiểu và tối đa của đoạn con.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các giá trị của mảng.

# Kết quả

In ra một số nguyên: tổng đoạn con lớn nhất.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a \le b \le n$
* $-10^9 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8 1 2
-1 3 -2 5 3 -5 2 2
```

Kết quả:

```cpp
8
```
