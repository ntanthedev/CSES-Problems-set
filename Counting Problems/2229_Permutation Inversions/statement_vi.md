# 2229 - Permutation Inversions

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là đếm số lượng hoán vị của $1,2,\dots,n$ có chính xác $k$ nghịch thế (tức là các cặp phần tử theo thứ tự sai).

Ví dụ, khi $n=4$ và $k=3$, có $6$ hoán vị như vậy:

* $[1,4,3,2]$
* $[2,3,4,1]$
* $[2,4,1,3]$
* $[3,1,4,2]$
* $[3,2,1,4]$
* $[4,1,2,3]$

# Dữ liệu vào

Dòng duy nhất chứa hai số nguyên $n$ và $k$.

# Kết quả

In ra đáp án modulo $10^9+7$.

# Giới hạn

* $1 \le n \le 500$
* $0 \le k \le \frac{n(n-1)}{2}$

# Ví dụ

Input:

```cpp
4 3
```

Output:

```cpp
6
```
