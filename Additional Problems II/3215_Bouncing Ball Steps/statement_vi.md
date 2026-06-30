# 3215 - Bước đi của Bóng nảy

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một quả bóng ở góc trên bên trái của một lưới $n \times m$. Các hàng của lưới được đánh số $1,2,\dots,n$, và các cột được đánh số $1,2,\dots,m$.

Ban đầu quả bóng di chuyển theo đường chéo ra xa khỏi góc trên bên trái. Mỗi bước, nó di chuyển một ô. Bất cứ khi nào bóng chạm vào biên của lưới, nó đổi hướng.

Vị trí của quả bóng sau $k$ bước là ở đâu và nó đã đổi hướng bao nhiêu lần?

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $t$: số lượng bộ test.

Sau đó là $t$ dòng. Mỗi dòng chứa ba số nguyên $n$, $m$ và $k$: kích thước lưới và số bước di chuyển.

# Kết quả

Với mỗi bộ test, in ra ba số nguyên: vị trí của quả bóng và số lần đổi hướng.

# Giới hạn

* $1 \le t \le 1000$
* $2 \le n,m \le 10^9$
* $0 \le k \le 10^{18}$

# Ví dụ

Dữ liệu vào:

```cpp
6
3 4 0
3 4 1
3 4 2
3 4 3
3 4 4
42 1337 123456789
```

Kết quả:

```cpp
1 1 0
2 2 0
3 3 1
2 4 2
1 3 3
34 300 3101295
```
