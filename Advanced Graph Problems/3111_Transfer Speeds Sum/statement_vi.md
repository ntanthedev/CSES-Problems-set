# 3111 - Tổng Tốc Độ Truyền

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một mạng máy tính gồm $n$ máy tính và $n-1$ kết nối giữa hai máy tính. Thông tin có thể được trao đổi giữa mọi cặp máy tính thông qua các kết nối.

Mỗi kết nối có một tốc độ truyền nhất định. Gọi $d(a,b)$ là tốc độ truyền giữa máy tính $a$ và $b$, là tốc độ của kết nối chậm nhất trên đường đi giữa $a$ và $b$. Nhiệm vụ của bạn là tính tổng tốc độ truyền giữa tất cả các cặp máy tính.

## Dữ liệu vào

Dòng đầu tiên chứa số nguyên $n$: số lượng máy tính. Các máy tính được đánh số $1,2,\dots,n$.

Sau đó, có $n-1$ dòng mô tả các kết nối. Mỗi dòng chứa ba số nguyên $a$, $b$ và $x$: có một kết nối giữa máy tính $a$ và $b$ với tốc độ truyền $x$.

## Kết quả

In ra một số nguyên: tổng tốc độ truyền.

## Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x \le 10^6$

## Ví dụ

Dữ liệu vào:

```cpp
4
1 2 5
2 3 1
2 4 2
```

Kết quả:

```cpp
12
```

*Giải thích*: Hình dưới đây tương ứng với dữ liệu vào mẫu:
![](16b814426d2f0b3ccec778ce5c70779d0d400d53fd7a8b6c152803effe49c302)
Ở đây $d(1,2)=5$, $d(1,3)=1$, $d(1,4)=2$, $d(2,3)=1$, $d(2,4)=2$, và $d(3,4)=1$, do đó tổng tốc độ truyền là $12$.
