# 1091 - Concert Tickets

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ vé hòa nhạc có sẵn, mỗi vé có một giá nhất định. Sau đó, $m$ khách hàng lần lượt đến.

Mỗi khách hàng đưa ra mức giá tối đa họ sẵn sàng trả cho một vé, và sau đó, họ sẽ nhận được một vé có giá gần nhất với mức giá đó sao cho giá vé không vượt quá mức giá tối đa.

# Dữ liệu vào

Dòng đầu tiên chứa các số nguyên $n$ và $m$: số lượng vé và số lượng khách hàng.

Dòng tiếp theo chứa $n$ số nguyên $h\_1,h\_2,\ldots,h\_n$: giá của mỗi vé.

Dòng cuối cùng chứa $m$ số nguyên $t\_1,t\_2,\ldots,t\_m$: mức giá tối đa của mỗi khách hàng theo thứ tự họ đến.

# Kết quả

Với mỗi khách hàng, in ra giá mà họ sẽ trả cho vé. Sau đó, vé đó không thể được mua lại.

Nếu một khách hàng không thể mua được vé nào, in ra $-1$.

# Giới hạn

* $1 \le n, m \le 2 \cdot 10^5$
* $1 \le h\_i, t\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
5 3 7 8 5
4 8 3
```

Kết quả:

```cpp
3
8
-1
```
