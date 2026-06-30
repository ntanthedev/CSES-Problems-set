# 2208 - Another Game

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ đống đồng xu và hai người chơi thay phiên nhau di chuyển. Mỗi lượt, người
chơi chọn một số đống không rỗng và bỏ một đồng xu khỏi mỗi đống đó. Người chơi
bỏ đồng xu cuối cùng sẽ thắng.

Nhiệm vụ của bạn là tìm ra ai thắng nếu cả hai chơi tối ưu.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $t$: số lượng bộ test. Sau đó, $t$ bộ test được mô
tả như sau:

Dòng đầu tiên chứa số nguyên $n$: số lượng đống.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: số đồng xu trong mỗi
đống.

# Kết quả

Với mỗi bộ test, in ra "first" nếu người chơi đầu tiên thắng và "second" nếu
người chơi thứ hai thắng.

# Giới hạn

* $1 \le t \le 2 \cdot 10^5$
* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$
* tổng tất cả các $n$ không vượt quá $2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
3
3
1 2 3
2
2 2
4
5 5 4 5
```

Kết quả:

```cpp
first
second
first
```
