# 1099 - Trò chơi cầu thang

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một cầu thang gồm $n$ bậc, được đánh số $1,2,\ldots,n$. Ban đầu, mỗi bậc có một số quả bóng.

Có hai người chơi luân phiên nhau. Mỗi lượt, một người chơi chọn một bậc $k$ sao cho $k \neq 1$ và bậc đó có ít nhất một quả bóng. Sau đó, người chơi di chuyển một số lượng bóng bất kỳ từ bậc $k$ xuống bậc $k-1$. Người di chuyển cuối cùng sẽ thắng.

Nhiệm vụ của bạn là xác định ai thắng nếu cả hai chơi tối ưu.

Lưu ý rằng nếu không có nước đi nào có thể thực hiện, người chơi thứ hai thắng.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test. Sau đó, $t$ bộ test được mô tả như sau:

Dòng đầu tiên chứa một số nguyên $n$: số lượng bậc thang.

Dòng tiếp theo chứa $n$ số nguyên $p\_1,p\_2,\ldots,p\_n$: số lượng bóng ban đầu trên mỗi bậc.

# Kết quả

Với mỗi bộ test, in ra "first" nếu người chơi thứ nhất thắng và "second" nếu người chơi thứ hai thắng.

# Giới hạn

* $1 \le t \le 2 \cdot 10^5$
* $1 \le n \le 2 \cdot 10^5$
* $0 \le p\_i \le 10^9$
* tổng tất cả $n$ không vượt quá $2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
3
3
0 2 1
4
1 1 1 1
2
5 3
```

Kết quả:

```cpp
first
second
first
```
