# 3158 - Công Ty Xe Buýt

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ công ty xe buýt. Mỗi công ty xe buýt hoạt động tại các thành phố nhất định và bán vé với giá cụ thể. Mua một vé từ công ty xe buýt cho phép bạn di chuyển giữa hai thành phố bất kỳ mà công ty đó hoạt động.

Xác định chi phí của tuyến đường rẻ nhất từ Syrjälä đến mọi thành phố.

## Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và công ty xe buýt. Các thành phố được đánh số $1,2,\dots,n$, và thành phố $1$ là Syrjälä.

Dòng tiếp theo chứa $m$ số nguyên $c\_1, c\_2,\dots, c\_m$: giá vé cho mỗi công ty xe buýt.

Sau đó, có $m$ cặp dòng mô tả các thành phố cho mỗi công ty xe buýt.

Dòng đầu tiên của mỗi cặp chứa một số nguyên $k$: số lượng thành phố mà công ty xe buýt hoạt động.

Dòng thứ hai của mỗi cặp chứa $k$ số nguyên phân biệt $a\_1, a\_2,\dots, a\_k$: các thành phố mà công ty xe buýt hoạt động.

Bạn có thể giả sử có thể đi từ Syrjälä đến tất cả các thành phố khác.

## Kết quả

In ra $n$ số nguyên: chi phí tuyến đường rẻ nhất từ Syrjälä đến các thành phố $1,2,\dots,n$.

## Giới hạn

* $1 \le n, m \le 10^5$
* $1 \le c \le 10^9$
* $2 \le k \le n$
* $1 \le a \le n$
* tổng của tất cả $k$ không vượt quá $2 \cdot 10^5$

## Ví dụ

Dữ liệu vào:

```cpp
5 3
4 3 2
3
1 4 3
2
5 1
4
2 3 4 5
```

Kết quả:

```cpp
0 5 4 4 3
```
