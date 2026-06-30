# 2077 - Necessary Cities

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ con đường giữa chúng. Có đường đi giữa mọi cặp thành phố.

Một thành phố được gọi là *cần thiết* (necessary) nếu sau khi xóa thành phố đó (và các con đường kề với nó), không còn đường đi giữa hai thành phố khác nào đó. Nhiệm vụ của bạn là tìm tất cả các thành phố cần thiết.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và con đường. Các thành phố được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các con đường. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một con đường giữa thành phố $a$ và $b$. Có tối đa một con đường giữa hai thành phố, và mỗi con đường nối hai thành phố phân biệt.

# Kết quả

Đầu tiên in ra một số nguyên $k$: số lượng thành phố cần thiết. Sau đó, in ra danh sách $k$ thành phố. Bạn có thể in các thành phố theo thứ tự bất kỳ.

# Giới hạn

* $2 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 5
1 2
1 4
2 4
3 5
4 5
```

Kết quả:

```cpp
2
4 5
```
