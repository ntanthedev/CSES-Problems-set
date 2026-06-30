# 3304 - Visible Buildings Queries (Truy vấn Tòa nhà Có thể Nhìn thấy)

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ tòa nhà xếp thành một hàng được đánh số $1, 2,\dots, n$ từ trái sang phải. Bạn đang đứng ở bên trái của tòa nhà đầu tiên. Bạn có thể nhìn thấy một tòa nhà nếu nó cao hơn tất cả các tòa nhà ở bên trái nó.

Nhiệm vụ của bạn là xử lý $q$ truy vấn: Nếu chỉ có các tòa nhà trong đoạn $[a, b]$ tồn tại, bạn sẽ nhìn thấy bao nhiêu tòa nhà?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: số lượng tòa nhà và số truy vấn.

Dòng thứ hai chứa $n$ số nguyên $h\_1, h\_2, \dots, h\_n$: chiều cao của các tòa nhà.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa hai số nguyên $a$ và $b$.

# Kết quả

Với mỗi truy vấn, in ra một số nguyên: số lượng tòa nhà có thể nhìn thấy.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le q \le 2 \cdot 10^5$
* $1 \le h\_i \le 10^9$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
4 1 2 2 3
1 5
2 5
3 4
```

Kết quả:

```cpp
1
3
1
```
