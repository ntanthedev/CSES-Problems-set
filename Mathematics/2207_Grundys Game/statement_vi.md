# 2207 - Trò chơi Grundy

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một đống $n$ đồng xu và hai người chơi thay phiên nhau di chuyển. Mỗi lượt,
người chơi chọn một đống và chia nó thành hai đống không rỗng có số lượng đồng
xu khác nhau. Người chơi thực hiện lượt cuối cùng sẽ thắng.

Nhiệm vụ của bạn là tìm ra ai thắng nếu cả hai chơi tối ưu.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $t$: số lượng bộ test.

Sau đó là $t$ dòng mô tả các bộ test. Mỗi dòng chứa một số nguyên $n$: số đồng
xu trong đống ban đầu.

# Kết quả

Với mỗi bộ test, in ra "first" nếu người chơi đầu tiên thắng và "second" nếu
người chơi thứ hai thắng.

# Giới hạn

* $1 \le t \le 10^5$
* $1 \le n \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
3
6
7
8
```

Kết quả:

```cpp
first
second
first
```
