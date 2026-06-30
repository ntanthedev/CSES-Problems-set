# 3305 - Điểm Số Cao Thứ K

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ lập trình viên đến từ Phần Lan và $n$ lập trình viên đến từ Thụy Điển trong một kỳ thi lập trình. Sau kỳ thi, mỗi lập trình viên có một điểm số phân biệt.

Nhiệm vụ của bạn là tìm điểm số cao thứ $k$ trong kỳ thi.

Để làm điều này, bạn có thể đặt câu hỏi: bạn có thể chọn một quốc gia (Phần Lan hoặc Thụy Điển) và một số nguyên $i$ và sẽ được cho biết điểm số cao thứ $i$ của quốc gia đã chọn.

# Tương tác

Đây là một bài toán tương tác. Mã của bạn sẽ tương tác với bộ chấm điểm qua đầu vào và đầu ra chuẩn. Bạn nên bắt đầu bằng cách đọc hai số nguyên $n$ và $k$.

Trong mỗi lượt, bạn có thể in một trong các dòng sau:

* "$\mathrm{F}\ i$", với $1 \le i \le n$: hỏi điểm số cao thứ $i$ của Phần Lan.
* "$\mathrm{S}\ i$", với $1 \le i \le n$: hỏi điểm số cao thứ $i$ của Thụy Điển.
* "$!\ s$": thông báo rằng điểm số cao thứ $k$ là $s$. Chương trình của bạn phải kết thúc sau đó.

Mỗi dòng phải được kết thúc bằng một dấu xuống dòng. Bạn phải đảm bảo bộ đệm đầu ra được xả sau khi in mỗi dòng.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le k \le 2n$
* mỗi điểm số nằm giữa $1$ và $10^9$
* bạn có thể hỏi tổng cộng tối đa $100$ truy vấn thuộc hai loại đầu tiên

# Ví dụ

```cpp
3 1
F 1
9
S 1
8
! 9
```

**Giải thích:** Điểm số của Phần Lan là $[9, 4, 3]$ và điểm số của Thụy Điển là $[8, 6, 1]$. Vì $k = 1$, nhiệm vụ là tìm điểm số cao nhất tổng thể, trong trường hợp này là $9$.
