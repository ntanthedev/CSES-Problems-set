# 2415 - Phân phối đồ thị hàm số

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một *đồ thị hàm số* (functional graph) là một đồ thị có hướng mà mỗi đỉnh có bậc ra (outdegree) bằng $1$. Ví dụ, sau đây là một đồ thị hàm số có $9$ đỉnh và $2$ thành phần liên thông:

![](39a5e727e368197cdce7593736c5cfd1abf75b6439c0823e27c671ff10662377)

Cho $n$, nhiệm vụ của bạn là tính với mỗi $k=1 \dots n$ số lượng đồ thị hàm số có $n$ đỉnh và $k$ thành phần liên thông.

# Dữ liệu vào

Dòng duy nhất chứa một số nguyên $n$: số lượng đỉnh.

# Kết quả

In ra $n$ dòng: với mỗi $k=1 \dots n$, số lượng đồ thị lấy modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 5000$

# Ví dụ

Dữ liệu vào:

```cpp
3
```

Kết quả:

```cpp
17
9
1
```
