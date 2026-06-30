# 1698 - Swap Round Sorting

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng chứa hoán vị của các số $1,2,\dots,n$, nhiệm vụ của bạn là sắp xếp mảng bằng cách sử dụng các *vòng đổi chỗ*. Trong mỗi vòng đổi chỗ, bạn có thể chọn bất kỳ số lượng cặp phần tử phân biệt nào và đổi chỗ mỗi cặp.

Nhiệm vụ của bạn là tìm số vòng tối thiểu và chỉ ra cách chọn các cặp trong mỗi vòng.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng.

Dòng thứ hai chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: hoán vị ban đầu.

# Kết quả

Đầu tiên, in ra một số nguyên $k$: số vòng tối thiểu.

Sau đó, với mỗi vòng, in ra số lượng phép đổi chỗ và các chỉ số của mỗi phép đổi chỗ. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
5
5 2 1 3 4
```

Kết quả:

```cpp
2
2
1 3
4 5
1
3 5
```

*Giải thích*: Mảng ban đầu là $[5,2,1,3,4]$. Sau vòng $1$, mảng trở thành $[1,2,5,4,3]$. Sau vòng $2$, mảng trở thành $[1,2,3,4,5]$.
