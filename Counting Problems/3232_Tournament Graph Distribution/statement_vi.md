# 3232 - Phân phối đồ thị giải đấu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một *đồ thị giải đấu* (tournament graph) là một đồ thị có hướng mà giữa mọi cặp đỉnh đều có đúng một cạnh có hướng.

Cho $n$, nhiệm vụ của bạn là tính với mỗi $k = 1 \dots n$ số lượng đồ thị giải đấu có $n$ đỉnh và $k$ thành phần liên thông mạnh.

# Dữ liệu vào

Dòng duy nhất chứa một số nguyên $n$: số lượng đỉnh.

# Kết quả

In ra $n$ dòng: với mỗi $k=1 \dots n$ số lượng đồ thị lấy modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 500$

# Ví dụ

Dữ liệu vào:

```cpp
3
```

Kết quả:

```cpp
2
0
6
```
