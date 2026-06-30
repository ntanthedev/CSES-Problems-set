# 2402 - Two Stacks Sorting

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một danh sách đầu vào gồm $n$ số. Mỗi số nguyên từ $1$ đến $n$ xuất hiện đúng một lần trong danh sách.

Nhiệm vụ của bạn là tạo một danh sách đầu ra đã được sắp xếp bằng cách sử dụng hai ngăn xếp. Mỗi lượt, bạn có thể thực hiện một trong các thao tác sau:

* Di chuyển số đầu tiên từ danh sách đầu vào vào một ngăn xếp
* Di chuyển một số từ một ngăn xếp đến cuối danh sách đầu ra

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$.

Dòng thứ hai chứa $n$ số nguyên: nội dung của danh sách đầu vào.

# Kết quả

In ra $n$ số nguyên: với mỗi số, in ra ngăn xếp mà nó được di chuyển vào ($1$ hoặc $2$).

Bạn có thể in ra bất kỳ phương án hợp lệ nào. Nếu không có phương án nào, in ra `IMPOSSIBLE`.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
5
2 3 1 5 4
```

Kết quả:

```cpp
1 2 1 1 2
```
