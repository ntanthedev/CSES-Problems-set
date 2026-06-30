# 1697 - Giải đấu cờ vua

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Sẽ có một giải đấu cờ vua gồm $n$ kỳ thủ. Mỗi kỳ thủ đã thông báo số ván đấu họ muốn chơi.

Mỗi cặp kỳ thủ có thể chơi tối đa một ván. Nhiệm vụ của bạn là xác định các ván đấu sẽ được tổ chức sao cho tất cả đều hài lòng.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng kỳ thủ. Các kỳ thủ được đánh số $1,2,\dots,n$.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: với mỗi kỳ thủ, số ván đấu họ muốn chơi.

# Kết quả

In ra đầu tiên một số nguyên $k$: số ván đấu. Sau đó, in $k$ dòng mô tả các ván đấu. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

Nếu không có lời giải, in ra "IMPOSSIBLE".

# Giới hạn

* $1 \le n \le 10^5$
* $\sum\_{i=1}^{n} x\_i \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 3 2 0 2
```

Kết quả:

```cpp
4
1 2
2 3
2 5
3 5
```
