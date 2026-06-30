# 2432 - Grid Puzzle I

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một lưới $n \times n$, nhiệm vụ của bạn là chọn từ mỗi hàng và mỗi cột một số ô vuông nhất định. Làm thế nào để làm được điều đó?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của lưới. Các hàng và cột được đánh số $1,2,\dots,n$.

Dòng tiếp theo chứa $n$ số nguyên $a\_1,a\_2,\ldots,a\_n$: Bạn phải chọn đúng $a\_i$ ô vuông từ hàng thứ $i$.

Dòng cuối cùng chứa $n$ số nguyên $b\_1,b\_2,\ldots,b\_n$: Bạn phải chọn đúng $b\_j$ ô vuông từ cột thứ $j$.

# Kết quả

In ra $n$ dòng mô tả các ô vuông bạn chọn (`X` nghĩa là bạn chọn ô vuông đó, `.` nghĩa là bạn không chọn nó). Bạn có thể in ra bất kỳ phương án hợp lệ nào.

Nếu không thể thỏa mãn các điều kiện, chỉ cần in ra $-1$.

# Giới hạn

* $1 \le n \le 50$
* $0 \le a\_i \le n$
* $0 \le b\_j \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5
0 1 3 2 0
1 2 2 0 1
```

Kết quả:

```cpp
.....
..X..
.XX.X
XX...
.....
```
