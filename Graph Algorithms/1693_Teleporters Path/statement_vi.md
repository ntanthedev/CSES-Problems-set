# 1693 - Đường đi của các Cổng dịch chuyển

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một trò chơi có $n$ màn chơi và $m$ cổng dịch chuyển giữa chúng. Bạn thắng trò chơi nếu bạn đi từ màn $1$ đến màn $n$ sử dụng mỗi cổng dịch chuyển đúng một lần.

Bạn có thể thắng trò chơi không, và một cách chơi khả dĩ là gì?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng màn chơi và cổng dịch chuyển. Các màn chơi được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các cổng dịch chuyển. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một cổng dịch chuyển từ màn $a$ đến màn $b$.

Bạn có thể giả sử mỗi cặp $(a,b)$ trong dữ liệu vào là phân biệt.

# Kết quả

In ra $m+1$ số nguyên: thứ tự các màn chơi bạn đi qua trong trò chơi. Bạn có thể in ra bất kỳ nghiệm đúng nào.

Nếu không có nghiệm, in ra "IMPOSSIBLE".

# Giới hạn

* $2 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 6
1 2
1 3
2 4
2 5
3 1
4 2
```

Kết quả:

```cpp
1 3 1 2 4 2 5
```
