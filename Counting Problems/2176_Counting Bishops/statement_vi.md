# 2176 - Counting Bishops

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là đếm số cách đặt $k$ quân tượng lên bàn cờ $n \times n$ sao cho không có hai quân tượng nào tấn công nhau.

Hai quân tượng tấn công nhau nếu chúng nằm trên cùng một đường chéo.

# Dữ liệu vào

Dòng duy nhất chứa hai số nguyên $n$ và $k$: kích thước bàn cờ và số lượng quân tượng.

# Kết quả

In ra một số nguyên: số cách modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 500$
* $1 \le k \le n^2$

# Ví dụ

Input:

```cpp
5 4
```

Output:

```cpp
2728
```
