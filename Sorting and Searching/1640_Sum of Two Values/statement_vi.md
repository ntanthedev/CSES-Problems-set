# 1640 - Tổng Hai Giá Trị

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, nhiệm vụ của bạn là tìm hai giá trị (ở hai vị trí phân biệt) có tổng bằng $x$.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $x$: kích thước mảng và tổng mục tiêu.

Dòng thứ hai chứa $n$ số nguyên $a\_1,a\_2,\dots,a\_n$: các giá trị của mảng.

# Kết quả

In ra hai số nguyên: vị trí của hai giá trị. Nếu có nhiều lời giải, bạn có thể in ra bất kỳ lời giải nào. Nếu không có lời giải, in ra `IMPOSSIBLE`.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x,a\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 8
2 7 5 1
```

Kết quả:

```cpp
2 4
```
