# 1671 - Shortest Routes I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ kết nối bay giữa chúng. Nhiệm vụ của bạn là xác định độ dài đường đi ngắn nhất từ Syrjälä đến mọi thành phố.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và kết nối bay. Các thành phố được đánh số $1,2,\dots,n$, và thành phố $1$ là Syrjälä.

Sau đó, có $m$ dòng mô tả các kết nối bay. Mỗi dòng chứa ba số nguyên $a$, $b$ và $c$: một chuyến bay bắt đầu từ thành phố $a$, kết thúc tại thành phố $b$, và có độ dài là $c$. Mỗi chuyến bay là một chiều.

Bạn có thể giả sử rằng có thể đi từ Syrjälä đến tất cả các thành phố khác.

# Kết quả

In $n$ số nguyên: độ dài đường đi ngắn nhất từ Syrjälä đến các thành phố $1,2,\dots,n$.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le c \le 10^9$

# Ví dụ

Input:

```cpp
3 4
1 2 6
1 3 2
3 2 3
1 3 4
```

Output:

```cpp
0 5 2
```
