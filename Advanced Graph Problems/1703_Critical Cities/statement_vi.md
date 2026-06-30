# 1703 - Thành Phố Quan Trọng

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và $m$ đường bay kết nối giữa chúng. Một thành phố được gọi là *thành phố quan trọng* nếu nó nằm trên mọi đường đi từ một thành phố này đến một thành phố khác.

Nhiệm vụ của bạn là tìm tất cả các thành phố quan trọng từ Syrjälä đến Lehmälä.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và đường bay. Các thành phố được đánh số $1,2,\dots,n$. Thành phố $1$ là Syrjälä, và thành phố $n$ là Lehmälä.

Sau đó là $m$ dòng mô tả các đường bay. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một đường bay từ thành phố $a$ đến thành phố $b$. Tất cả các đường bay đều là một chiều.

Bạn có thể giả định rằng có một đường đi từ Syrjälä đến Lehmälä.

# Kết quả

Đầu tiên in một số nguyên $k$: số lượng thành phố quan trọng. Sau đó, in $k$ số nguyên: các thành phố quan trọng theo thứ tự tăng dần.

# Giới hạn

* $2 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 5
1 2
2 3
2 4
3 5
4 5
```

Kết quả:

```cpp
3
1 2 5
```
