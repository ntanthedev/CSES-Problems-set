# 2130 - Các Đường Đi Phân Biệt II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một trò chơi gồm $n$ căn phòng và $m$ máy dịch chuyển. Vào đầu mỗi ngày, bạn bắt đầu ở phòng $1$ và phải đến phòng $n$.

Bạn có thể sử dụng mỗi máy dịch chuyển tối đa một lần trong suốt trò chơi. Bạn muốn chơi trò chơi trong đúng $k$ ngày. Mỗi lần bạn sử dụng bất kỳ máy dịch chuyển nào, bạn phải trả một đồng xu. Hỏi số đồng xu tối thiểu bạn phải trả trong $k$ ngày nếu bạn chơi tối ưu là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên gồm ba số nguyên $n$, $m$ và $k$: số lượng phòng, số lượng máy dịch chuyển và số ngày bạn chơi trò chơi. Các phòng được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các máy dịch chuyển. Mỗi dòng gồm hai số nguyên $a$ và $b$: có một máy dịch chuyển từ phòng $a$ đến phòng $b$.

Không có hai máy dịch chuyển nào có cùng phòng xuất phát và phòng đến.

# Kết quả

Đầu tiên, in ra một số nguyên: số đồng xu tối thiểu phải trả nếu chơi tối ưu. Sau đó, in $k$ mô tả tuyến đường theo mẫu trong ví dụ. Bạn có thể in ra bất kỳ cách hợp lệ nào.

Nếu không thể chơi trò chơi trong $k$ ngày, chỉ in ra -1.

# Giới hạn

* $2 \le n \le 500$
* $1 \le m \le 1000$
* $1 \le k \le n-1$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
8 10 2
1 2
1 3
2 5
2 4
3 5 
3 6
4 8
5 8
6 7 
7 8
```

Kết quả:

```cpp
6
4
1 2 4 8 
4
1 3 5 8
```
