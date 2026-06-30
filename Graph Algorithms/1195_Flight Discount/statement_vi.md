# 1195 - Giảm Giá Vé Máy Bay

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là tìm một tuyến bay có giá tối thiểu từ Syrjälä đến Metsälä. Bạn có một phiếu giảm giá, sử dụng nó bạn có thể giảm một nửa giá của bất kỳ chuyến bay nào trên tuyến đường. Tuy nhiên, bạn chỉ được sử dụng phiếu giảm giá một lần.

Khi bạn sử dụng phiếu giảm giá cho một chuyến bay có giá $x$, giá của nó trở thành $\lfloor x/2 \rfloor$ (được làm tròn xuống thành số nguyên).

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và các chuyến bay. Các thành phố được đánh số $1,2,\ldots,n$. Thành phố 1 là Syrjälä, và thành phố $n$ là Metsälä.

Sau đó là $m$ dòng mô tả các chuyến bay. Mỗi dòng chứa ba số nguyên $a$, $b$, và $c$: một chuyến bay bắt đầu từ thành phố $a$, kết thúc tại thành phố $b$, và có giá $c$. Mỗi chuyến bay là một chiều.

Bạn có thể giả sử rằng luôn có thể đi từ Syrjälä đến Metsälä.

# Kết quả

In ra một số nguyên: giá của tuyến đường rẻ nhất từ Syrjälä đến Metsälä.

# Giới hạn

* $2 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le c \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
3 4
1 2 3
2 3 1
1 3 7
2 1 5
```

Kết quả:

```cpp
2
```
