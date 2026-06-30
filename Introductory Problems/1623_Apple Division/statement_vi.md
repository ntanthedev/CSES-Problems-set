# 1623 - Chia táo

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ quả táo với khối lượng đã biết. Nhiệm vụ của bạn là chia số táo thành hai nhóm sao cho chênh lệch khối lượng giữa hai nhóm là nhỏ nhất.

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng quả táo.

Dòng tiếp theo chứa $n$ số nguyên $p_1,p_2,\dots,p_n$: khối lượng của mỗi quả táo.

# Kết quả

In ra một số nguyên: chênh lệch nhỏ nhất giữa khối lượng của hai nhóm.

# Giới hạn

* $1 \le n \le 20$
* $1 \le p_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
5
3 2 7 4 1
```

Kết quả:

```cpp
1
```

Giải thích: Nhóm 1 có khối lượng 2, 3 và 4 (tổng khối lượng 9), nhóm 2 có khối lượng 1 và 7 (tổng khối lượng 8).
