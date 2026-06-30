# 2190 - Giao Điểm Đoạn Thẳng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho hai đoạn thẳng: đoạn thứ nhất đi qua các điểm $(x\_1,y\_1)$ và $(x\_2,y\_2)$, và đoạn thứ hai đi qua các điểm $(x\_3,y\_3)$ và $(x\_4,y\_4)$.

Nhiệm vụ của bạn là xác định xem các đoạn thẳng có giao nhau hay không, tức là chúng có ít nhất một điểm chung.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $t$: số lượng bộ test.

Sau đó là $t$ dòng mô tả các bộ test. Mỗi dòng chứa tám số nguyên $x\_1$, $y\_1$, $x\_2$, $y\_2$, $x\_3$, $y\_3$, $x\_4$ và $y\_4$.

# Kết quả

Với mỗi bộ test, in ra "YES" nếu các đoạn thẳng giao nhau và "NO" nếu ngược lại.

# Giới hạn

* $1 \le t \le 10^5$
* $-10^9 \le x\_1, y\_1, x\_2, y\_2, x\_3, y\_3, x\_4, y\_4 \le 10^9$
* $(x\_1,y\_1) \neq (x\_2,y\_2)$
* $(x\_3,y\_3) \neq (x\_4,y\_4)$

# Ví dụ

Dữ liệu vào:

```cpp
5
1 1 5 3 1 2 4 3
1 1 5 3 1 1 4 3
1 1 5 3 2 3 4 1
1 1 5 3 2 4 4 1
1 1 5 3 3 2 7 4
```

Kết quả:

```cpp
NO
YES
YES
YES
YES
```
