# 2169 - Đếm Đoạn Chứa Nhau

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho $n$ đoạn, nhiệm vụ của bạn là với mỗi đoạn, hãy đếm xem có bao nhiêu đoạn khác nằm trong nó và nó nằm trong bao nhiêu đoạn khác.

Đoạn $[a,b]$ chứa đoạn $[c,d]$ nếu $a \le c$ và $d \le b$.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng đoạn.

Sau đó là $n$ dòng mô tả các đoạn. Mỗi dòng chứa hai số nguyên $x$ và $y$: đoạn $[x,y]$.

Bạn có thể giả sử rằng không có đoạn nào xuất hiện quá một lần trong dữ liệu vào.

# Kết quả

Đầu tiên, in ra một dòng mô tả cho mỗi đoạn (theo thứ tự dữ liệu vào) có bao nhiêu đoạn khác nằm trong nó.

Sau đó, in ra một dòng mô tả cho mỗi đoạn (theo thứ tự dữ liệu vào) nó nằm trong bao nhiêu đoạn khác.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x < y \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
1 6
2 4
4 8
3 6
```

Kết quả:

```cpp
2 0 0 0
0 1 0 1
```
