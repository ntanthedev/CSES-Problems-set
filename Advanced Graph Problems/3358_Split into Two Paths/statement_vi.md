# 3358 - Chia Thành Hai Đường Đi

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một đồ thị có hướng không chu trình gồm $n$ đỉnh và $m$ cạnh.

Hãy xác định xem có thể tạo thành hai đường đi trong đồ thị sao cho mỗi đỉnh của đồ thị xuất hiện trong đúng một trong hai đường đi hay không. Lưu ý rằng không nhất thiết tất cả các cạnh của đồ thị phải xuất hiện trong các đường đi.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đỉnh và số lượng cạnh. Các đỉnh được đánh số $1, 2, \dots, n$.

Sau đó, có $m$ dòng mô tả các cạnh.
Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cạnh trong đồ thị từ đỉnh $a$ đến đỉnh $b$.

# Kết quả

Đầu tiên, in ra dòng `YES` nếu có thể tạo thành các đường đi, hoặc `NO` nếu không thể.

Nếu có thể tạo thành các đường đi, in ra chúng trên hai dòng tiếp theo.

Ở đầu mỗi dòng, in ra số lượng đỉnh trong đường đi và sau đó là các đỉnh của đường đi theo thứ tự. Phải có một cạnh trong đồ thị giữa các đỉnh liên tiếp. Một trong hai đường đi có thể không chứa đỉnh nào.

Nếu có nhiều phương án, bạn có thể in ra bất kỳ phương án nào.

# Giới hạn

* $2 \le n \le 2\cdot10^5$
* $0 \le m \le 5\cdot 10^5$

# Ví dụ 1

Dữ liệu vào:

```cpp
5 4
1 2
1 4
3 4
4 5
```

Kết quả:

```cpp
YES
2 1 2
3 3 4 5
```

# Ví dụ 2

Dữ liệu vào:

```cpp
5 4
1 2
1 3
1 4
1 5
```

Kết quả:

```cpp
NO
```
