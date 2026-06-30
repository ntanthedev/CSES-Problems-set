# 1672 - Shortest Routes II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ con đường giữa chúng. Nhiệm vụ của bạn là xử lý $q$ truy vấn, trong đó bạn cần xác định độ dài đường đi ngắn nhất giữa hai thành phố cho trước.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $q$: số lượng thành phố, con đường và truy vấn.

Sau đó, có $m$ dòng mô tả các con đường. Mỗi dòng chứa ba số nguyên $a$, $b$ và $c$: có một con đường giữa thành phố $a$ và $b$ với độ dài $c$. Tất cả các con đường đều là đường hai chiều.

Cuối cùng, có $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $a$ và $b$: xác định độ dài đường đi ngắn nhất giữa hai thành phố $a$ và $b$.

# Kết quả

In độ dài đường đi ngắn nhất cho mỗi truy vấn. Nếu không có đường đi, in $-1$.

# Giới hạn

* $1 \le n \le 500$
* $1 \le m \le n^2$
* $1 \le q \le 10^5$
* $1 \le a,b \le n$
* $1 \le c \le 10^9$

# Ví dụ

Input:

```cpp
4 3 5
1 2 5
1 3 9
2 3 3
1 2
2 1
1 3
1 4
3 2
```

Output:

```cpp
5
5
8
-1
3
```
