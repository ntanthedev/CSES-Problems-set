# 1695 - Cuộc rượt đuổi của Cảnh sát

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Kaaleppi vừa cướp một ngân hàng và đang trên đường đến bến cảng. Tuy nhiên, cảnh sát muốn chặn anh ta bằng cách phong tỏa một số con đường trong thành phố.

Hỏi số lượng con đường tối thiểu cần phong tỏa để không còn đường đi nào giữa ngân hàng và bến cảng?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng giao lộ và con đường. Các giao lộ được đánh số $1,2,\dots,n$. Ngân hàng ở giao lộ $1$, và bến cảng ở giao lộ $n$.

Sau đó, có $m$ dòng mô tả các con đường. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một con đường giữa giao lộ $a$ và $b$. Tất cả các con đường đều là đường hai chiều, và có tối đa một con đường giữa hai giao lộ.

# Kết quả

Đầu tiên in ra một số nguyên $k$: số lượng con đường tối thiểu cần phong tỏa. Sau đó, in ra $k$ dòng mô tả các con đường đó. Bạn có thể in ra bất kỳ nghiệm đúng nào.

# Giới hạn

* $2 \le n \le 500$
* $1 \le m \le 1000$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 2
1 3
2 3
3 4
1 4
```

Kết quả:

```cpp
2
3 4
1 4
```
