# 1143 - Hotel Queries

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ khách sạn trên một con phố. Với mỗi khách sạn, bạn biết số phòng trống. Nhiệm vụ của bạn là xếp phòng khách sạn cho các đoàn khách du lịch. Tất cả thành viên của một đoàn muốn ở cùng một khách sạn.

Các đoàn khách sẽ đến lần lượt, và bạn biết số phòng mỗi đoàn yêu cầu. Bạn luôn xếp một đoàn vào khách sạn đầu tiên có đủ phòng. Sau đó, số phòng trống của khách sạn đó giảm đi.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng khách sạn và số lượng đoàn khách. Các khách sạn được đánh số $1,2,\ldots,n$.

Dòng tiếp theo chứa $n$ số nguyên $h\_1,h\_2,\ldots,h\_n$: số phòng trống trong mỗi khách sạn.

Dòng cuối cùng chứa $m$ số nguyên $r\_1,r\_2,\ldots,r\_m$: số phòng mỗi đoàn khách yêu cầu.

# Kết quả

In ra khách sạn được xếp cho mỗi đoàn khách. Nếu không thể xếp khách sạn cho một đoàn, in ra 0.

# Giới hạn

* $1 \le n,m \le 2 \cdot 10^5$
* $1 \le h\_i \le 10^9$
* $1 \le r\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
8 5
3 2 4 1 5 5 2 6
4 4 7 1 1
```

Kết quả:

```cpp
3 5 0 1 1
```
