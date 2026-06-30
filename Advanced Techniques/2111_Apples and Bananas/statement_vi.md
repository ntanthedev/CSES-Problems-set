# 2111 - Apples and Bananas

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ quả táo và $m$ quả chuối, mỗi quả có một trọng lượng nguyên từ $1 \ldots k$. Nhiệm vụ của bạn là tính, với mỗi trọng lượng $w$ từ $2 \dots 2k$, số cách chọn một quả táo và một quả chuối sao cho tổng trọng lượng của chúng là $w$.

# Dữ liệu vào

Dòng đầu tiên chứa ba số nguyên $k$, $n$ và $m$: số $k$, số lượng táo và số lượng chuối.

Dòng tiếp theo chứa $n$ số nguyên $a\_1,a\_2,\ldots,a\_n$: trọng lượng của mỗi quả táo.

Dòng cuối cùng chứa $m$ số nguyên $b\_1,b\_2,\ldots,b\_m$: trọng lượng của mỗi quả chuối.

# Kết quả

Với mỗi số nguyên $w$ từ $2 \ldots 2k$, in ra số cách chọn một quả táo và một quả chuối sao cho tổng trọng lượng của chúng là $w$.

# Giới hạn

* $1 \le k,n,m \le 2 \cdot 10^5$
* $1 \le a\_i \le k$
* $1 \le b\_i \le k$

# Ví dụ

Dữ liệu vào:

```cpp
5 3 4
5 2 5
4 3 2 3
```

Kết quả:

```cpp
0 0 1 2 1 2 4 2 0
```

Giải thích: Ví dụ với $w = 8$ có $4$ cách khác nhau: ta có thể chọn một quả táo trọng lượng $5$ theo hai cách khác nhau và một quả chuối trọng lượng $3$ theo hai cách khác nhau.
