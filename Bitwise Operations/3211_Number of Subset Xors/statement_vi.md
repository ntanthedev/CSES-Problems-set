# 3211 - Number of Subset Xors

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng gồm $n$ số nguyên, nhiệm vụ của bạn là tìm số lượng xor của tập con phân biệt.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: các phần tử của mảng.

# Kết quả

In ra một số nguyên: số lượng xor của tập con phân biệt.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $0 \le x\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
3
3 6 5
```

Kết quả:

```cpp
4
```

Giải thích: Các giá trị sau đây có thể là xor của một tập con:

* $0 = \text{xor của tập rỗng}$
* $3 = 3$
* $5 = 3 \oplus 6$
* $6 = 3 \oplus 5$

Trong trường hợp này, không có giá trị nào khác có thể là xor của một tập con.
