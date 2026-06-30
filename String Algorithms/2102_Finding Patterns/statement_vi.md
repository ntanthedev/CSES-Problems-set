# 2102 - Tìm Mẫu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu và các mẫu, hãy kiểm tra từng mẫu xem nó có xuất hiện trong xâu hay không.

# Dữ liệu vào

Dòng đầu tiên chứa một xâu có độ dài $n$.

Dòng tiếp theo chứa một số nguyên $k$: số lượng mẫu. Cuối cùng, có $k$ dòng mô tả các mẫu.

Xâu và các mẫu đều gồm các ký tự a–z.

# Kết quả

Với mỗi mẫu, in "YES" nếu nó xuất hiện trong xâu và "NO" nếu ngược lại.

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
ayba
```

Kết quả:

```cpp
YES
NO
YES
```
