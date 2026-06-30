# 3355 - Tổng Bốn Bình Phương

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một kết quả nổi tiếng trong lý thuyết số là mọi số nguyên không âm đều có thể biểu diễn thành tổng của bốn bình phương của các số nguyên không âm.

Cho một số nguyên không âm $n$. Nhiệm vụ của bạn là tìm bốn số nguyên không âm $a$, $b$, $c$ và $d$ sao cho $n = a^2 + b^2 + c^2 + d^2$.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test.

Mỗi dòng trong $t$ dòng tiếp theo chứa một số nguyên $n$.

# Kết quả

Với mỗi bộ test, in ra bốn số nguyên không âm $a$, $b$, $c$ và $d$ thỏa mãn $n = a^2 + b^2 + c^2 + d^2$.

# Giới hạn

* $1 \le t \le 1000$
* $0 \le n \le 10^7$
* tổng của tất cả $n$ không vượt quá $10^7$

# Ví dụ

Dữ liệu vào:

```cpp
3
5
30
322266
```

Kết quả:

```cpp
2 1 0 0
1 2 3 4
314 159 265 358
```
