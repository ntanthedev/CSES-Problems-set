# 2228 - Counting Sequences

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là đếm số lượng dãy độ dài $n$ mà mỗi phần tử là một số nguyên từ $1 \dots k$ và mỗi số nguyên từ $1 \dots k$ xuất hiện ít nhất một lần trong dãy.

Ví dụ, khi $n=6$ và $k=4$, một số dãy hợp lệ là $[1,3,1,4,3,2]$ và $[2,2,1,3,4,2]$.

# Dữ liệu vào

Dòng duy nhất chứa hai số nguyên $n$ và $k$.

# Kết quả

In ra một số nguyên: số lượng dãy modulo $10^9+7$.

# Giới hạn

* $1 \le k \le n \le 10^6$

# Ví dụ

Input:

```cpp
6 4
```

Output:

```cpp
1560
```
