# 1131 - Tree Diameter

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một cây gồm $n$ đỉnh.

*Đường kính* của một cây là khoảng cách lớn nhất giữa hai đỉnh. Nhiệm vụ của bạn là xác định đường kính của cây.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng đỉnh. Các đỉnh được đánh số $1,2,\ldots,n$.

Sau đó là $n-1$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh nối giữa đỉnh $a$ và $b$.

# Kết quả

In ra một số nguyên: đường kính của cây.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 2
1 3
3 4
3 5
```

Kết quả:

```cpp
3
```

Giải thích: Đường kính tương ứng với đường đi $2 \rightarrow 1 \rightarrow 3 \rightarrow 5$.
