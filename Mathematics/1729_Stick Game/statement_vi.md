# 1729 - Stick Game

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Xét một trò chơi trong đó hai người chơi lấy que từ một đống. Hai người chơi thay phiên nhau, và người lấy que cuối cùng sẽ thắng cuộc.

Một tập $P=\{p\_1,p\_2,\ldots,p\_k\}$ xác định các nước đi được phép. Ví dụ, nếu $P=\{1,3,4\}$, người chơi có thể lấy $1$, $3$ hoặc $4$ que.

Nhiệm vụ của bạn là xác định với mỗi số lượng que $1,2,\dots,n$ xem người chơi đầu tiên có thắng hay thua.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: số lượng que và số nước đi.

Dòng tiếp theo chứa $k$ số nguyên $p\_1,p\_2,\dots,p\_k$ mô tả các nước đi được phép. Tất cả các số đều phân biệt, và một trong số chúng là $1$.

# Kết quả

In ra một xâu gồm $n$ ký tự: `W` nghĩa là vị thế thắng, và `L` nghĩa là vị thế thua.

# Giới hạn

* $1 \le n \le 10^6$
* $1 \le k \le 100$
* $1 \le p\_i \le n$

# Ví dụ

Dữ liệu vào:

```cpp
10 3
1 3 4
```

Kết quả:

```cpp
WLWWWWLWLW
```
