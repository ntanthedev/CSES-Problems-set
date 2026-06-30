# 2073 - Substring Reversals

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu, nhiệm vụ của bạn là xử lý các thao tác đảo ngược một xâu con của xâu. Xâu cuối cùng sau tất cả các thao tác là gì?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: độ dài của xâu và số lượng thao tác. Các ký tự của xâu được đánh số $1,2,\dots,n$.

Dòng tiếp theo chứa một xâu có độ dài $n$ gồm các ký tự A–Z.

Cuối cùng, có $m$ dòng mô tả các thao tác. Mỗi dòng chứa hai số nguyên $a$ và $b$: bạn đảo ngược một xâu con từ vị trí $a$ đến vị trí $b$.

# Kết quả

In ra xâu cuối cùng sau tất cả các thao tác.

# Giới hạn

* $1 \le n, m \le 2 \cdot 10^5$
* $1 \le a \le b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
7 2
AYBABTU
3 4
4 7
```

Kết quả:

```cpp
AYAUTBB
```
