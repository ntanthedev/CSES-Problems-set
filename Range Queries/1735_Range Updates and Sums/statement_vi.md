# 1735 - Cập nhật và tính tổng trên đoạn

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là duy trì một mảng gồm $n$ giá trị và xử lý hiệu quả các loại truy vấn sau:

1. Tăng mỗi giá trị trong đoạn $[a,b]$ lên $x$.
2. Gán mỗi giá trị trong đoạn $[a,b]$ thành $x$.
3. Tính tổng các giá trị trong đoạn $[a,b]$.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: kích thước mảng và số lượng truy vấn.

Dòng tiếp theo chứa $n$ giá trị $t\_1,t\_2,\dots,t\_n$: nội dung ban đầu của mảng.

Cuối cùng là $q$ dòng mô tả các truy vấn. Định dạng của mỗi dòng là một trong các dạng sau: "1 $a$ $b$ $x$", "2 $a$ $b$ $x$", hoặc "3 $a$ $b$".

# Kết quả

In ra câu trả lời cho mỗi truy vấn tính tổng.

# Giới hạn

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le t\_i, x \le 10^6$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
6 5
2 3 1 1 5 3
3 3 5
1 2 4 2
3 3 5
2 2 4 5
3 3 5
```

Kết quả:

```cpp
7
11
15
```
