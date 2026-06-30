# 1638 - Đường đi trên lưới I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một lưới $n \times n$ mà các ô có thể có bẫy. Không được phép di chuyển vào ô có bẫy.

Nhiệm vụ của bạn là tính số đường đi từ ô trên cùng bên trái đến ô dưới cùng bên phải. Bạn chỉ có thể di chuyển sang phải hoặc xuống dưới.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: kích thước của lưới.

Sau đó là $n$ dòng mô tả lưới. Mỗi dòng có $n$ ký tự: `.` biểu thị ô trống và `*` biểu thị bẫy.

# Kết quả

In ra số đường đi modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
4
....
.*..
...*
*...
```

Kết quả:

```cpp
3
```
