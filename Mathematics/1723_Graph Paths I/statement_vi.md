# 1723 - Đường đi trên đồ thị I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một đồ thị có hướng gồm $n$ đỉnh và $m$ cạnh. Nhiệm vụ của bạn là đếm số lượng đường đi từ đỉnh $1$ đến đỉnh $n$ với đúng $k$ cạnh.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $k$: số lượng đỉnh, số lượng cạnh và độ dài của đường đi. Các đỉnh được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh từ đỉnh $a$ đến đỉnh $b$.

# Kết quả

In ra số lượng đường đi modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 100$
* $1 \le m \le n(n-1)$
* $1 \le k \le 10^9$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
3 4 8
1 2
2 3
3 1
3 2
```

Kết quả:

```cpp
2
```

Giải thích: Các đường đi là $1 \rightarrow 2 \rightarrow 3 \rightarrow 1 \rightarrow 2 \rightarrow 3 \rightarrow 1 \rightarrow 2 \rightarrow 3$ và $1 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 3$.
