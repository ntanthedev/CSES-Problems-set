# 2425 - Trọng số Chồng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Bạn có $n$ đồng xu, mỗi đồng xu có trọng lượng phân biệt.

Có hai chồng, ban đầu đều rỗng. Ở mỗi bước, bạn di chuyển một đồng xu vào một chồng. Bạn không bao giờ lấy đồng xu ra khỏi chồng.

Sau mỗi bước di chuyển, nhiệm vụ của bạn là xác định chồng nào nặng hơn (nếu ta có thể chắc chắn rằng một chồng nặng hơn).

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng đồng xu. Các đồng xu được đánh số $1,2,\dots,n$. Bạn biết rằng đồng xu $i$ luôn nặng hơn đồng xu $i-1$, nhưng bạn không biết trọng lượng chính xác của chúng.

Sau đó, có $n$ dòng mô tả các bước di chuyển. Mỗi dòng chứa hai số nguyên $c$ và $s$: di chuyển đồng xu $c$ vào chồng $s$ (1 = trái, 2 = phải).

# Kết quả

Sau mỗi bước di chuyển, in ra `<` nếu chồng phải nặng hơn, `>` nếu chồng trái nặng hơn, và `?` nếu ta không thể biết chồng nào nặng hơn.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$

# Ví dụ

Dữ liệu vào:

```cpp
3
2 1
3 2
1 1
```

Kết quả:

```cpp
>
<
?
```

Giải thích: Sau bước di chuyển cuối cùng, nếu các đồng xu là $[2,3,4]$, chồng trái nặng hơn, nhưng nếu các đồng xu là $[1,2,5]$, chồng phải nặng hơn.
