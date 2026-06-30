# 3400 - Trò chơi Raab II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một trò chơi hai người, mỗi người chơi có $n$ thẻ được đánh số $1,2,\dots,n$. Trong mỗi lượt, cả hai người chơi đặt một trong các thẻ của mình lên bàn. Người chơi nào đặt thẻ có số lớn hơn sẽ được một điểm. Nếu các thẻ bằng nhau, không ai được điểm nào. Trò chơi tiếp tục cho đến khi tất cả các thẻ đã được đánh.

Bạn được cho số lượng thẻ $n$ và điểm số của hai người chơi khi kết thúc trò chơi, $a$ và $b$. Nhiệm vụ của bạn là đếm số ván đấu có thể có với kết quả đó.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test.

Sau đó là $t$ dòng, mỗi dòng chứa ba số nguyên $n$, $a$ và $b$.

# Kết quả

Với mỗi bộ test, in ra số ván đấu có thể có lấy modulo $10^9+7$.

# Giới hạn

* $1 \le t \le 1000$
* $1 \le n \le 5000$
* $0 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
3 1 2
2 0 1
5 2 2
9 3 5
4 4 1
```

Kết quả:

```cpp
6
0
4200
976757050
0
```
