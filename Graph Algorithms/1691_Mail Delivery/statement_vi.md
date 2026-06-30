# 1691 - Phát thư

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Nhiệm vụ của bạn là phát thư cho các cư dân của một thành phố. Vì lý do này, bạn muốn tìm một tuyến đường có điểm bắt đầu và kết thúc là bưu điện, và đi qua mỗi con phố đúng một lần.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng ngã tư và số con phố. Các ngã tư được đánh số $1,\,2,\ldots,\,n$, và bưu điện nằm ở ngã tư $1$.

Sau đó, có m dòng mô tả các con phố. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một con phố giữa ngã tư $a$ và $b$. Tất cả các con phố đều là đường hai chiều.

Mỗi con phố nối giữa hai ngã tư khác nhau và có nhiều nhất một con phố giữa hai ngã tư bất kỳ.

# Kết quả

In ra tất cả các ngã tư trên tuyến đường theo thứ tự bạn sẽ ghé thăm chúng. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

Nếu không có lời giải, in ra "IMPOSSIBLE".

# Giới hạn

$2\leq n\leq 10^5$  
$1\leq m\leq 2 \cdot 10^5$  
$1\leq a,\,b\leq n$

# Ví dụ

Dữ liệu vào:

```cpp
6 8
1 2
1 3
2 3
2 4
2 6
3 5
3 6
4 5
```

Kết quả:

```cpp
1 2 6 3 2 4 5 3 1
```
