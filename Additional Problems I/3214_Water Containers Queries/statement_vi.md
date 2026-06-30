# 3214 - Water Containers Queries

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có hai bình nước: bình $A$ có thể tích $a$ và bình $B$ có thể tích $b$. Bạn muốn đong $x$ đơn vị nước bằng các bình này.

Ban đầu cả hai bình đều rỗng. Trong mỗi bước, bạn có thể đổ đầy một bình, đổ hết một bình hoặc chuyển nước từ bình này sang bình kia. Khi chuyển nước, bạn phải luôn đổ đầy hoặc đổ hết ít nhất một bình. Sau các bước, bình $A$ phải có $x$ đơn vị nước.

Nhiệm vụ của bạn là kiểm tra một cách hiệu quả xem có thể đong được nước trong nhiều trường hợp hay không.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng bộ test.

Sau đó là $n$ dòng, mỗi dòng chứa ba số nguyên $a$, $b$ và $x$.

# Kết quả

Với mỗi bộ test, in ra YES nếu có thể đong được nước và NO nếu ngược lại.

# Giới hạn

* $1 \le n \le 1000$
* $1 \le a, b, x \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
7
5 3 4
1 1 1
1 1 2
2 2 1
123 456 42
1000 999 123
1000 998 123
```

Kết quả:

```cpp
YES
YES
NO
NO
YES
YES
NO
```
