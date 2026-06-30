# 3216 - Chu trình của Bóng nảy

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có một quả bóng ở góc trên bên trái của một lưới $n \times m$. Các hàng của lưới được đánh số $1,2,\dots,n$, và các cột được đánh số $1,2,\dots,m$.

Ban đầu quả bóng di chuyển theo đường chéo ra xa khỏi góc trên bên trái. Mỗi bước, nó di chuyển một ô. Bất cứ khi nào bóng chạm vào biên của lưới, nó đổi hướng.

Sau bao nhiêu bước thì quả bóng trở lại vị trí ban đầu? Số ô phân biệt mà nó đã đi qua là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa số nguyên $t$: số lượng bộ test.

Sau đó là $t$ dòng. Mỗi dòng chứa hai số nguyên $n$, $m$: kích thước của lưới.

# Kết quả

Với mỗi bộ test, in ra hai số nguyên: số bước di chuyển và số ô đã đi qua.

# Giới hạn

* $1 \le t \le 1000$
* $2 \le n,m \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
4
3 4
2 2
19 18
42 1337
```

Kết quả:

```cpp
12 6
2 2
612 171
109552 28077
```
