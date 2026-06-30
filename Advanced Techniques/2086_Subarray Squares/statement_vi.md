# 2086 - Subarray Squares

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ phần tử, nhiệm vụ của bạn là chia nó thành $k$ đoạn con. Chi phí của mỗi đoạn con là bình phương tổng các giá trị trong đoạn con đó. Tổng chi phí tối thiểu nếu bạn hành động tối ưu là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: số phần tử của mảng và số đoạn con. Các phần tử của mảng được đánh số $1,2,\dots,n$.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

# Kết quả

In ra một số nguyên: tổng chi phí tối thiểu.

# Giới hạn

* $1 \le k \le n \le 3000$
* $1 \le x\_i \le 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
8 3
2 3 1 2 2 3 4 1
```

Kết quả:

```cpp
110
```

Giải thích: Một cách chia tối ưu là $[2,3,1]$, $[2,2,3]$, $[4,1]$, với chi phí là $(2+3+1)^2+(2+2+3)^2+(4+1)^2=110$.
