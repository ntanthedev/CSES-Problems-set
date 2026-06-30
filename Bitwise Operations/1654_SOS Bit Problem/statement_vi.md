# 1654 - Bài toán bit SOS

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một danh sách gồm $n$ số nguyên, nhiệm vụ của bạn là với mỗi phần tử $x$ hãy tính:

1. số lượng phần tử $y$ sao cho $x \mid y = x$
2. số lượng phần tử $y$ sao cho $x \mathrel{\&} y = x$
3. số lượng phần tử $y$ sao cho $x \mathrel{\&} y \neq 0$

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của danh sách.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các phần tử của danh sách.

# Kết quả

In ra $n$ dòng: với mỗi phần tử, in ra các giá trị yêu cầu.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
5
3 7 2 9 2
```

Kết quả:

```cpp
3 2 5
4 1 5
2 4 4
1 1 3
2 4 4
```
