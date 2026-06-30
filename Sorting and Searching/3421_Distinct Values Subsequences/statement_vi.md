# 3421 - Dãy Con Các Giá Trị Phân Biệt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, đếm số lượng dãy con mà mỗi phần tử là phân biệt.

Một dãy con là một dãy các phần tử của mảng theo thứ tự từ trái sang phải và có thể bỏ qua một số phần tử.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: kích thước mảng.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

# Kết quả

In ra số lượng dãy con với các phần tử phân biệt. Đáp án có thể rất lớn, do đó hãy in ra kết quả modulo $10^9+7$.

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
11
```

*Giải thích*: Các dãy con là $[1]$ (hai lần), $[2]$, $[3]$, $[1,2]$, $[1,3]$ (hai lần), $[2,1]$, $[2,3]$, $[1,2,3]$ và $[2,1,3]$.
