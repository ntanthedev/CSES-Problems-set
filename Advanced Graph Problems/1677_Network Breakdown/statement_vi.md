# 1677 - Sự Cố Mạng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Mạng của Syrjälä có $n$ máy tính và $m$ kết nối giữa chúng. Mạng bao gồm các thành phần gồm các máy tính có thể gửi tin nhắn cho nhau.

Không ai ở Syrjälä hiểu cách mạng hoạt động. Vì lý do này, nếu một kết nối bị hỏng, không ai sẽ sửa nó. Trong tình huống này, một thành phần có thể bị chia thành hai thành phần.

Nhiệm vụ của bạn là tính số lượng thành phần sau mỗi lần kết nối bị hỏng.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $k$: số lượng máy tính, kết nối và sự cố. Các máy tính được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả các kết nối. Mỗi dòng có hai số nguyên $a$ và $b$: có một kết nối giữa máy tính $a$ và máy tính $b$. Mỗi kết nối là giữa hai máy tính khác nhau, và có tối đa một kết nối giữa hai máy tính.

Cuối cùng, có $k$ dòng mô tả các sự cố. Mỗi dòng có hai số nguyên $a$ và $b$: kết nối giữa máy tính $a$ và máy tính $b$ bị hỏng.

# Kết quả

Sau mỗi sự cố, in ra số lượng thành phần.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le k \le m$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 5 3
1 2
1 3
2 3
3 4
4 5
3 4
2 3
4 5
```

Kết quả:

```cpp
2 2 3
```
