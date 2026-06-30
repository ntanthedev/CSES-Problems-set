# 2205 - Gray Code

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Mã Gray là một danh sách tất cả $2^n$ xâu bit độ dài $n$, sao cho hai xâu liên tiếp bất kỳ chỉ khác nhau đúng một bit (tức là khoảng cách Hamming của chúng bằng một).

Nhiệm vụ của bạn là tạo một mã Gray cho độ dài $n$ cho trước.

# Dữ liệu vào

Dòng duy nhất chứa một số nguyên $n$.

# Kết quả

In ra $2^n$ dòng mô tả mã Gray. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

# Giới hạn

* $1 \le n \le 16$

# Ví dụ

Dữ liệu vào:

```cpp
2
```

Kết quả:

```cpp
00
01
11
10
```
