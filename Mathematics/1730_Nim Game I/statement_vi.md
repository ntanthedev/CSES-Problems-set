# 1730 - Nim Game I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ đống que và hai người chơi thay phiên nhau di chuyển. Ở mỗi lượt, người chơi chọn một đống không rỗng và lấy ra một số que bất kỳ. Người lấy que cuối cùng sẽ thắng cuộc.

Nhiệm vụ của bạn là xác định ai thắng nếu cả hai chơi tối ưu.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $t$: số lượng bộ test. Sau đó, $t$ bộ test được mô tả như sau:

Dòng đầu tiên chứa một số nguyên $n$: số lượng đống.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: số lượng que trong mỗi đống.

# Kết quả

Với mỗi bộ test, in ra "first" nếu người chơi đầu tiên thắng và "second" nếu người chơi thứ hai thắng.

# Giới hạn

* $1 \le t \le 2 \cdot 10^5$
* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$
* tổng của tất cả $n$ không vượt quá $2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
3
4
5 7 2 5
2
4 1
3
3 5 6
```

Kết quả:

```cpp
first
first
second
```
