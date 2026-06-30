# 1726 - Moving Robots

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Mỗi ô của một bàn cờ $8 \times 8$ có một robot. Mỗi robot di chuyển độc lập $k$ bước, và có thể có nhiều robot trên cùng một ô.

Ở mỗi lượt, một robot di chuyển một bước sang trái, phải, lên hoặc xuống, nhưng không được ra ngoài bàn cờ. Nó chọn ngẫu nhiên một hướng trong số các hướng có thể di chuyển.

Nhiệm vụ của bạn là tính số ô *trống* kỳ vọng sau $k$ lượt.

# Dữ liệu vào

Dòng duy nhất chứa một số nguyên $k$.

# Kết quả

In ra số ô trống kỳ vọng làm tròn đến sáu chữ số thập phân (làm tròn nửa đến chẵn).

# Giới hạn

* $1 \le k \le 100$

# Ví dụ

Dữ liệu vào:

```cpp
10
```

Kết quả:

```cpp
23.120740
```
