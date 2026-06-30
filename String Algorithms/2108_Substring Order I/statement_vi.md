# 2108 - Thứ tự xâu con I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu có độ dài $n$. Nếu tất cả các xâu con phân biệt của nó được sắp xếp theo thứ tự từ điển, thì xâu nhỏ thứ $k$ là xâu nào?

# Dữ liệu vào

Dòng đầu tiên chứa một xâu có độ dài $n$ gồm các ký tự a–z.

Dòng thứ hai chứa một số nguyên $k$.

# Kết quả

In ra xâu con phân biệt nhỏ thứ $k$ theo thứ tự từ điển.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le k \le \frac{n(n+1)}{2}$
* Được đảm bảo rằng $k$ không vượt quá số lượng xâu con phân biệt.

# Ví dụ

Dữ liệu vào:

```cpp
babaacbaab
10
```

Kết quả:

```cpp
aba
```

Giải thích: 10 xâu con phân biệt nhỏ nhất theo thứ tự là a, aa, aab, aac, aacb, aacba, aacbaa, aacbaab, ab, và aba.
