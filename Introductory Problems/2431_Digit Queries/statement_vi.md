# 2431 - Truy vấn chữ số

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một xâu vô hạn gồm tất cả các số nguyên dương theo thứ tự tăng dần:

12345678910111213141516171819202122232425...

Nhiệm vụ của bạn là xử lý $q$ truy vấn dạng: chữ số ở vị trí $k$ trong xâu là gì?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $q$: số lượng truy vấn.

Sau đó, có $q$ dòng mô tả các truy vấn. Mỗi dòng chứa một số nguyên $k$: vị trí (đánh số từ $1$) trong xâu.

# Kết quả

Với mỗi truy vấn, in ra chữ số tương ứng.

# Giới hạn

* $1 \le q \le 1000$
* $1 \le k \le 10^{18}$

# Ví dụ

Dữ liệu vào:

```cpp
3
7
19
12
```

Kết quả:

```cpp
7
4
1
```
