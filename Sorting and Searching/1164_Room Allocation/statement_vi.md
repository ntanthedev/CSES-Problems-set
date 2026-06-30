# 1164 - Phân Phòng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một khách sạn lớn, và $n$ khách hàng sẽ đến sớm. Mỗi khách hàng muốn có một phòng đơn.

Bạn biết ngày đến và ngày đi của mỗi khách hàng. Hai khách hàng có thể ở cùng một phòng nếu ngày đi của khách hàng đầu tiên sớm hơn ngày đến của khách hàng thứ hai.

Hỏi số lượng phòng tối thiểu cần thiết để phục vụ tất cả khách hàng là bao nhiêu? Và có thể phân phòng như thế nào?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng khách hàng.

Sau đó là $n$ dòng, mỗi dòng mô tả một khách hàng. Mỗi dòng chứa hai số nguyên $a$ và $b$: ngày đến và ngày đi.

# Kết quả

In ra đầu tiên một số nguyên $k$: số phòng tối thiểu cần thiết.

Sau đó, in ra một dòng chứa số phòng của mỗi khách hàng theo đúng thứ tự trong dữ liệu vào. Các phòng được đánh số $1,2,\ldots,k$. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a \le b \le 10^9$

# Ví dụ

Input:

```cpp
3
1 2
2 4
4 4
```

Output:

```cpp
2
1 2 1
```
