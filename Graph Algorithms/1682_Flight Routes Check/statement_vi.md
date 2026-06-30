# 1682 - Kiểm tra các tuyến bay

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ kết nối bay. Nhiệm vụ của bạn là kiểm tra xem bạn có thể di chuyển từ bất kỳ thành phố nào đến bất kỳ thành phố nào khác bằng các chuyến bay hiện có hay không.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và số chuyến bay. Các thành phố được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các chuyến bay. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một chuyến bay từ thành phố $a$ đến thành phố $b$. Tất cả các chuyến bay đều là một chiều.

# Kết quả

In ra "YES" nếu tất cả các đường đi đều khả thi, và "NO" nếu ngược lại. Trong trường hợp sau, cũng in ra hai thành phố $a$ và $b$ sao cho bạn không thể đi từ thành phố $a$ đến thành phố $b$. Nếu có nhiều phương án, bạn có thể in ra bất kỳ phương án nào.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 2
2 3
3 1
1 4
3 4
```

Kết quả:

```cpp
NO
4 2
```
