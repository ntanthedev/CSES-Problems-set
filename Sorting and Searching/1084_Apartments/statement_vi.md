# 1084 - Apartments

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ người nộp đơn và $m$ căn hộ trống. Nhiệm vụ của bạn là phân bổ các căn hộ sao cho nhiều người nộp đơn nhất có thể nhận được căn hộ.

Mỗi người nộp đơn có một kích thước căn hộ mong muốn, và họ sẽ chấp nhận bất kỳ căn hộ nào có kích thước đủ gần với kích thước mong muốn.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$, và $k$: số lượng người nộp đơn, số lượng căn hộ, và độ chênh lệch tối đa cho phép.

Dòng tiếp theo chứa $n$ số nguyên $a\_1, a\_2, \ldots, a\_n$: kích thước căn hộ mong muốn của mỗi người nộp đơn. Nếu kích thước mong muốn của một người nộp đơn là $x$, họ sẽ chấp nhận bất kỳ căn hộ nào có kích thước trong khoảng từ $x-k$ đến $x+k$.

Dòng cuối cùng chứa $m$ số nguyên $b\_1, b\_2, \ldots, b\_m$: kích thước của mỗi căn hộ.

# Kết quả

In ra một số nguyên: số lượng người nộp đơn sẽ nhận được căn hộ.

# Giới hạn

* $1 \le n, m \le 2 \cdot 10^5$
* $0 \le k \le 10^9$
* $1 \le a\_i, b\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 3 5
60 45 80 60
30 60 75
```

Kết quả:

```cpp
2
```
