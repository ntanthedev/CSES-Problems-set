# 1079 - Hệ số nhị thức

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là tính $n$ hệ số nhị thức modulo $10^9+7$.

Một hệ số nhị thức ${a \choose b}$ có thể được tính bằng công thức $\frac{a!}{b!(a-b)!}$. Chúng ta giả sử $a$ và $b$ là các số nguyên và $0 \le b \le a$.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng phép tính.

Sau đó là $n$ dòng, mỗi dòng chứa hai số nguyên $a$ và $b$.

# Kết quả

In ra mỗi hệ số nhị thức modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 10^5$
* $0 \le b \le a \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
3
5 3
8 1
9 5
```

Kết quả:

```cpp
10
8
126
```
