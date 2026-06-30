# 3314 - Dãy núi

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ ngọn núi xếp thành một hàng, mỗi ngọn có một độ cao nhất định. Bạn bắt đầu đường bay lượn của mình từ một ngọn núi nào đó.

Bạn có thể lượn từ núi $a$ đến núi $b$ nếu núi $a$ cao hơn núi $b$ và cao hơn tất cả các núi nằm giữa $a$ và $b$.

Hỏi số lượng núi tối đa bạn có thể ghé thăm trên đường đi của mình là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng ngọn núi.

Dòng tiếp theo chứa $n$ số nguyên $h\_1, h\_2,\dots, h\_n$: độ cao của các ngọn núi.

# Kết quả

In ra một số nguyên: số lượng núi tối đa.

# Giới hạn

* $1\le n \le 2 \cdot 10^5$
* $1\le h\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
10
20 15 17 35 25 40 12 19 13 12
```

Kết quả:

```cpp
5
```
