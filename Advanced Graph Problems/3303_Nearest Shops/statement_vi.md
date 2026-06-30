# 3303 - Cửa Hàng Gần Nhất

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ con đường. Mỗi con đường là hai chiều và kết nối hai thành phố. Biết rằng $k$ thành phố có cửa hàng anime.

Nếu bạn sống ở một thành phố, tất nhiên bạn biết rõ cửa hàng anime địa phương nếu có. Bạn muốn tìm cửa hàng anime gần nhất không nằm ở thành phố của bạn.

Với mỗi thành phố, hãy xác định khoảng cách nhỏ nhất đến một thành phố khác có cửa hàng anime.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $k$: số lượng thành phố, con đường và cửa hàng anime. Các thành phố được đánh số $1,2,\dots,n$.

Dòng tiếp theo chứa $k$ số nguyên: các thành phố có cửa hàng anime.

Cuối cùng, có $m$ dòng mô tả các con đường. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một con đường giữa thành phố $a$ và $b$.

# Kết quả

In ra $n$ số nguyên: với mỗi thành phố, khoảng cách nhỏ nhất đến một thành phố khác có cửa hàng anime. Nếu không có thành phố như vậy, in ra $-1$.

# Giới hạn

* $1 \le k \le n \le 10^5$
* $0 \le m \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
9 6 4
2 4 5 7
1 2
1 3
1 8
2 4
3 4
5 6
```

Kết quả:

```cpp
1 1 1 1 -1 1 -1 2 -1
```
