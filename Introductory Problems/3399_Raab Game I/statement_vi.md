# 3399 - Raab Game I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét trò chơi hai người chơi, mỗi người có $n$ thẻ được đánh số $1,2,\dots,n$. Ở mỗi lượt, cả hai người chơi đặt một thẻ của mình lên bàn. Người chơi nào đặt thẻ có số lớn hơn sẽ được một điểm. Nếu các thẻ bằng nhau, không ai được điểm. Trò chơi tiếp tục cho đến khi tất cả các thẻ đã được chơi.

Cho biết số lượng thẻ $n$ và điểm số của hai người chơi khi kết thúc trò chơi, $a$ và $b$. Nhiệm vụ của bạn là đưa ra một ví dụ về diễn biến khả thi của trò chơi.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test.

Sau đó là $t$ dòng, mỗi dòng chứa ba số nguyên $n$, $a$ và $b$.

# Kết quả

Với mỗi bộ test, in ra `YES` nếu tồn tại một ván đấu với kết quả đã cho và `NO` nếu ngược lại.

Nếu câu trả lời là `YES`, in ra một ví dụ về một ván đấu khả thi. In ra hai dòng mô tả thứ tự mà người chơi đặt các thẻ của họ. Bạn có thể đưa ra bất kỳ ví dụ hợp lệ nào.

# Giới hạn

* $1 \le t \le 1000$
* $1 \le n \le 100$
* $0 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
4 1 2
2 0 1
3 0 0
2 1 1
4 4 1
```

Kết quả:

```cpp
YES
1 4 3 2
2 1 3 4
NO
YES
1 2 3
1 2 3
YES
1 2
2 1
NO
```
