# 1095 - Lũy thừa

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là tính toán hiệu quả các giá trị $a^b$ modulo $10^9+7$.

Lưu ý rằng trong bài toán này ta giả sử $0^0=1$.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng phép tính.

Sau đó là $n$ dòng, mỗi dòng chứa hai số nguyên $a$ và $b$.

# Kết quả

In ra mỗi giá trị $a^b$ modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $0 \le a,b \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
3
3 4
2 8
123 123
```

Kết quả:

```cpp
81
256
921450052
```
