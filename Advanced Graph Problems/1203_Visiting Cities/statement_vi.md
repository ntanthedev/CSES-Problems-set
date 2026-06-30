# 1203 - Thành Phố Ghé Thăm

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn muốn đi từ Syrjälä đến Lehmälä bằng máy bay sử dụng tuyến đường có giá nhỏ nhất. Những thành phố nào bạn chắc chắn sẽ ghé thăm?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và số lượng chuyến bay. Các thành phố được đánh số $1,2,\ldots,n$. Thành phố 1 là Syrjälä, và thành phố $n$ là Lehmälä.

Sau đó, có $m$ dòng mô tả các chuyến bay. Mỗi dòng có ba số nguyên $a$, $b$, và $c$: có một chuyến bay từ thành phố $a$ đến thành phố $b$ với giá $c$. Tất cả các chuyến bay đều là chuyến bay một chiều.

Bạn có thể giả định rằng có một tuyến đường từ Syrjälä đến Lehmälä.

# Kết quả

Đầu tiên in ra một số nguyên $k$: số lượng thành phố chắc chắn có trong tuyến đường. Sau đó, in ra $k$ thành phố được sắp xếp theo thứ tự tăng dần.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le c \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 6
1 2 3
1 3 4
2 3 1
2 4 5
3 4 1
4 5 8
```

Kết quả:

```cpp
4
1 3 4 5
```
