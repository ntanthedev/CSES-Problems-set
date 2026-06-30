# 2078 - Eulerian Subgraphs

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đồ thị vô hướng có $n$ đỉnh và $m$ cạnh.

Chúng ta xét các đồ thị con bao gồm tất cả các đỉnh của đồ thị ban đầu và một số cạnh của nó. Một đồ thị con được gọi là *Eulerian* nếu mỗi đỉnh có bậc chẵn.

Nhiệm vụ của bạn là đếm số lượng đồ thị con Eulerian theo modulo $10^9+7$.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh và cạnh. Các đỉnh được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các cạnh. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh giữa đỉnh $a$ và $b$. Có tối đa một cạnh giữa hai đỉnh, và mỗi cạnh nối hai đỉnh phân biệt.

# Kết quả

In ra số lượng đồ thị con Eulerian theo modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 10^5$
* $0 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4 3
1 2
1 3
2 3
```

Kết quả:

```cpp
2
```

Giải thích: Bạn có thể giữ hoặc xóa tất cả các cạnh, do đó có hai đồ thị con Eulerian khả dĩ.
