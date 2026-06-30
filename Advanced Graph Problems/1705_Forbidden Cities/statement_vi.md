# 1705 - Thành Phố Cấm

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ con đường giữa chúng. Kaaleppi hiện đang ở thành phố $a$ và muốn đi đến thành phố $b$.

Tuy nhiên, có một vấn đề: Kaaleppi vừa cướp một ngân hàng ở thành phố $c$ và không thể vào thành phố đó, vì cảnh sát địa phương sẽ bắt anh ta. Nhiệm vụ của bạn là xác định xem có đường đi nào từ thành phố $a$ đến thành phố $b$ mà không đi qua thành phố $c$ hay không.

Như một thử thách bổ sung, bạn phải xử lý $q$ truy vấn với $a$, $b$ và $c$ thay đổi.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $n$, $m$ và $q$: số lượng thành phố, con đường và truy vấn. Các thành phố được đánh số $1,2,\dots,n$.

Sau đó là $m$ dòng mô tả các con đường. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một con đường giữa thành phố $a$ và $b$. Mỗi con đường là hai chiều.

Cuối cùng là $q$ dòng mô tả các truy vấn. Mỗi dòng chứa ba số nguyên $a$, $b$ và $c$: có đường đi từ thành phố $a$ đến thành phố $b$ mà không đi qua thành phố $c$ hay không?

Bạn có thể giả định rằng có đường đi giữa mọi cặp thành phố.

# Kết quả

Với mỗi truy vấn, in "YES" nếu có đường đi như vậy, và "NO" nếu ngược lại.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le q \le 10^5$
* $1 \le a,b,c \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 6 3
1 2
1 3
2 3
2 4
3 4
4 5
1 4 2
3 5 4
3 5 2
```

Kết quả:

```cpp
YES
NO
YES
```
