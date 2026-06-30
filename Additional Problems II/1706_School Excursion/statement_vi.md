# 1706 - Chuyến tham quan của trường

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Một nhóm gồm $n$ đứa trẻ đến Helsinki. Có hai điểm tham quan: một đứa trẻ có thể đến thăm Korkeasaari (vườn thú) hoặc Linnanmäki (công viên giải trí).

Có $m$ cặp đứa trẻ muốn đến thăm cùng một điểm tham quan. Nhiệm vụ của bạn là tìm tất cả các khả năng khác nhau cho số lượng đứa trẻ sẽ đến thăm Korkeasaari. Mong muốn của các đứa trẻ phải được tính đến.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng đứa trẻ và số lượng mong muốn của chúng. Các đứa trẻ được đánh số $1,2,\dots,n$.

Sau đó, có $m$ dòng mô tả mong muốn của các đứa trẻ. Mỗi dòng chứa hai số nguyên $a$ và $b$: đứa trẻ $a$ và $b$ muốn đến thăm cùng một điểm tham quan.

# Kết quả

In ra một xâu bit độ dài $n$ mà bit 1 tại vị trí $i$ cho biết có thể có chính xác $i$ đứa trẻ đến thăm Korkeasaari (xâu bit được đánh chỉ số bắt đầu từ 1).

# Giới hạn

* $1 \le n \le 10^5$
* $0 \le m \le 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
1 2
2 3
1 5
```

Kết quả:

```cpp
10011
```

*Giải thích*: Số lượng đứa trẻ đến thăm Korkeasaari có thể là $1$, $4$ hoặc $5$.
