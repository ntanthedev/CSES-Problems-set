# 2413 - Đếm tháp

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là xây một tháp có chiều rộng là $2$ và chiều cao là $n$. Bạn có nguồn cung cấp không giới hạn các khối có chiều rộng và chiều cao là số nguyên.

Ví dụ, dưới đây là một số cách có thể cho $n=6$:
![](a2fc04205fb57157bd28c9a6041601fc284681929941470fdfb15fcd4a14b4f2.png)
Cho $n$, có bao nhiêu tháp khác nhau bạn có thể xây? Các tháp được phản chiếu và xoay được tính riêng nếu chúng trông khác nhau.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $t$: số lượng test.

Sau đó, có $t$ dòng, mỗi dòng chứa một số nguyên $n$: chiều cao của tháp.

# Kết quả

Với mỗi test, in ra số lượng tháp modulo $10^9+7$.

# Giới hạn

* $1 \le t \le 100$
* $1 \le n \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
3
2
6
1337
```

Kết quả:

```cpp
8
2864
640403945
```
