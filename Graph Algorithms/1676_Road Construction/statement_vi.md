# 1676 - Xây dựng đường giao thông

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ thành phố và ban đầu không có con đường nào giữa chúng. Tuy nhiên, mỗi ngày một con đường mới sẽ được xây dựng, và tổng cộng sẽ có $m$ con đường.

Một thành phần liên thông là một nhóm các thành phố mà có đường đi giữa hai thành phố bất kỳ trong nhóm sử dụng các con đường đã có. Sau mỗi ngày, nhiệm vụ của bạn là tìm số lượng thành phần liên thông và kích thước của thành phần liên thông lớn nhất.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và số lượng con đường. Các thành phố được đánh số $1,2,\dots,n$.

Sau đó là $m$ dòng mô tả các con đường mới. Mỗi dòng chứa hai số nguyên $a$ và $b$: một con đường mới được xây dựng giữa thành phố $a$ và $b$.

Bạn có thể giả định rằng mỗi con đường sẽ được xây dựng giữa hai thành phố khác nhau.

# Kết quả

In ra $m$ dòng: thông tin yêu cầu sau mỗi ngày.

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
5 3
1 2
1 3
4 5
```

Kết quả:

```cpp
4 2
3 3
2 3
```
