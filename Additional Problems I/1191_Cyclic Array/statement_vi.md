# 1191 - Mảng Vòng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Cho một mảng vòng gồm $n$ giá trị. Mỗi phần tử có hai láng giềng; các phần tử ở vị trí $n$ và $1$ cũng được coi là láng giềng.

Nhiệm vụ của bạn là chia mảng thành các đoạn con sao cho tổng của mỗi đoạn con không vượt quá $k$. Hỏi số lượng đoạn con tối thiểu là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$.

Dòng tiếp theo chứa $n$ số nguyên $x\_1,x\_2,\ldots,x\_n$: nội dung của mảng.

Luôn tồn tại ít nhất một cách chia (tức là không có giá trị nào trong mảng lớn hơn $k$).

# Kết quả

In ra một số nguyên: số lượng đoạn con tối thiểu.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x\_i \le 10^9$
* $1 \le k \le 10^{18}$

# Ví dụ

Dữ liệu vào:

```cpp
8 5
2 2 2 1 3 1 2 1
```

Kết quả:

```cpp
3
```

*Giải thích*: Ta có thể tạo ba đoạn con: $[2,2,1]$, $[3,1]$, và $[2,1,2]$ (nhớ rằng mảng là mảng vòng).
