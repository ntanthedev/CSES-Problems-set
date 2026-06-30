# 2104 - Vị Trí Mẫu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu và các mẫu, hãy tìm với mỗi mẫu vị trí đầu tiên (đánh chỉ số từ 1) mà nó xuất hiện trong xâu.

# Dữ liệu vào

Dòng đầu tiên chứa một xâu có độ dài $n$.

Dòng tiếp theo chứa một số nguyên $k$: số lượng mẫu. Cuối cùng, có $k$ dòng mô tả các mẫu.

Xâu và các mẫu đều gồm các ký tự a–z.

# Kết quả

In ra vị trí đầu tiên cho mỗi mẫu (hoặc $-1$ nếu nó không xuất hiện).

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le k \le 5 \cdot 10^5$
* tổng độ dài các mẫu tối đa là $5 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
aybabtu
3
bab
abc
a
```

Kết quả:

```cpp
3
-1
1
```
