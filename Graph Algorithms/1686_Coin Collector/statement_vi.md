# 1686 - Người thu thập xu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một trò chơi có $n$ căn phòng và $m$ đường hầm giữa chúng. Mỗi căn phòng có một số lượng xu nhất định. Hỏi số lượng xu tối đa bạn có thể thu thập được khi di chuyển qua các đường hầm là bao nhiêu, biết rằng bạn có thể tự do chọn phòng bắt đầu và phòng kết thúc?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng căn phòng và đường hầm. Các phòng được đánh số $1,2,\dots,n$.

Tiếp theo, có $n$ số nguyên $k\_1,k\_2,\ldots,k\_n$: số lượng xu trong mỗi căn phòng.

Cuối cùng, có $m$ dòng mô tả các đường hầm. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một đường hầm từ phòng $a$ đến phòng $b$. Mỗi đường hầm là một chiều.

# Kết quả

In ra một số nguyên: số lượng xu tối đa bạn có thể thu thập.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le k\_i \le 10^9$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4 4
4 5 2 7
1 2
2 1
1 3
2 4
```

Kết quả:

```cpp
16
```
