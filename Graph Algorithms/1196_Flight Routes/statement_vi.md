# 1196 - Các Tuyến Bay

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là tìm $k$ tuyến bay ngắn nhất từ Syrjälä đến Metsälä. Một tuyến đường có thể đi qua cùng một thành phố nhiều lần.

Lưu ý rằng có thể có nhiều tuyến đường có cùng giá và mỗi tuyến trong số chúng đều được tính (xem ví dụ).

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$, và $k$: số lượng thành phố, số lượng chuyến bay và tham số $k$. Các thành phố được đánh số $1,2,\ldots,n$. Thành phố 1 là Syrjälä, và thành phố $n$ là Metsälä.

Sau đó, dữ liệu vào có $m$ dòng mô tả các chuyến bay. Mỗi dòng chứa ba số nguyên $a$, $b$, và $c$: một chuyến bay bắt đầu từ thành phố $a$, kết thúc tại thành phố $b$, và có giá $c$. Tất cả các chuyến bay đều là một chiều.

Bạn có thể giả sử rằng có ít nhất $k$ tuyến đường phân biệt từ Syrjälä đến Metsälä.

# Kết quả

In ra $k$ số nguyên: giá của $k$ tuyến đường rẻ nhất được sắp xếp theo giá.

# Giới hạn

* $2 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$
* $1 \le c \le 10^9$
* $1 \le k \le 10$

# Ví dụ

Dữ liệu vào:

```cpp
4 6 3
1 2 1
1 3 3
2 3 2
2 4 6
3 2 8
3 4 1
```

Kết quả:

```cpp
4 4 7
```

Giải thích: Các tuyến đường rẻ nhất là $1 \rightarrow 3 \rightarrow 4$ (giá $4$), $1 \rightarrow 2 \rightarrow 3 \rightarrow 4$ (giá $4$) và $1 \rightarrow 2 \rightarrow 4$ (giá $7$).
