# 1754 - Hai đống xu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn có hai đống xu chứa $a$ và $b$ đồng xu. Mỗi lượt, bạn có thể lấy một đồng xu từ đống bên trái và hai đồng xu từ đống bên phải, hoặc hai đồng xu từ đống bên trái và một đồng xu từ đống bên phải.

Nhiệm vụ của bạn là xác định một cách hiệu quả liệu bạn có thể làm rỗng cả hai đống hay không.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $t$: số lượng bộ test.

Sau đó, có $t$ dòng, mỗi dòng chứa hai số nguyên $a$ và $b$: số lượng đồng xu trong hai đống.

# Kết quả

Với mỗi bộ test, in ra "YES" nếu có thể làm rỗng cả hai đống và "NO" nếu ngược lại.

# Giới hạn

* $1 \le t \le 10^5$
* $0 \le a, b \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
3
2 1
2 2
3 3
```

Kết quả:

```cpp
YES
NO
YES
```
