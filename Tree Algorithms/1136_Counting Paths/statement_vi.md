# 1136 - Counting Paths

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một cây gồm $n$ đỉnh và $m$ đường đi trong cây.

Nhiệm vụ của bạn là tính với mỗi đỉnh số lượng đường đi chứa đỉnh đó.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh và số đường đi. Các đỉnh được đánh số $1,2,\ldots,n$.

Sau đó là $n-1$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh nối giữa đỉnh $a$ và $b$.

Cuối cùng là $m$ dòng mô tả các đường đi. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một đường đi giữa hai đỉnh $a$ và $b$.

# Kết quả

In ra $n$ số nguyên: với mỗi đỉnh $1,2,\ldots,n$, số lượng đường đi chứa đỉnh đó.

# Giới hạn

* $1 \le n, m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
1 2
1 3
3 4
3 5
1 3
2 5
1 4
```

Kết quả:

```cpp
3 1 3 1 1
```
