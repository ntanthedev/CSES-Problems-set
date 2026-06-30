# 3139 - Hoán Vị Ẩn

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một hoán vị $a\_1, a\_2,\dots, a\_n$ bị ẩn của các số nguyên $1, 2,\dots, n$. Nhiệm vụ của bạn là tìm ra hoán vị này.

Để làm điều này, bạn có thể đặt câu hỏi: bạn có thể chọn hai chỉ số $i$ và $j$ và sẽ được cho biết liệu $a\_i < a\_j$ hay không.

# Tương tác

Đây là một bài toán tương tác. Mã của bạn sẽ tương tác với bộ chấm điểm qua đầu vào và đầu ra chuẩn. Bạn nên bắt đầu bằng cách đọc một số nguyên $n$: độ dài của hoán vị.

Trong mỗi lượt, bạn có thể in một trong các dòng sau:

* "$?\ i\ j$", với $1 \le i, j \le n$: hỏi liệu $a\_i < a\_j$. Bộ chấm sẽ trả về `YES` nếu $a\_i < a\_j$ và `NO` nếu ngược lại.
* "$!\ a\_1\ a\_2 \dots a\_n$": thông báo rằng hoán vị bị ẩn là $a\_1, a\_2,\dots, a\_n$. Chương trình của bạn phải kết thúc sau đó.

Mỗi dòng phải được kết thúc bằng một dấu xuống dòng. Bạn phải đảm bảo bộ đệm đầu ra được xả sau khi in mỗi dòng.

# Giới hạn

* $1 \le n \le 1000$
* bạn có thể hỏi tối đa $10^4$ câu hỏi loại $?$

# Ví dụ

```cpp
3
? 3 2
NO
? 3 1
YES
! 3 1 2
```

**Giải thích:** Hoán vị bị ẩn là $[3, 1, 2]$. Câu hỏi đầu tiên hỏi liệu $a\_3 < a\_2$, điều này sai, nên câu trả lời là `NO`. Câu hỏi thứ hai hỏi liệu $a\_3 < a\_1$, điều này đúng, nên câu trả lời là `YES`.
