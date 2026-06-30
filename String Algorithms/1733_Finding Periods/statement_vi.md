# 1733 - Tìm Chu Kỳ

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một *chu kỳ* (period) của một xâu là một tiền tố có thể được dùng để sinh ra toàn bộ xâu bằng cách lặp lại tiền tố đó. Lần lặp cuối cùng có thể không đầy đủ. Ví dụ, các chu kỳ của `abcabca` là `abc`, `abcabc` và `abcabca`.

Nhiệm vụ của bạn là tìm tất cả độ dài chu kỳ của một xâu.

# Dữ liệu vào

Dòng đầu tiên chứa một xâu có độ dài $n$ gồm các ký tự a–z.

# Kết quả

In ra tất cả độ dài chu kỳ theo thứ tự tăng dần.

# Giới hạn

* $1 \le n \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
abcabca
```

Kết quả:

```cpp
3 6 7
```
