# 2087 - Houses and Schools

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ ngôi nhà trên một con đường, được đánh số $1,2,\dots,n$. Khoảng cách giữa hai ngôi nhà $a$ và $b$ là $|a-b|$. Bạn biết số lượng trẻ em trong mỗi ngôi nhà.

Nhiệm vụ của bạn là thành lập $k$ trường học sao cho mỗi trường học nằm tại một ngôi nhà nào đó. Sau đó, mỗi đứa trẻ sẽ đến trường học gần nhất. Tổng khoảng cách đi lại tối thiểu của các đứa trẻ nếu bạn hành động tối ưu là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $k$: số lượng ngôi nhà và số lượng trường học. Các ngôi nhà được đánh số $1,2\dots,n$.

Sau đó là $n$ số nguyên $c\_1,c\_2,\dots,c\_n$: số lượng trẻ em trong mỗi ngôi nhà.

# Kết quả

In ra tổng khoảng cách tối thiểu.

# Giới hạn

* $1 \le k \le n \le 3000$
* $1 \le c\_i \le 10^9$

# Ví dụ

Dữ liệu vào:

```cpp
6 2
2 7 1 4 6 4
```

Kết quả:

```cpp
11
```

Giải thích: Các ngôi nhà 2 và 5 sẽ có trường học.
