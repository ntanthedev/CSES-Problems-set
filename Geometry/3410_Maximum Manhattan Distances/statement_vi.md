# 3410 - Khoảng cách Manhattan lớn nhất

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một tập hợp ban đầu rỗng và $n$ điểm được thêm vào đó. Tính khoảng cách Manhattan lớn nhất giữa hai điểm sau mỗi lần thêm.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng điểm.

$n$ dòng tiếp theo mô tả các điểm. Mỗi dòng chứa hai số nguyên $x$ và $y$. Bạn có thể giả sử các điểm đều phân biệt.

# Kết quả

Sau mỗi lần thêm, in ra khoảng cách lớn nhất.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $-10^9 \le x, y \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 1
3 2
2 4
2 1
4 5
```

Kết quả:

```cpp
0
3
4
4
7
```
