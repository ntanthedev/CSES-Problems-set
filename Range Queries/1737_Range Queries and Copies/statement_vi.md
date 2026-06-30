# 1737 - Truy vấn đoạn và Sao chép

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là duy trì một danh sách các mảng, ban đầu có một mảng duy nhất. Bạn cần xử lý các loại truy vấn sau:

1. Gán giá trị $a$ trong mảng $k$ thành $x$.
2. Tính tổng các giá trị trong đoạn $[a,b]$ của mảng $k$.
3. Tạo một bản sao của mảng $k$ và thêm nó vào cuối danh sách.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: kích thước mảng và số lượng truy vấn.

Dòng tiếp theo chứa $n$ số nguyên $t\_1,t\_2,\ldots,t\_n$: nội dung ban đầu của mảng.

Cuối cùng, có $q$ dòng mô tả các truy vấn. Định dạng của mỗi dòng là một trong các dạng sau: "1 $k$ $a$ $x$", "2 $k$ $a$ $b$" hoặc "3 $k$".

# Kết quả

In ra câu trả lời cho mỗi truy vấn tính tổng.

# Giới hạn

* $1 \le n, q \le 2 \cdot 10^5$
* $1 \le t\_i, x \le 10^9$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 6
2 3 1 2 5
3 1
2 1 1 5
2 2 1 5
1 2 2 5
2 1 1 5
2 2 1 5
```

Kết quả:

```cpp
13
13
13
15
```
