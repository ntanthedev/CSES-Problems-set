# 1085 - Array Division

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên dương.

Nhiệm vụ của bạn là chia mảng thành $k$ mảng con sao cho tổng lớn nhất trong một mảng con là nhỏ nhất có thể.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: kích thước của mảng và số lượng mảng con trong cách chia.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung của mảng.

# Kết quả

In ra một số nguyên: tổng lớn nhất trong một mảng con trong cách chia tối ưu.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le k \le n$
* $1 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
2 4 7 3 5
```

Kết quả:

```cpp
8
```

Giải thích: Một cách chia tối ưu là $[2,4],[7],[3,5]$ với tổng các mảng con lần lượt là $6,7,8$. Tổng lớn nhất là tổng cuối cùng $8$.
