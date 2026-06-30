# 2195 - Bao lồi

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một tập hợp gồm $n$ điểm trên mặt phẳng hai chiều, nhiệm vụ của bạn là xác định bao lồi của các điểm.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng điểm.

Sau đó là $n$ dòng mô tả các điểm. Mỗi dòng chứa hai số nguyên $x$ và $y$: tọa độ của một điểm.

Bạn có thể giả sử các điểm đều phân biệt và diện tích của bao lồi là dương.

# Kết quả

Đầu tiên in ra số nguyên $k$: số lượng điểm trên bao lồi.

Sau đó, in ra $k$ dòng mô tả các điểm. Bạn có thể in các điểm theo thứ tự bất kỳ. In ra tất cả các điểm nằm trên bao lồi.

# Giới hạn

* $3 \le n \le 2 \cdot 10^5$
* $-10^9 \le x, y \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
6
2 1
2 5
3 3
4 3
4 4
6 3
```

Kết quả:

```cpp
4
2 1
2 5
4 4
6 3
```
