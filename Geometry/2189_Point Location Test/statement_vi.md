# 2189 - Xác Định Vị Trí Điểm

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đường thẳng đi qua hai điểm $p\_1=(x\_1,y\_1)$ và $p\_2=(x\_2,y\_2)$. Cho một điểm $p\_3=(x\_3,y\_3)$.

Nhiệm vụ của bạn là xác định xem $p\_3$ nằm ở bên trái hay bên phải của đường thẳng, hay nó nằm trên đường thẳng khi nhìn từ $p\_1$ đến $p\_2$.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $t$: số lượng bộ test.

Sau đó là $t$ dòng mô tả các bộ test. Mỗi dòng chứa sáu số nguyên: $x\_1$, $y\_1$, $x\_2$, $y\_2$, $x\_3$ và $y\_3$.

# Kết quả

Với mỗi bộ test, in ra "LEFT", "RIGHT" hoặc "TOUCH".

# Giới hạn

* $1 \le t \le 10^5$
* $-10^9 \le x\_1, y\_1, x\_2, y\_2, x\_3, y\_3 \le 10^9$
* $x\_1 \neq x\_2$ hoặc $y\_1 \neq y\_2$

# Ví dụ

Dữ liệu vào:

```cpp
3
1 1 5 3 2 3
1 1 5 3 4 1
1 1 5 3 3 2
```

Kết quả:

```cpp
LEFT
RIGHT
TOUCH
```
