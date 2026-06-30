# 1711 - Các Đường đi Phân biệt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một trò chơi gồm $n$ căn phòng và $m$ cổng dịch chuyển. Vào đầu mỗi ngày, bạn bắt đầu ở phòng $1$ và phải đến được phòng $n$.

Bạn có thể sử dụng mỗi cổng dịch chuyển tối đa một lần trong suốt trò chơi. Hỏi bạn có thể chơi tối đa bao nhiêu ngày nếu chọn đường đi tối ưu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng phòng và cổng dịch chuyển. Các phòng được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các cổng dịch chuyển. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cổng dịch chuyển từ phòng $a$ đến phòng $b$.

Không có hai cổng dịch chuyển nào có cùng phòng xuất phát và phòng đến.

# Kết quả

Đầu tiên in ra một số nguyên $k$: số ngày tối đa bạn có thể chơi. Sau đó, in ra $k$ mô tả đường đi theo ví dụ. Bạn có thể in ra bất kỳ nghiệm đúng nào.

# Giới hạn

* $2 \le n \le 500$
* $1 \le m \le 1000$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
6 7
1 2
1 3
2 6
3 4
3 5
4 6
5 6
```

Kết quả:

```cpp
2
3
1 2 6
4
1 3 4 6
```
