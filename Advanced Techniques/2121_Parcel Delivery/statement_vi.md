# 2121 - Giao Hàng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ tuyến đường mà qua đó các bưu kiện có thể được vận chuyển từ thành phố này đến thành phố khác. Với mỗi tuyến đường, bạn biết số lượng bưu kiện tối đa và chi phí cho một bưu kiện.

Bạn muốn gửi $k$ bưu kiện từ Syrjälä đến Lehmälä. Hãy tìm cách rẻ nhất để thực hiện điều đó.

# Dữ liệu vào

Dòng đầu tiên gồm ba số nguyên $n$, $m$ và $k$: số lượng thành phố, tuyến đường và bưu kiện. Các thành phố được đánh số $1,2,\dots,n$. Thành phố $1$ là Syrjälä và thành phố $n$ là Lehmälä.

Sau đó, có $m$ dòng mô tả các tuyến đường. Mỗi dòng gồm bốn số nguyên $a$, $b$, $r$ và $c$: có một tuyến đường từ thành phố $a$ đến thành phố $b$, tối đa $r$ bưu kiện có thể được vận chuyển qua tuyến đường này, và chi phí cho mỗi bưu kiện là $c$.

# Kết quả

In ra một số nguyên: tổng chi phí nhỏ nhất hoặc $-1$ nếu không có cách nào.

# Giới hạn

* $2 \le n \le 500$
* $1 \le m \le 1000$
* $1 \le k \le 100$
* $1 \le a,b \le n$
* $1 \le r,c \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
4 5 3
1 2 5 100
1 3 10 50
1 4 7 500
2 4 8 350
3 4 2 100
```

Kết quả:

```cpp
750
```

Giải thích: Một bưu kiện được gửi qua tuyến đường $1 \rightarrow 2 \rightarrow 4$ (chi phí $1 \cdot 450 = 450$) và hai bưu kiện được gửi qua tuyến đường $1 \rightarrow 3 \rightarrow 4$ (chi phí $2 \cdot 150 = 300$).
