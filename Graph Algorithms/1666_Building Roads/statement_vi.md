# 1666 - Building Roads

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Byteland có $n$ thành phố và $m$ con đường giữa chúng. Mục tiêu là xây dựng các con đường mới sao cho có đường đi giữa bất kỳ hai thành phố nào.

Nhiệm vụ của bạn là tìm số lượng con đường tối thiểu cần xây dựng, và cũng xác định những con đường nào nên được xây.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và con đường. Các thành phố được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các con đường. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một con đường giữa hai thành phố đó.

Một con đường luôn kết nối hai thành phố khác nhau, và có nhiều nhất một con đường giữa hai thành phố bất kỳ.

# Kết quả

Đầu tiên in một số nguyên $k$: số lượng con đường cần xây dựng.

Sau đó, in $k$ dòng mô tả các con đường mới. Bạn có thể in bất kỳ phương án hợp lệ nào.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Input:

```cpp
4 2
1 2
3 4
```

Output:

```cpp
1
2 3
```
