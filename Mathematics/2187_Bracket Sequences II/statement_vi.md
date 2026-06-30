# 2187 - Dãy ngoặc II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là tính số lượng dãy ngoặc hợp lệ có độ dài $n$ khi biết một
*tiền tố* của dãy.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$.

Dòng thứ hai chứa một xâu gồm $k$ ký tự: tiền tố của dãy.

# Kết quả

In ra số lượng dãy modulo $10^9+7$.

# Giới hạn

* $1 \le k \le n \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
6
(()
```

Kết quả:

```cpp
2
```

Giải thích: Có hai dãy khả dĩ: `(())()` và `(()())`.
