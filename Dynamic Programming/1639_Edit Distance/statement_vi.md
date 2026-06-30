# 1639 - Khoảng cách sửa đổi

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

*Khoảng cách sửa đổi* (edit distance) giữa hai xâu là số phép toán tối thiểu cần thực hiện để biến đổi xâu này thành xâu kia.

Các phép toán được phép là:

* Thêm một ký tự vào xâu.
* Xóa một ký tự khỏi xâu.
* Thay thế một ký tự trong xâu.

Ví dụ, khoảng cách sửa đổi giữa LOVE và MOVIE là 2, vì bạn có thể thay L bằng M, rồi thêm I.

Nhiệm vụ của bạn là tính khoảng cách sửa đổi giữa hai xâu.

# Dữ liệu vào

Dòng đầu tiên chứa một xâu gồm $n$ ký tự từ A–Z.

Dòng thứ hai chứa một xâu gồm $m$ ký tự từ A–Z.

# Kết quả

In ra một số nguyên: khoảng cách sửa đổi giữa hai xâu.

# Giới hạn

* $1 \le n,m \le 5000$

# Ví dụ

Dữ liệu vào:

```cpp
LOVE
MOVIE
```

Kết quả:

```cpp
2
```
