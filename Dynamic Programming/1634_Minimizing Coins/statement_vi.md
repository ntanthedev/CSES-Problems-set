# 1634 - Minimizing Coins

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một hệ thống tiền tệ gồm $n$ đồng xu. Mỗi đồng xu có giá trị nguyên dương. Nhiệm vụ của bạn là tạo ra một số tiền $x$ bằng cách sử dụng các đồng xu có sẵn sao cho số lượng đồng xu được sử dụng là ít nhất.

Ví dụ, nếu các đồng xu là $\{1,5,7\}$ và số tiền cần tạo là $11$, một nghiệm tối ưu là $5+5+1$ cần $3$ đồng xu.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $x$: số lượng đồng xu và số tiền cần tạo.

Dòng thứ hai chứa $n$ số nguyên phân biệt $c\_1,c\_2,\dots,c\_n$: giá trị của mỗi đồng xu.

# Kết quả

In ra một số nguyên: số lượng đồng xu ít nhất. Nếu không thể tạo ra được số tiền cần tạo, in ra $-1$.

# Giới hạn

* $1 \le n \le 100$
* $1 \le x \le 10^6$
* $1 \le c\_i \le 10^6$

# Ví dụ

Input:

```cpp
3 11
1 5 7
```

Output:

```cpp
3
```
