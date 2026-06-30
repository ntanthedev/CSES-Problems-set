# 1670 - Trò chơi Hoán đổi

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một lưới $3 \times 3$ chứa các số $1,2,\dots,9$. Nhiệm vụ của bạn là thực hiện một dãy các bước di chuyển để lưới trông như thế này:
$$\begin{matrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9 \\
\end{matrix}$$
Ở mỗi bước, bạn có thể hoán đổi hai số ở hai ô liền kề bất kỳ (theo chiều ngang hoặc chiều dọc). Số bước di chuyển ít nhất cần thực hiện là bao nhiêu?

# Dữ liệu vào

Đầu vào gồm ba dòng, mỗi dòng chứa ba số nguyên.

# Kết quả

In ra một số nguyên: số bước di chuyển ít nhất.

# Ví dụ

Dữ liệu vào:

```cpp
2 1 3
7 5 9
8 4 6
```

Kết quả:

```cpp
4
```
