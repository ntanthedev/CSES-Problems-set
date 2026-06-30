# 1739 - Truy vấn Rừng II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một lưới $n \times n$ biểu diễn bản đồ của một khu rừng. Mỗi ô hoặc là trống hoặc có một cây. Nhiệm vụ của bạn là xử lý $q$ truy vấn thuộc các loại sau:

1. Thay đổi trạng thái (trống/có cây) của một ô.
2. Có bao nhiêu cây nằm trong một hình chữ nhật trong rừng?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $q$: kích thước của khu rừng và số lượng truy vấn.

Tiếp theo, có $n$ dòng mô tả khu rừng. Mỗi dòng có $n$ ký tự: `.` là ô trống và `*` là cây.

Cuối cùng, có $q$ dòng mô tả các truy vấn. Định dạng của mỗi dòng là "1 $y$ $x$" hoặc "2 $y\_1$ $x\_1$ $y\_2$ $x\_2$".

# Kết quả

In ra câu trả lời cho mỗi truy vấn loại thứ hai.

# Giới hạn

* $1 \le n \le 1000$
* $1 \le q \le 2 \cdot 10^5$
* $1 \le y,x \le n$
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
2 2 2 3 4
1 3 3
2 2 2 3 4
```

Kết quả:

```cpp
3
4
```
