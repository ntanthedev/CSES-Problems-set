# 3423 - Hoán vị tổng nguyên tố

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho $n$, hãy tạo hai hoán vị $a$ và $b$ kích thước $n$ sao cho $a\_i+b\_i$ là số nguyên tố với $i=1,2,\dots,n$.

# Dữ liệu vào

Dòng duy nhất chứa một số nguyên $n$.

# Kết quả

In ra hai hoán vị. Bạn có thể in ra bất kỳ phương án hợp lệ nào. Nếu không có lời giải, in ra `IMPOSSIBLE`.

# Giới hạn

* $1 \le n \le 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
5
```

Kết quả:

```cpp
2 1 3 5 4
5 1 4 2 3
```

*Giải thích*: Các tổng là $2+5=7$, $1+1=2$, $3+4=7$, $5+2=7$ và $4+3=7$, tất cả đều là số nguyên tố.
