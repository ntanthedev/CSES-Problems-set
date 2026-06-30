# 3401 - Hiệu của Que

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho $n$ que với độ dài $a\_1,a\_2,\dots,a\_n$.
Bạn phải thực hiện chính xác $k$ lần cắt vào các que, sao cho
số lượng que trở thành $n + k$.

Sau khi thực hiện các lần cắt, chênh lệch giữa độ dài của que dài nhất và que ngắn nhất càng nhỏ càng tốt. Nhiệm vụ của bạn là tính chênh lệch nhỏ nhất có thể cho tất cả các lượng $k=1,2,\dots,m$.

Các lần cắt phải giữ cho độ dài của các que là số nguyên dương. Bạn có thể giả định rằng các que có thể được cắt $m$ lần.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n,m$: số lượng que và số lần cắt tối đa.

Dòng thứ hai chứa $n$ số nguyên $a\_1,a\_2,\dots,a\_n$:
độ dài của các que.

# Kết quả

In ra một dòng với $m$ số nguyên: chênh lệch nhỏ nhất có thể nếu thực hiện chính xác $k=1,2,\dots,m$ lần cắt.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
3 3
7 3 2
```

Kết quả:

```cpp
2 1 2
```

*Giải thích*: Khi $k=1$, bạn có thể cắt que đầu tiên thành hai que có độ dài $3$ và $4$. Sau đó, độ dài các que là $[3,4,3,2]$ và chênh lệch lớn nhất là $2$.
