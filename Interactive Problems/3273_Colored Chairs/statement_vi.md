# 3273 - Ghế Màu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ chiếc ghế được xếp thành một vòng tròn. Mỗi chiếc ghế có màu đỏ hoặc xanh dương. Các ghế được đánh số $1, 2,\dots, n$; ghế $i$ và $i+1$ nằm cạnh nhau với mọi $1 \le i \le n$. Ở đây ghế $n+1$ được hiểu là ghế $1$.

Nhiệm vụ của bạn là tìm hai chiếc ghế có cùng màu và nằm cạnh nhau.

Để làm điều này, bạn có thể đặt câu hỏi: bạn có thể chọn một chiếc ghế và sẽ được cho biết màu của ghế đó.

# Tương tác

Đây là một bài toán tương tác. Mã của bạn sẽ tương tác với bộ chấm điểm qua đầu vào và đầu ra chuẩn. Bạn nên bắt đầu bằng cách đọc một số nguyên $n$: số lượng ghế.

Trong mỗi lượt, bạn có thể in một trong các dòng sau:

* "$?\ i$", với $1 \le i \le n$: hỏi màu của ghế $i$. Bộ chấm sẽ trả về `R` hoặc `B` tương ứng với màu đỏ hoặc xanh dương.
* "$!\ i$": thông báo rằng ghế $i$ và $i+1$ có cùng màu. Chương trình của bạn phải kết thúc sau đó.

Mỗi dòng phải được kết thúc bằng một dấu xuống dòng. Bạn phải đảm bảo bộ đệm đầu ra được xả sau khi in mỗi dòng.

# Giới hạn

* $3 \le n \le 2 \cdot 10^5$, $n$ là số lẻ
* bạn có thể hỏi tối đa $20$ câu hỏi loại $?$

# Ví dụ

```cpp
5
? 1
R
? 2
B
? 3
B
! 2
```
