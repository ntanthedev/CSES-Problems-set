# 2075 - Sắp xếp bằng đảo đoạn

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn có một mảng chứa một hoán vị của các số nguyên $1,2,\dots,n$. Nhiệm vụ của bạn là sắp xếp mảng theo thứ tự tăng dần bằng cách đảo ngược các đoạn con. Bạn có thể xây dựng bất kỳ phương án nào có tối đa $n$ lần đảo ngược.

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của mảng. Các phần tử của mảng được đánh số $1,2,\dots,n$.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\dots,x\_n$: nội dung của mảng.

# Kết quả

Đầu tiên in ra một số nguyên $k$: số lần đảo ngược.

Sau đó, in ra $k$ dòng mô tả các lần đảo ngược. Mỗi dòng chứa hai số nguyên $a$ và $b$: bạn đảo ngược đoạn con từ vị trí $a$ đến vị trí $b$.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
4
2 3 1 4
```

Kết quả:

```cpp
2
1 3
2 3
```
