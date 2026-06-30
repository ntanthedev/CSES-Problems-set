# 2182 - Phân tích ước số

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một số nguyên, nhiệm vụ của bạn là tìm số lượng, tổng và tích các ước số của
nó. Ví dụ, xét số $12$:

* số lượng ước số là $6$ (đó là $1$, $2$, $3$, $4$, $6$, $12$)
* tổng các ước số là $1+2+3+4+6+12=28$
* tích các ước số là $1 \cdot 2 \cdot 3 \cdot 4 \cdot 6 \cdot 12 = 1728$

Vì số đầu vào có thể lớn, nó được cho dưới dạng phân tích thừa số nguyên tố.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng phần trong phân tích thừa số nguyên tố.

Sau đó là $n$ dòng mô tả phân tích. Mỗi dòng chứa hai số $x$ và $k$, trong đó $x$
là một số nguyên tố và $k$ là số mũ của nó.

# Kết quả

In ra ba số nguyên modulo $10^9+7$: số lượng, tổng và tích các ước số.

# Giới hạn

* $1 \le n \le 10^5$
* $2 \le x \le 10^6$
* mỗi $x$ là một số nguyên tố phân biệt
* $1 \le k \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
2
2 2
3 1
```

Kết quả:

```cpp
6 28 1728
```
