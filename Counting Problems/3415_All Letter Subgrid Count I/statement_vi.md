# 3415 - All Letter Subgrid Count I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một lưới các ký tự. Nhiệm vụ của bạn là tính số lượng lưới con *hình vuông* chứa tất cả các ký tự.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: kích thước lưới và số lượng ký tự. Các ký tự là $k$ chữ cái in hoa đầu tiên.

Sau đó là $n$ dòng mô tả lưới. Mỗi dòng có $n$ ký tự.

# Kết quả

In ra số lượng lưới con.

# Giới hạn

* $1 \le n \le 3000$
* $1 \le k \le 26$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
ABBBC
BBBBC
BCAAA
AAAAA
AAAAA
```

Kết quả:

```cpp
15
```
