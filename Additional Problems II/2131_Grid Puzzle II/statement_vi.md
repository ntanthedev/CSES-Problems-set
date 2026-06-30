# 2131 - Câu đố lưới II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một lưới $n \times n$ mà mỗi ô vuông chứa một số lượng đồng xu nhất định.

Bạn biết với mỗi hàng và mỗi cột cần phải chọn bao nhiêu ô vuông từ hàng hoặc cột đó. Bạn nhận được tất cả các đồng xu từ mỗi ô vuông bạn chọn. Hỏi số lượng đồng xu tối đa bạn có thể thu thập được là bao nhiêu và bạn nên chọn các ô vuông như thế nào để thỏa mãn các điều kiện đã cho?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: kích thước của lưới. Các hàng và cột được đánh số $1,2,\dots,n$.

Dòng tiếp theo chứa $n$ số nguyên $a\_1,a\_2,\ldots,a\_n$: Bạn phải chọn chính xác $a\_i$ ô vuông từ hàng thứ $i$.

Dòng tiếp theo chứa $n$ số nguyên $b\_1,b\_2,\ldots,b\_n$: Bạn phải chọn chính xác $b\_j$ ô vuông từ cột thứ $j$.

Cuối cùng, có $n$ dòng mô tả lưới. Bạn có thể giả sử rằng tổng của $a\_1,a\_2,\ldots,a\_n$ và $b\_1,b\_2,\ldots,b\_n$ là bằng nhau.

# Kết quả

Đầu tiên in ra một số nguyên $k$: số lượng đồng xu tối đa bạn có thể thu thập được. Sau đó in ra $n$ dòng mô tả các ô vuông bạn chọn (`X` nghĩa là bạn chọn ô vuông đó, `.` nghĩa là bạn không chọn nó).

Nếu không thể thỏa mãn các điều kiện, chỉ in ra $-1$.

# Giới hạn

* $1 \le n \le 50$
* $0 \le a\_i \le n$
* $0 \le b\_j \le n$
* $0 \le c\_{ij} \le 1000$

# Ví dụ

Dữ liệu vào:

```cpp
5
0 1 3 2 0
1 2 2 0 1
2 5 1 5 1
0 2 5 1 2
3 8 9 3 5
1 4 3 7 3
0 3 6 2 8
```

Kết quả:

```cpp
32
.....
..X..
.XX.X
XX...
.....
```
