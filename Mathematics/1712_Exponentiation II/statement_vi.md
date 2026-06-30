# 1712 - Luỹ thừa II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là tính toán hiệu quả các giá trị $a^{b^c}$ modulo $10^9+7$.

Lưu ý rằng trong bài toán này ta coi $0^0=1$.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng phép tính.

Sau đó, có $n$ dòng, mỗi dòng chứa ba số nguyên $a$, $b$ và $c$.

# Kết quả

In ra mỗi giá trị $a^{b^c}$ modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 10^5$
* $0 \le a,b,c \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
3
3 7 1
15 2 2
3 4 5
```

Kết quả:

```cpp
2187
50625
763327764
```
