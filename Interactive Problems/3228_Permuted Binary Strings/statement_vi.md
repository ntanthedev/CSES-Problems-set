# 3228 - Xâu Nhị Phân Hoán Vị

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một hoán vị $a\_1, a\_2,\dots, a\_n$ bị ẩn của các số nguyên $1, 2,\dots, n$. Nhiệm vụ của bạn là tìm ra hoán vị này.

Để làm điều này, bạn có thể đặt câu hỏi: bạn có thể chọn một xâu nhị phân $b\_1b\_2\dots b\_n$ và sẽ nhận được xâu nhị phân $b\_{a\_1}b\_{a\_2}\dots b\_{a\_n}$.

# Tương tác

Đây là một bài toán tương tác. Mã của bạn sẽ tương tác với bộ chấm điểm qua đầu vào và đầu ra chuẩn. Bạn nên bắt đầu bằng cách đọc một số nguyên $n$: độ dài của hoán vị.

Trong mỗi lượt, bạn có thể in một trong các dòng sau:

* "$?\ b\_1b\_2\dots b\_n$", với $b\_i\in\{0, 1\}$: Bộ chấm sẽ trả về xâu nhị phân $b\_{a\_1}b\_{a\_2}\dots b\_{a\_n}$.
* "$!\ a\_1\ a\_2 \dots a\_n$": thông báo rằng hoán vị bị ẩn là $a\_1, a\_2,\dots, a\_n$. Chương trình của bạn phải kết thúc sau đó.

Mỗi dòng phải được kết thúc bằng một dấu xuống dòng. Bạn phải đảm bảo bộ đệm đầu ra được xả sau khi in mỗi dòng.

# Giới hạn

* $1 \le n \le 1000$
* bạn có thể hỏi tối đa $10$ câu hỏi loại $?$

# Ví dụ

```cpp
3
? 100
100
? 010
001
? 001
010
! 1 3 2
```

**Giải thích:** Hoán vị bị ẩn là $[1, 3, 2]$. Ở câu hỏi đầu tiên $b\_1b\_2b\_3 = 100$ và bộ chấm trả về $b\_{a\_1}b\_{a\_2}b\_{a\_3} = b\_1b\_3b\_2 = 100$. Ở câu hỏi thứ hai $b\_1b\_2b\_3 = 010$ và bộ chấm trả về $b\_1b\_3b\_2 = 001$.
