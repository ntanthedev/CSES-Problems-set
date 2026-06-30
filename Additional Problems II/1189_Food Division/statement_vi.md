# 1189 - Food Division

* **Giới hạn thời gian:** 1.00 s
* **Giới hạn bộ nhớ:** 512 MB

Có $n$ đứa trẻ ngồi quanh một bàn tròn. Với mỗi đứa trẻ, bạn biết lượng thức ăn hiện tại chúng có và lượng thức ăn chúng muốn. Tổng lượng thức ăn trên bàn là chính xác.

Mỗi bước, một đứa trẻ có thể đưa một đơn vị thức ăn cho đứa trẻ bên cạnh. Hỏi số bước tối thiểu cần thực hiện là bao nhiêu?

# Dữ liệu vào

Dòng đầu tiên chứa một số nguyên $n$: số lượng đứa trẻ.

Dòng tiếp theo chứa $n$ số nguyên $a\_1,a\_2,\ldots,a\_n$: lượng thức ăn hiện tại của mỗi đứa trẻ.

Dòng cuối cùng chứa $n$ số nguyên $b\_1,b\_2,\ldots,b\_n$: lượng thức ăn yêu cầu của mỗi đứa trẻ.

# Kết quả

In ra một số nguyên: số bước tối thiểu.

# Giới hạn

* $1 \le n \le 2 \cdot 10^5$
* $0 \le a\_i, b\_i \le 10^6$

# Ví dụ

Dữ liệu vào:

```cpp
3
3 5 0
2 4 2
```

Kết quả:

```cpp
2
```

*Giải thích*: Đứa trẻ 1 đưa một đơn vị thức ăn cho đứa trẻ 3, và đứa trẻ 2 đưa một đơn vị thức ăn cho đứa trẻ 3.
