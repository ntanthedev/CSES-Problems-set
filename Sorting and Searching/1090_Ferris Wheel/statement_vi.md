# 1090 - Ferris Wheel

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ đứa trẻ muốn đi vòng quay ngựa gỗ, và nhiệm vụ của bạn là tìm một gondola cho mỗi đứa trẻ.

Mỗi gondola có thể chứa một hoặc hai đứa trẻ, và ngoài ra, tổng trọng lượng trong một gondola không được vượt quá $x$. Bạn biết trọng lượng của mỗi đứa trẻ.

Hỏi số lượng gondola tối thiểu cần dùng cho các đứa trẻ là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $x$: số lượng đứa trẻ và trọng lượng tối đa cho phép.

Dòng tiếp theo chứa $n$ số nguyên $p\_1,p\_2,\ldots,p\_n$: trọng lượng của mỗi đứa trẻ.

# Kết quả

In ra một số nguyên: số lượng gondola tối thiểu.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x \le 10^9$
* $1 \le p\_i \le x$

# Ví dụ

Dữ liệu vào:

```cpp
4 10
7 2 3 9
```

Kết quả:

```cpp
3
```
