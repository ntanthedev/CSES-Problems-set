# 1636 - Tổ hợp xu II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một hệ thống tiền tệ gồm $n$ đồng xu. Mỗi đồng xu có một giá trị nguyên dương. Nhiệm vụ của bạn là tính số cách có thứ tự khác nhau để tạo ra tổng tiền $x$ bằng các đồng xu có sẵn.

Ví dụ, nếu các đồng xu là $\{2,3,5\}$ và tổng cần tạo là $9$, có $3$ cách:

* $2+2+5$
* $3+3+3$
* $2+2+2+3$

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $x$: số lượng đồng xu và tổng tiền cần tạo.

Dòng thứ hai chứa $n$ số nguyên phân biệt $c\_1,c\_2,\dots,c\_n$: giá trị của mỗi đồng xu.

# Kết quả

In ra một số nguyên: số cách modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 100$
* $1 \le x \le 10^6$
* $1 \le c\_i \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
3 9
2 3 5
```

Kết quả:

```cpp
3
```
