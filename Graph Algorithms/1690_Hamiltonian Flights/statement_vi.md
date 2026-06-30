# 1690 - Các chuyến bay Hamilton

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ kết nối bay giữa chúng. Bạn muốn đi từ Syrjälä đến Lehmälä sao cho bạn ghé thăm mỗi thành phố đúng một lần. Hỏi có bao nhiêu tuyến đường khả dĩ?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và số chuyến bay. Các thành phố được đánh số $1,2,\dots,n$. Thành phố $1$ là Syrjälä, và thành phố $n$ là Lehmälä.

Tiếp theo, có $m$ dòng mô tả các chuyến bay. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một chuyến bay từ thành phố $a$ đến thành phố $b$. Tất cả các chuyến bay đều là một chiều.

# Kết quả

In ra một số nguyên: số lượng tuyến đường chia lấy dư cho $10^9+7$.

# Giới hạn

* $2 \le n \le 20$
* $1 \le m \le n^2$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4 6
1 2
1 3
2 3
3 2
2 4
3 4
```

Kết quả:

```cpp
2
```
