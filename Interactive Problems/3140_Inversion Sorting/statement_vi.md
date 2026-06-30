# 3140 - Sắp Xếp Bằng Nghịch Thế

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một hoán vị $a\_1, a\_2,\dots, a\_n$ bị ẩn của các số nguyên $1, 2,\dots, n$. Nhiệm vụ của bạn là sắp xếp hoán vị bằng cách đảo ngược các đoạn con.

Trong mỗi lượt, bạn có thể đảo ngược một đoạn con của hoán vị. Sau đó, bạn sẽ được thông báo số lượng nghịch thế trong hoán vị. Nếu số lượng nghịch thế là $0$ (tức là hoán vị đã được sắp xếp), bạn thắng.

# Tương tác

Đây là một bài toán tương tác. Mã của bạn sẽ tương tác với bộ chấm điểm qua đầu vào và đầu ra chuẩn. Bạn nên bắt đầu bằng cách đọc một số nguyên $n$: độ dài của hoán vị.

Trong lượt của bạn, in hai số nguyên $i$ và $j$: đảo ngược đoạn con từ chỉ số $i$ đến $j$.

Sau đó, dòng đầu vào tiếp theo chứa một số nguyên: số lượng nghịch thế sau thao tác. Nếu số này là $0$, bạn thắng và chương trình của bạn phải kết thúc.

# Giới hạn

* $1 \le n \le 1000$
* bạn có thể thực hiện tối đa $4n$ thao tác

# Ví dụ

```cpp
3
1 2
1
2 3
0
```

**Giải thích:** Ở đây hoán vị ban đầu là $[3,1,2]$. Sau thao tác đầu tiên, hoán vị trở thành $[1,3,2]$ và số lượng nghịch thế là $1$. Sau thao tác thứ hai, hoán vị trở thành $[1,2,3]$ và số lượng nghịch thế là $0$.
