# 3112 - Số Nguyên Ẩn

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một số nguyên $x$ bị ẩn. Nhiệm vụ của bạn là tìm ra giá trị của $x$.

Để làm điều này, bạn có thể đặt câu hỏi: bạn có thể chọn một số nguyên $y$ và sẽ được cho biết liệu $y < x$ hay không.

# Tương tác

Đây là một bài toán tương tác. Mã của bạn sẽ tương tác với bộ chấm điểm qua đầu vào và đầu ra chuẩn. Bạn có thể bắt đầu đặt câu hỏi ngay lập tức.

Trong mỗi lượt, bạn có thể in một trong các dòng sau:

* "$?\ y$", với $1 \le y \le 10^9$: hỏi liệu $y < x$. Bộ chấm sẽ trả về `YES` nếu $y < x$ và `NO` nếu ngược lại.
* "$!\ x$": thông báo rằng số nguyên bị ẩn là $x$. Chương trình của bạn phải kết thúc sau đó.

Mỗi dòng phải được kết thúc bằng một dấu xuống dòng. Bạn phải đảm bảo bộ đệm đầu ra được xả sau khi in mỗi dòng.

# Giới hạn

* $1 \le x \le 10^9$
* bạn có thể hỏi tối đa $30$ câu hỏi loại $?$

# Ví dụ

```cpp
? 3
YES
? 6
YES
? 7
NO
! 7
```
