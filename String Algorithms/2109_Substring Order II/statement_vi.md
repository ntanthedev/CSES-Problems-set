# 2109 - Thứ tự xâu con II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu có độ dài $n$. Nếu tất cả các xâu con của nó (không nhất thiết phân biệt) được sắp xếp theo thứ tự từ điển, thì xâu nhỏ thứ $k$ là xâu nào?

# Dữ liệu vào

Dòng đầu tiên chứa một xâu có độ dài $n$ gồm các ký tự a–z.

Dòng thứ hai chứa một số nguyên $k$.

# Kết quả

In ra xâu con nhỏ thứ $k$ theo thứ tự từ điển.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le k \le \frac{n(n+1)}{2}$

# Ví dụ

Dữ liệu vào:

```cpp
baabaa
10
```

Kết quả:

```cpp
ab
```

Giải thích: 10 xâu con nhỏ nhất theo thứ tự là a, a, a, a, aa, aa, aab, aaba, aabaa, và ab.
