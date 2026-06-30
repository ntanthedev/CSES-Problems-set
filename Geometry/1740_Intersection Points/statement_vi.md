# 1740 - Điểm Giao Nhau

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho $n$ đoạn thẳng nằm ngang và dọc, nhiệm vụ của bạn là đếm số điểm giao nhau của chúng.

Bạn có thể giả sử rằng không có hai đoạn thẳng song song nào giao nhau và không có điểm đầu mút nào của một đoạn thẳng là điểm giao nhau.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng đoạn thẳng.

Sau đó là $n$ dòng mô tả các đoạn thẳng. Mỗi dòng chứa bốn số nguyên $x\_1$, $y\_1$, $x\_2$ và $y\_2$: một đoạn thẳng bắt đầu tại điểm $(x\_1,y\_1)$ và kết thúc tại điểm $(x\_2,y\_2)$.

# Kết quả

In ra số lượng điểm giao nhau.

# Giới hạn

* $1 \le n \le 10^5$
* $-10^6 \le x\_1 \le x\_2 \le 10^6$
* $-10^6 \le y\_1 \le y\_2 \le 10^6$
* $(x\_1,y\_1) \neq (x\_2,y\_2)$

# Ví dụ

Dữ liệu vào:

```cpp
3
2 3 7 3
3 1 3 5
6 2 6 6
```

Kết quả:

```cpp
2
```
