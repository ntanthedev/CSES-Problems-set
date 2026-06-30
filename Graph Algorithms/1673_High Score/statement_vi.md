# 1673 - Điểm số cao nhất

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn chơi một trò chơi gồm $n$ căn phòng và $m$ đường hầm. Điểm số ban đầu của bạn là $0$, và mỗi đường hầm làm tăng điểm số của bạn thêm $x$, trong đó $x$ có thể là số dương hoặc âm. Bạn có thể đi qua một đường hầm nhiều lần.

Nhiệm vụ của bạn là đi từ phòng $1$ đến phòng $n$. Hỏi điểm số tối đa bạn có thể đạt được là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng phòng và số lượng đường hầm. Các phòng được đánh số $1,2,\dots,n$.

Sau đó là $m$ dòng mô tả các đường hầm. Mỗi dòng chứa ba số nguyên $a$, $b$ và $x$: đường hầm bắt đầu từ phòng $a$, kết thúc tại phòng $b$, và làm tăng điểm số của bạn thêm $x$. Tất cả các đường hầm đều là đường hầm một chiều.

Bạn có thể giả định rằng luôn có thể đi từ phòng $1$ đến phòng $n$.

# Kết quả

In ra một số nguyên: điểm số tối đa bạn có thể đạt được. Tuy nhiên, nếu bạn có thể đạt được điểm số lớn tùy ý, in ra $-1$.

# Giới hạn

* $1 \le n \le 2500$
* $1 \le m \le 5000$
* $1 \le a,b \le n$
* $-10^9 \le x \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 2 3
2 4 -1
1 3 -2
3 4 7
1 4 4
```

Kết quả:

```cpp
5
```
