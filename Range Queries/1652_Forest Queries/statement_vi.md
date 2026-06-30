# 1652 - Truy vấn khu rừng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một lưới $n \times n$ biểu diễn bản đồ của một khu rừng. Mỗi ô vuông hoặc là trống hoặc chứa một cây. Ô vuông trên cùng bên trái có tọa độ $(1,1)$, và ô vuông dưới cùng bên phải có tọa độ $(n,n)$.

Nhiệm vụ của bạn là xử lý $q$ truy vấn có dạng: có bao nhiêu cây nằm trong một hình chữ nhật cho trước trong khu rừng?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: kích thước của khu rừng và số lượng truy vấn.

Sau đó là $n$ dòng mô tả khu rừng. Mỗi dòng chứa $n$ ký tự: `.` là ô trống và `*` là cây.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa bốn số nguyên $y\_1$, $x\_1$, $y\_2$, $x\_2$ tương ứng với các góc của một hình chữ nhật.

# Kết quả

In ra số lượng cây bên trong mỗi hình chữ nhật.

# Giới hạn

* $1 \le n \le 1000$
* $1 \le q \le 2 \cdot 10^5$
* $1 \le y\_1 \le y\_2 \le n$
* $1 \le x\_1 \le x\_2 \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4 3
.*..
*.**
**..
****
2 2 3 4
3 1 3 1
1 1 2 2
```

Kết quả:

```cpp
3
1
2
```
