# 2107 - Hàm xâu

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu có $n$ ký tự, được đánh chỉ số $1,2,\dots,n$. Nhiệm vụ của bạn là tính tất cả các giá trị của các hàm sau:

* $z(i)$ là độ dài lớn nhất của một xâu con bắt đầu tại vị trí $i$ và là tiền tố của xâu. Ngoài ra, $z(1)=0$.
* $\pi(i)$ là độ dài lớn nhất của một xâu con kết thúc tại vị trí $i$, là tiền tố của xâu, và có độ dài tối đa là $i-1$.

Chú ý rằng hàm $z$ được sử dụng trong giải thuật Z, và hàm $\pi$ được sử dụng trong giải thuật KMP.

# Dữ liệu vào

Dòng duy nhất chứa một xâu có độ dài $n$. Mỗi ký tự nằm trong khoảng a–z.

# Kết quả

In ra hai dòng: đầu tiên là các giá trị của hàm $z$, sau đó là các giá trị của hàm $\pi$.

# Giới hạn

* $1 \le n \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
abaabca
```

Kết quả:

```cpp
0 0 1 2 0 0 1
0 0 1 1 2 0 1
```
