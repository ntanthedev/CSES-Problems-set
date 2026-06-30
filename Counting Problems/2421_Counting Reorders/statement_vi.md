# 2421 - Đếm hoán vị ký tự

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Tính số cách sắp xếp lại các ký tự của một xâu sao cho không có hai ký tự liền kề nào giống nhau.

Ví dụ, đáp án cho xâu `aabc` là $6$, vì các cách sắp xếp hợp lệ là `abac`, `abca`, `acab`, `acba`, `baca` và `caba`.

# Dữ liệu vào

Dòng duy nhất chứa một xâu gồm $n$ ký tự từ `a`–`z`.

# Kết quả

In ra một số nguyên: đáp án lấy modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 5000$

# Ví dụ

Dữ liệu vào:

```cpp
aabc
```

Kết quả:

```cpp
6
```
