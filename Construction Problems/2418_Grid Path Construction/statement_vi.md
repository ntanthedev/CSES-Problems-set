# 2418 - Xây dựng đường đi trên lưới

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một lưới $n \times m$ và hai ô $a=(y\_1,x\_1)$ và $b=(y\_2,x\_2)$, hãy tạo một đường đi từ $a$ đến $b$ đi qua mỗi ô đúng một lần.

Ví dụ, đây là một đường đi từ $a=(1,3)$ đến $b=(3,6)$ trong lưới $4 \times 7$:
![](944079e41a17eca6debb54a7d4da8f9124232206a1d80256432e8a2715c00055)

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test.

Sau đó là $t$ dòng mô tả các bộ test. Mỗi dòng chứa sáu số nguyên $n$, $m$, $y\_1$, $x\_1$, $y\_2$ và $x\_2$.

Trong tất cả các bộ test, $1 \le y\_1,y\_2 \le n$ và $1 \le x\_1,x\_2 \le m$. Ngoài ra, $y\_1 \neq y\_2$ hoặc $x\_1 \neq x\_2$.

# Kết quả

In ra YES nếu có thể xây dựng một đường đi, và NO nếu không thể.

Nếu có đường đi, cũng in ra mô tả của nó gồm các ký tự `U` (lên), `D` (xuống), `L` (trái) và `R` (phải). Nếu có nhiều đường đi, bạn có thể in ra bất kỳ đường nào.

# Giới hạn

* $1 \le t \le 100$
* $1 \le n \le 50$
* $1 \le m \le 50$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 3 1 1 1 3
1 3 1 2 1 3
2 2 1 1 2 2
2 2 1 1 2 1
4 7 1 3 3 6
```

Kết quả:

```cpp
YES
RR
NO
NO
YES
RDL
YES
RRRRDDDLLLLLLUUURDDRURDRURD
```
