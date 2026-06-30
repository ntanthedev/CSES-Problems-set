# 1750 - Truy vấn Hành tinh I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn đang chơi một trò chơi gồm $n$ hành tinh. Mỗi hành tinh có một cổng dịch chuyển đến một hành tinh khác (hoặc chính nó).

Nhiệm vụ của bạn là xử lý $q$ truy vấn dạng: khi bạn bắt đầu ở hành tinh $x$ và đi qua $k$ cổng dịch chuyển, bạn sẽ đến hành tinh nào?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng hành tinh và truy vấn. Các hành tinh được đánh số $1,2,\dots,n$.

Dòng thứ hai chứa $n$ số nguyên $t\_1,t\_2,\dots,t\_n$: với mỗi hành tinh, đích đến của cổng dịch chuyển. Có thể $t\_i=i$.

Cuối cùng, có $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $x$ và $k$: bạn bắt đầu ở hành tinh $x$ và đi qua $k$ cổng dịch chuyển.

# Kết quả

In ra câu trả lời cho mỗi truy vấn.

# Giới hạn

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le t\_i \le n$
* $1 \le x \le n$
* $0 \le k \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4 3
2 1 1 4
1 2
3 4
4 1
```

Kết quả:

```cpp
1
2
4
```
