# 1625 - Mô tả đường đi trên lưới

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $88418$ đường đi trong một lưới $7 \times 7$ từ ô trên cùng bên trái đến ô dưới cùng bên trái. Mỗi đường đi tương ứng với một mô tả gồm $48$ ký tự bao gồm các ký tự `D` (xuống), `U` (lên), `L` (trái) và `R` (phải).

Ví dụ, đường đi
![](3624b569007eb03818b6611755f1bdbe4cdbd0a8334baf9fedc5365914bdd661)
tương ứng với mô tả `DRURRRRRDDDLUULDDDLDRRURDDLLLLLURULURRUULDLLDDDD`.

Bạn được cho một mô tả đường đi có thể chứa các ký tự `?` (hướng bất kỳ). Nhiệm vụ của bạn là tính số lượng đường đi khớp với mô tả.

# Dữ liệu vào

Dòng đầu vào duy nhất chứa một xâu $48$ ký tự gồm các ký tự `?`, `D`, `U`, `L` và `R`.

# Kết quả

In ra một số nguyên: tổng số đường đi.

# Ví dụ

Dữ liệu vào:

```cpp
??????R??????U??????????????????????????LD????D?
```

Kết quả:

```cpp
201
```
