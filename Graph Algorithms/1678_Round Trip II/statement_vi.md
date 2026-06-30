# 1678 - Hành trình khứ hồi II

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Byteland có $n$ thành phố và $m$ kết nối bay. Nhiệm vụ của bạn là thiết kế một hành trình khứ hồi bắt đầu từ một thành phố, đi qua một hoặc nhiều thành phố khác, và cuối cùng quay trở lại thành phố xuất phát. Mỗi thành phố trung gian trên đường đi phải là khác nhau.

# Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$: số lượng thành phố và số lượng chuyến bay. Các thành phố được đánh số $1,2,\dots,n$.

Sau đó là $m$ dòng mô tả các chuyến bay. Mỗi dòng chứa hai số nguyên $a$ và $b$: có một kết nối bay từ thành phố $a$ đến thành phố $b$. Tất cả các kết nối đều là bay một chiều từ thành phố này đến thành phố khác.

# Kết quả

Đầu tiên in ra một số nguyên $k$: số lượng thành phố trên hành trình. Sau đó in ra $k$ thành phố theo thứ tự chúng sẽ được ghé thăm. Bạn có thể in ra bất kỳ phương án hợp lệ nào.

Nếu không có lời giải, in ra "IMPOSSIBLE".

# Giới hạn

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Ví dụ

Dữ liệu vào:

```cpp
4 5
1 3
2 1
2 4
3 2
3 4
```

Kết quả:

```cpp
4
2 1 3 2
```
