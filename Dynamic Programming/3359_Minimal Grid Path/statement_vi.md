# 3359 - Đường đi lưới nhỏ nhất

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn được cho một lưới $n \times n$ mà mỗi ô chứa một chữ cái.

Bạn cần di chuyển từ ô trên cùng bên trái đến ô dưới cùng bên phải. Bạn chỉ có thể di chuyển sang phải hoặc xuống dưới.

Xâu có thứ tự từ điển nhỏ nhất bạn có thể tạo ra là gì?

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: kích thước của lưới.

Sau đó, có $n$ dòng mô tả lưới. Mỗi dòng có $n$ chữ cái từ `A` đến `Z`.

# Kết quả

In ra xâu có thứ tự từ điển nhỏ nhất.

# Giới hạn

* $1 \le n \le 3000$

# Ví dụ

Dữ liệu vào:

```cpp
4
AACA
BABC
ABDA
AACA
```

Kết quả:

```cpp
AAABACA
```
