# 1748 - Dãy con tăng dần II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, nhiệm vụ của bạn là đếm số lượng dãy con tăng dần mà nó chứa. Nếu hai dãy con có cùng giá trị nhưng ở các vị trí khác nhau trong mảng, chúng được tính riêng biệt.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: kích thước của mảng.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

# Kết quả

In ra một số nguyên: số lượng dãy con tăng dần modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
3
2 1 3
```

Kết quả:

```cpp
5
```

Giải thích: Các dãy con tăng dần là $[2]$, $[1]$, $[3]$, $[2,3]$ và $[1,3]$.
