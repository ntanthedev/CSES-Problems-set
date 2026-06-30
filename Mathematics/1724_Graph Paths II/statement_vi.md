# 1724 - Graph Paths II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đồ thị có hướng có trọng số gồm $n$ đỉnh và $m$ cạnh. Nhiệm vụ của bạn là tính độ dài đường đi ngắn nhất từ đỉnh $1$ đến đỉnh $n$ với đúng $k$ cạnh.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $k$: số lượng đỉnh và cạnh, và độ dài của đường đi. Các đỉnh được đánh số $1,2,\dots,n$.

Sau đó là m dòng mô tả các cạnh. Mỗi dòng chứa ba số nguyên $a$, $b$ và $c$: có một cạnh từ đỉnh $a$ đến đỉnh $b$ với trọng số $c$.

# Kết quả

In ra độ dài đường đi ngắn nhất. Nếu không có đường đi nào, in ra $-1$.

# Giới hạn

* $1 \le n \le 100$
* $1 \le m \le n(n-1)$
* $1 \le k \le 10^9$
* $1 \le a,b \le n$
* $1 \le c \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
3 4 8
1 2 5
2 3 4
3 1 1
3 2 2
```

Kết quả:

```cpp
27
```
