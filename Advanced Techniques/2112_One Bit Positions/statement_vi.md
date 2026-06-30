# 2112 - Các Vị Trí Bit 1

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một xâu nhị phân độ dài $n$. Nhiệm vụ của bạn là tính, với mỗi $k$ từ $1 \ldots n-1$, số cách chọn hai vị trí $i$ và $j$ sao cho $i-j=k$ và cả hai vị trí đều có bit 1.

# Dữ liệu vào

Dòng duy nhất chứa một xâu chỉ gồm các ký tự $0$ và $1$.

# Kết quả

Với mỗi khoảng cách $k$ từ $1 \ldots n-1$, in ra số cách chọn hai vị trí như vậy.

# Giới hạn

* $2 \le n \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
1001011010
```

Kết quả:

```cpp
1 2 3 0 2 1 0 1 0
```
