# 3157 - Phân phối trò chơi thu thập số

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một mảng chứa mỗi số từ $1 \dots n$ đúng một lần. Bạn thu thập các số theo thứ tự tăng dần từ $1$ đến $n$. Trong mỗi lượt, bạn duyệt mảng từ trái sang phải và thu thập càng nhiều số liên tiếp càng tốt, bắt đầu từ số nhỏ nhất chưa được thu thập.

Nhiệm vụ của bạn là xác định, với mỗi $k=1,2,\dots,n$, số lượng mảng cần đúng $k$ lượt để thu thập tất cả các số.

# Dữ liệu vào

Dòng duy nhất chứa một số nguyên $n$.

# Kết quả

In ra $n$ số: với mỗi $k=1,2,\dots,n$, đáp án lấy modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 5000$

# Ví dụ

Dữ liệu vào:

```cpp
3
```

Kết quả:

```cpp
1
4
1
```

*Giải thích*: Các mảng là $[1,2,3]$ ($1$ lượt), $[1,3,2]$ ($2$ lượt), $[2,1,3]$ ($2$ lượt), $[2,3,1]$ ($2$ lượt), $[3,1,2]$ ($2$ lượt) và $[3,2,1]$ ($3$ lượt).
