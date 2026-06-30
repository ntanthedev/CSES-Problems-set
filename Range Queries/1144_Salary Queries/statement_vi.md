# 1144 - Salary Queries

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một công ty có $n$ nhân viên với mức lương nhất định. Nhiệm vụ của bạn là theo dõi mức lương và xử lý các truy vấn.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng nhân viên và số truy vấn. Các nhân viên được đánh số $1,2,\ldots,n$.

Dòng tiếp theo chứa $n$ số nguyên $p\_1,p\_2,\ldots,p\_n$: mức lương của mỗi nhân viên.

Sau đó là $q$ dòng mô tả các truy vấn. Mỗi dòng có một trong các dạng sau:

* `!` $k$ $x$: thay đổi lương của nhân viên $k$ thành $x$
* `?` $a$ $b$: đếm số lượng nhân viên có lương trong khoảng $a \ldots b$

# Kết quả

In ra câu trả lời cho mỗi truy vấn `?`.

# Giới hạn

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le p\_i \le 10^9$
* $1 \le k \le n$
* $1 \le x \le 10^9$
* $1 \le a \le b \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
3 7 2 2 5
? 2 3
! 3 6
? 2 3
```

Kết quả:

```cpp
3
2
```
