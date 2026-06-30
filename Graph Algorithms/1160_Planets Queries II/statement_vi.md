# 1160 - Truy vấn Hành tinh II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn đang chơi một trò chơi gồm n hành tinh. Mỗi hành tinh có một cổng dịch chuyển đến một hành tinh khác (hoặc chính nó).

Bạn cần xử lý $q$ truy vấn dạng: Bạn đang ở hành tinh $a$ và muốn đến hành tinh $b$. Số lần dịch chuyển tối thiểu là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng hành tinh và số truy vấn. Các hành tinh được đánh số $1,2,\ldots,n$.

Dòng thứ hai chứa $n$ số nguyên $t\_1,t\_2,\ldots,t\_n$: điểm đến của cổng dịch chuyển từ mỗi hành tinh.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $a$ và $b$: bạn đang ở hành tinh $a$ và muốn đến hành tinh $b$.

# Kết quả

Với mỗi truy vấn, in ra số lần dịch chuyển tối thiểu. Nếu không thể đến được đích, in ra $-1$.

# Giới hạn

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
2 3 2 3 2
1 2
1 3
1 4
```

Kết quả:

```cpp
1
2
-1
```
