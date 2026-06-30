# 2101 - New Roads Queries

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố ở Byteland nhưng chưa có con đường nào giữa chúng. Tuy nhiên, mỗi ngày, một con đường mới sẽ được xây dựng. Tổng cộng sẽ có $m$ con đường.

Nhiệm vụ của bạn là xử lý $q$ truy vấn dạng: "sau bao nhiêu ngày thì lần đầu tiên ta có thể đi từ thành phố $a$ đến thành phố $b$?"

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $q$: số lượng thành phố, số con đường và số truy vấn. Các thành phố được đánh số $1,2,\dots,n$.

Sau đó là $m$ dòng mô tả các con đường theo thứ tự chúng được xây dựng. Mỗi dòng chứa hai số nguyên $a$ và $b$: sẽ có một con đường giữa hai thành phố $a$ và $b$.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $a$ và $b$: ta muốn đi từ thành phố $a$ đến thành phố $b$.

# Kết quả

Với mỗi truy vấn, in ra số ngày, hoặc $-1$ nếu không bao giờ có thể đi được.

# Giới hạn

* $1 \le n, m, q \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 4 3
1 2
2 3
1 3
2 5
1 3
3 4
3 5
```

Kết quả:

```cpp
2
-1
4
```
