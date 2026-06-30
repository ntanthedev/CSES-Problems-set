# 3414 - Filled Subgrid Count II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một lưới các ký tự. Nhiệm vụ của bạn là tính, với mỗi ký tự, số lượng lưới con *hình chữ nhật* mà mỗi ô trong đó đều là cùng một ký tự.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: kích thước lưới và số lượng ký tự. Các ký tự là $k$ chữ cái in hoa đầu tiên.

Sau đó là $n$ dòng mô tả lưới. Mỗi dòng có $n$ ký tự.

# Kết quả

In ra $k$ dòng: với mỗi ký tự, số lượng lưới con.

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
64
24
4
```
