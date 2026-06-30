# 3360 - Kiểm tra ô lưới góc

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một lưới các chữ cái. Nhiệm vụ của bạn là tìm các ô lưới con có chiều cao và chiều rộng ít nhất bằng hai và tất cả các góc đều có cùng một chữ cái.

Với mỗi chữ cái, hãy kiểm tra xem có tồn tại một ô lưới con hợp lệ nào mà các góc của nó có chữ cái đó hay không.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: kích thước của lưới và số lượng chữ cái. Các chữ cái là $k$ chữ cái in hoa đầu tiên.

Sau đó là $n$ dòng mô tả lưới. Mỗi dòng có $n$ chữ cái.

# Kết quả

In ra $k$ dòng: với mỗi chữ cái, in `YES` nếu có ô lưới con hợp lệ và `NO` nếu ngược lại.

# Giới hạn

* $1 \le n \le 3000$
* $1 \le k \le 26$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
AAAA
CBBC
CBBE
AAAA
```

Kết quả:

```cpp
YES
YES
NO
NO
NO
```
