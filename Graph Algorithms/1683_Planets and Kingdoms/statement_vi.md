# 1683 - Các hành tinh và vương quốc

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một trò chơi có $n$ hành tinh, được kết nối bởi $m$ cổng dịch chuyển. Hai hành tinh $a$ và $b$ thuộc cùng một vương quốc khi và chỉ khi có đường đi cả từ $a$ đến $b$ và từ $b$ đến $a$. Nhiệm vụ của bạn là xác định vương quốc cho mỗi hành tinh.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng hành tinh và cổng dịch chuyển. Các hành tinh được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các cổng dịch chuyển. Mỗi dòng chứa hai số nguyên $a$ và $b$: bạn có thể đi từ hành tinh $a$ đến hành tinh $b$ qua một cổng dịch chuyển.

# Kết quả

Đầu tiên, in ra một số nguyên $k$: số lượng vương quốc. Sau đó, in ra cho mỗi hành tinh một nhãn vương quốc từ $1$ đến $k$. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 6
1 2
2 3
3 1
3 4
4 5
5 4
```

Kết quả:

```cpp
2
1 1 1 2 2
```
