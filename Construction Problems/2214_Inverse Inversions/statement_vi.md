# 2214 - Nghịch thế ngược

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là tạo một hoán vị của các số $1,2,\dots,n$ có chính xác $k$ nghịch thế.

Một nghịch thế là một cặp $(a,b)$ với $a<b$ và $p\_a>p\_b$, trong đó $p\_i$ là số tại vị trí $i$ trong hoán vị.

# Dữ liệu vào

Dòng duy nhất chứa hai số nguyên $n$ và $k$.

# Kết quả

In ra một dòng chứa hoán vị. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

# Giới hạn

* $1 \le n \le 10^6$
* $0 \le k \le \frac{n(n-1)}{2}$

# Ví dụ

Dữ liệu vào:

```cpp
5 4
```

Kết quả:

```cpp
1 5 2 4 3
```
