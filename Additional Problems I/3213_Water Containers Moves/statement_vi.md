# 3213 - Water Containers Moves

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có hai bình nước: bình $A$ có thể tích $a$ và bình $B$ có thể tích $b$. Bạn muốn đong $x$ đơn vị nước bằng các bình này.

Ban đầu cả hai bình đều rỗng. Trong mỗi bước, bạn có thể đổ đầy một bình, đổ hết một bình hoặc chuyển nước từ bình này sang bình kia. Khi chuyển nước, bạn ph luôn đổ đầy hoặc đổ hết ít nhất một bình. Sau các bước, bình $A$ phải có $x$ đơn vị nước.

Hãy tìm một dãy các bước sao cho tổng lượng nước đã chuyển là nhỏ nhất, hoặc xác định rằng không thể đong được nước.

# Dữ liệu vào

Dòng duy nhất chứa ba số nguyên $a$, $b$ và $x$.

# Kết quả

Đầu tiên in ra hai số nguyên $n$ và $m$: số bước và tổng lượng nước đã chuyển. Sau đó in ra một dãy $n$ bước. Mỗi bước phải chuyển ít nhất một đơn vị nước và là một trong các thao tác sau:

* `FILL A`: đổ đầy bình $A$
* `FILL B`: đổ đầy bình $B$
* `EMPTY A`: đổ hết bình $A$
* `EMPTY B`: đổ hết bình $B$
* `MOVE A B`: chuyển nước từ bình $A$ sang bình $B$
* `MOVE B A`: chuyển nước từ bình $B$ sang bình $A$

Nếu không thể đong được nước, chỉ in ra $-1$.

# Giới hạn

* $1 \le a, b, x \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
5 3 4
```

Kết quả:

```cpp
6 19
FILL A
MOVE A B
EMPTY B
MOVE A B
FILL A
MOVE A B
```
