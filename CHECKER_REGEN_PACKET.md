# CHECKER_REGEN_PACKET — Gói tái sinh checker CSES

> Nguồn audit: `CHECKER_AUDIT_2026-07-03.md`  
> Phạm vi: **16 FAIL** + **31 RISK** = **47 bài**  
> Ngày tạo packet: 2026-07-03

---

## Hướng dẫn cho AI bên ngoài (Gemini / ChatGPT / Claude)

Bạn là problem-setter viết **testlib.h checker** cho bài CSES chạy trên judge DMOJ/VNOJ (`bridged` + `testlib`: `checker input output judge_answer`; exit 0 = AC, 1 = WA, 2 = PE).

### Tài liệu bắt buộc

1. **`CHECKER_STRATEGY_V2.md`** — quy tắc v2 (6 nhóm bug → idiom bắt buộc). Tóm tắt cứng:
   - **Cấm** `readLine()` trên `inf` hoặc `ouf`; grid đọc bằng `readToken()` từng hàng.
   - **Mọi số từ `ouf`** phải `ouf.readInt(lo, hi, "tên")` / `ouf.readLong(...)` — không `atoi`/`stoi`/`stoll` trên output thí sinh.
   - **Sentinel** (`IMPOSSIBLE`, `-1`): đọc `ans` trước để chọn nhánh, rồi mới đọc `ouf`.
   - **Không cấp phát** `vector(k)` trước khi `k` qua bounded read.
   - **Không** `readEoln`/`readEof` trên `ouf`; kết thúc bằng `if (!ouf.seekEof()) quitf(_wa, "extra information in the output file");`
   - **Không** giải lại bài trong checker (max-flow, suffix array, `string::find` O(nm), hash xác suất).
   - **So khớp optimum** lấy scalar từ `ans`; kiểm tra mọi invariant hợp lệ từ đề.
   - **Ngân sách:** O((n+m) log), bộ nhớ O(n+m).
   - **Header contract** đầu file (Problem / Input read / Validity / Optimality / Complexity).
   - Thất bại → `quitf(_wa, "...")`; không `ensuref`/`assert` trên dữ liệu thí sinh.

2. **`checker_skeleton.cpp`** — template compile được; **chép cấu trúc và idiom phòng thủ**, thay logic theo từng bài.

3. Mỗi bài dưới đây có `statement_en.md` và checker hiện tại (hoặc ghi chú thiếu file). Đọc đề + checker cũ để hiểu output format, rồi **viết lại hoàn toàn**.

### Cách làm từng bài

- Đọc **Regen instructions** (FAIL = sửa bug semantics/hardening; RISK = giữ semantics, sửa lint/hardening).
- Điền header contract; self-check danh sách trong `CHECKER_STRATEGY_V2.md` §4 trước khi trả lời.
- Chỉ output C++ source cho checker — không giải thích dài.

### RESPONSE FORMAT (bắt buộc)

Trả về **từng bài một khối**, đúng delimiter để agent Cursor paste tự động vào thư mục bài:

```
===CHECKER:<ID>===
(toàn bộ nội dung checker.cpp — không bọc ```cpp)
===END===
```

Ví dụ:

```
===CHECKER:2402===
#include "testlib.h"
...
===END===
```

**Quy tắc:**
- Một bài = một cặp `===CHECKER:ID===` … `===END===`.
- `ID` là số CSES (vd. `1193`), không có prefix khác.
- Không thêm markdown fence bên trong khối.
- Nếu xử lý theo Batch, trả đủ mọi ID trong batch được yêu cầu.
- File output luôn là `checker.cpp` trong thư mục bài (kể cả bài 1134 thay generic cũ).

---

## PASTE BACK TO CURSOR (cho người dùng)

1. Mở chat với **Cursor Agent** trong repo `cses-crawler`.
2. Copy toàn bộ phản hồi từ AI bên ngoài (các khối `===CHECKER:…===`).
3. Gửi prompt kiểu: *"Áp dụng các checker sau vào đúng thư mục bài trong repo"* và dán khối.
4. Agent sẽ ghi `checker.cpp` vào từng folder; sau đó chạy `python validate_checker_v2.py --only <ids>` trên Linux/WSL.
5. Với bài **1680**, **3361** (chưa có checker): agent tạo file mới. Với **1134**: thay `checker.cpp` (và cập nhật manifest bỏ `checker_file` generic nếu cần).
6. Upload lại OJ khi validate PASS.

---

## Mục lục batch


- **Batch 1:** 2423, 2414, 1669, 1134, 3361
- **Batch 2:** 1680, 1711, 2130, 1193
- **Batch 3:** 1640, 1070, 1111, 2075, 2106
- **Batch 4:** 3225, 3355, 1092, 1164
- **Batch 5:** 1197, 1666, 1667, 1668, 1678
- **Batch 6:** 1679, 1682, 1683, 1685, 1689
- **Batch 7:** 1695, 1696, 1698, 1704, 1709
- **Batch 8:** 1756, 2079, 2129, 2131, 2165
- **Batch 9:** 2214, 3294, 3308, 3399, 3403
- **Batch 10:** 3404, 3422, 3423, 3424

---


# Batch 1

**Problem IDs:** 2423, 2414, 1669, 1134, 3361

Xử lý toàn bộ batch này; trả về đủ các khối `===CHECKER:ID===` … `===END===` cho mỗi ID.


---

## 2423 — Filling Trominos

- **Severity:** `FAIL`

- **Folder:** `Construction Problems/2423_Filling Trominos/`

- **Output file:** `Construction Problems/2423_Filling Trominos/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** `is_tromino` accepts three collinear cells; statement requires L-trominoes.


### statement_en.md


# 2423 - Filling Trominos

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Your task is to fill an $n \times m$ grid using L-trominos (three squares that have an L-shape). For example, here is one way to fill a $4 \times 6$ grid:
![](da3ce928fcf66fd793d582a1a5ad7f7f9cc37e68aa2aadacee90f99bc4271692)

# Input

The first input line has an integer $t$: the number of tests.

After that, there are $t$ lines that describe the tests. Each line has two integers $n$ and $m$.

# Output

For each test, print YES if there is a solution, and NO otherwise.

If there is a solution, also print $n$ lines that each contain $m$ letters between A–Z. Adjacent squares must have the same letter exactly when they belong to the same tromino. You can print any valid solution.

# Constraints

* $1 \le t \le 100$
* $1 \le n,m \le 100$

# Example

Input:

```cpp
2
4 6
4 7
```

Output:

```cpp
YES
AADDBB
ACCDEB
BCAEEC
BBAACC
NO
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <queue>
#include <string>
#include <vector>
using namespace std;

static bool is_tromino(const vector<pair<int, int>>& cells) {
    if ((int)cells.size() != 3)
        return false;

    auto adj = [](int r1, int c1, int r2, int c2) {
        return abs(r1 - r2) + abs(c1 - c2) == 1;
    };

    int r1 = cells[0].first, c1 = cells[0].second;
    int r2 = cells[1].first, c2 = cells[1].second;
    int r3 = cells[2].first, c3 = cells[2].second;

    if (adj(r1, c1, r2, c2) && adj(r1, c1, r3, c3) && !adj(r2, c2, r3, c3))
        return true;
    if (adj(r2, c2, r1, c1) && adj(r2, c2, r3, c3) && !adj(r1, c1, r3, c3))
        return true;
    if (adj(r3, c3, r1, c1) && adj(r3, c3, r2, c2) && !adj(r1, c1, r2, c2))
        return true;
    return false;
}

static void validate_grid(int n, int m, const vector<string>& grid) {
    vector<vector<bool>> seen(n, vector<bool>(m, false));
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] < 'A' || grid[i][j] > 'Z')
                quitf(_wa, "Invalid character '%c' at (%d,%d)", grid[i][j], i + 1, j + 1);
            if (seen[i][j])
                continue;

            char letter = grid[i][j];
            vector<pair<int, int>> comp;
            queue<pair<int, int>> q;
            q.push({i, j});
            seen[i][j] = true;

            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                comp.push_back({r, c});
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                        continue;
                    if (seen[nr][nc] || grid[nr][nc] != letter)
                        continue;
                    seen[nr][nc] = true;
                    q.push({nr, nc});
                }
            }

            if (!is_tromino(comp))
                quitf(_wa,
                      "Letter '%c' component at (%d,%d) is not a valid L-tromino (%d cells)",
                      letter, i + 1, j + 1, (int)comp.size());
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int test = 0; test < t; test++) {
        int n = inf.readInt();
        int m = inf.readInt();
        string ans_flag = ans.readToken();
        string ouf_flag = ouf.readToken();

        if (ans_flag == "NO") {
            if (ouf_flag != "NO")
                quitf(_wa, "Test %d: no valid tiling exists but contestant printed '%s'", test + 1, ouf_flag.c_str());
            continue;
        }

        if (ans_flag != "YES")
            quitf(_fail, "Test %d: judge answer malformed, expected YES or NO", test + 1);

        if (ouf_flag == "NO")
            quitf(_wa, "Test %d: a valid tiling exists but contestant printed NO", test + 1);
        if (ouf_flag != "YES")
            quitf(_wa, "Test %d: expected YES or NO, got '%s'", test + 1, ouf_flag.c_str());

        for (int i = 0; i < n; i++)
            ans.readToken();

        vector<string> grid(n);
        for (int i = 0; i < n; i++) {
            grid[i] = ouf.readToken();
            if ((int)grid[i].size() != m)
                quitf(_wa, "Test %d row %d has %d characters, expected %d",
                      test + 1, i + 1, (int)grid[i].size(), m);
        }

        validate_grid(n, m, grid);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "All %d tests passed", t);
}

```


---

## 2414 — List of Sums

- **Severity:** `FAIL`

- **Folder:** `Additional Problems I/2414_List of Sums/`

- **Output file:** `Additional Problems I/2414_List of Sums/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Does not enforce output values are positive/in `[1, k]`; negative reconstructions can be accepted if pair sums match.


### statement_en.md


# 2414 - List of Sums

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

List $A$ consists of $n$ positive integers, and list $B$ contains the sum of each element pair of list $A$.

For example, if $A=[1,2,3]$, then $B=[3,4,5]$, and if $A=[1,3,3,3]$, then $B=[4,4,4,6,6,6]$.

Given list $B$, your task is to reconstruct list $A$.

# Input

The first input line has an integer $n$: the size of list $A$.

The next line has $\frac{n(n-1)}{2}$ integers: the contents of list $B$.

You can assume that there is a list $A$ that corresponds to the input, and each value in $A$ is between $1 \dots k$.

# Output

Print $n$ integers: the contents of list $A$.

You can print the values in any order. If there are more than one solution, you can print any of them.

# Constraints

* $3 \le n \le 100$
* $1 \le k \le 10^9$

# Example

Input:

```cpp
4
4 4 4 6 6 6
```

Output:

```cpp
1 3 3 3
```

*Explanation*: In this case list $A$ can be either $[1,3,3,3]$ or $[2,2,2,4]$ and both solutions are accepted.


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = n * (n - 1) / 2;

    vector<ll> inputB(m);
    for (int i = 0; i < m; i++)
        inputB[i] = inf.readLong();
    sort(inputB.begin(), inputB.end());

    vector<ll> A(n);
    for (int i = 0; i < n; i++)
        A[i] = ouf.readLong();

    vector<ll> computedB;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            computedB.push_back(A[i] + A[j]);
    }
    sort(computedB.begin(), computedB.end());

    if (inputB != computedB)
        quitf(_wa, "The pairwise sums of the output do not match the input list B");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid reconstruction");
}

```


---

## 1669 — Round Trip

- **Severity:** `FAIL`

- **Folder:** `Graph Algorithms/1669_Round Trip/`

- **Output file:** `Graph Algorithms/1669_Round Trip/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Accepts `k = 3`, so `u v u` is accepted on any valid road, but statement requires going through two or more other cities.


### statement_en.md


# 1669 - Round Trip

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Byteland has $n$ cities and $m$ roads between them. Your task is to design a round trip that begins in a city, goes through two or more other cities, and finally returns to the starting city. Every intermediate city on the route has to be distinct.

# Input

The first input line has two integers $n$ and $m$: the number of cities and roads. The cities are numbered $1,2,\dots,n$.

Then, there are $m$ lines describing the roads. Each line has two integers $a$ and $b$: there is a road between those cities.

Every road is between two different cities, and there is at most one road between any two cities.

# Output

First print an integer $k$: the number of cities on the route. Then print $k$ cities in the order they will be visited. You can print any valid solution.

If there are no solutions, print "IMPOSSIBLE".

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
5 6
1 3
1 2
5 3
1 5
2 4
4 5
```

Output:

```cpp
4
3 5 1 3
```


### checker.cpp (hiện tại)


```cpp

/*
 * HEADER CONTRACT
 * Problem:      1669 Round Trip
 * Input read:   n, m; m undirected roads (a, b)
 * Validity:     IMPOSSIBLE if no cycle; else k then k cities in [1,n],
 *               first equals last, intermediate cities distinct,
 *               consecutive cities connected by a road
 * Optimality:   any valid cycle (no scalar from ans)
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        int u = min(a, b), v = max(a, b);
        edges.insert({u, v});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a cycle exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    int k = ouf.readInt(3, n + 1, "k");
    vector<int> cycle(k);
    for (int i = 0; i < k; i++)
        cycle[i] = ouf.readInt(1, n, format("city[%d]", i + 1).c_str());

    if (cycle[0] != cycle[k - 1])
        quitf(_wa, "cycle must start and end at the same city (got %d and %d)",
              cycle[0], cycle[k - 1]);

    for (int i = 0; i + 1 < k; i++) {
        int u = cycle[i], v = cycle[i + 1];
        int a = min(u, v), b = max(u, v);
        if (!edges.count({a, b}))
            quitf(_wa, "no road between %d and %d on cycle step %d", u, v, i + 1);
    }

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < k - 1; i++) {
        if (seen[cycle[i]])
            quitf(_wa, "city %d appears more than once among intermediate cities", cycle[i]);
        seen[cycle[i]] = true;
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid cycle of length %d", k);
}

```


---

## 1134 — Prüfer Code

- **Severity:** `FAIL`

- **Folder:** `Advanced Graph Problems/1134_Prüfer Code/`

- **Output file:** `Advanced Graph Problems/1134_Prüfer Code/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Manifest points to `checker_unordered_pairs_symmetric.cpp`, which expects a leading `k`; statement prints exactly `n-1` edge lines with no `k`.


### statement_en.md


# 1134 - Prüfer Code

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A *Prüfer code* of a tree of $n$ nodes is a sequence of $n-2$ integers that uniquely specifies the structure of the tree.

The code is constructed as follows: As long as there are at least three nodes left, find a leaf with the smallest label, add the label of its only neighbor to the code, and remove the leaf from the tree.

Given a Prüfer code of a tree, your task is to construct the original tree.

# Input

The first input line contains an integer $n$: the number of nodes. The nodes are numbered $1,2,\ldots,n$.

The second line contains $n-2$ integers: the Prüfer code.

# Output

Print $n-1$ lines describing the edges of the tree. Each line has to contain two integers $a$ and $b$: there is an edge between nodes $a$ and $b$. You can print the edges in any order.

# Constraints

* $3 \le n \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
5
2 2 4
```

Output:

```cpp
1 2
2 3
2 4
4 5
```


### checker.cpp (hiện tại)


```cpp

// Generic "unordered set of unordered pairs" checker - for problems whose
// output is k lines, each an edge "a b" where (a,b) and (b,a) are the SAME
// edge, and the k lines may be printed in any order. Matches e.g. CSES
// "Necessary Roads" and "Pruefer Code" ("... print k lines that describe the
// roads/edges. You can print the roads/edges in any order.").
//
// Each pair is canonicalised to (min, max) before comparison, since an edge
// a-b is identical to b-a - this is the exact detail a naive "sort all
// whitespace tokens" checker gets wrong (it would accept a submission that
// has the right 2k numbers but paired into the WRONG, nonexistent edges).
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<long long, long long> pll;

static pll read_edge(InStream &s) {
    long long a = s.readLong(0, 2000000000LL, "a");
    long long b = s.readLong(0, 2000000000LL, "b");
    if (a > b) swap(a, b);
    return pll(a, b);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int k_out = ouf.readInt(0, 2000000000, "k (contestant)");
    vector<pll> a(k_out);
    for (int i = 0; i < k_out; i++) a[i] = read_edge(ouf);

    int k_ans = ans.readInt();
    vector<pll> b(k_ans);
    for (int i = 0; i < k_ans; i++) b[i] = read_edge(ans);

    if (k_out != k_ans)
        quitf(_wa, "expected %d edges, found %d", k_ans, k_out);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a != b)
        quitf(_wa, "the set of %d edges does not match the reference set", k_ans);

    quitf(_ok, "%d edges, correct set", k_ans);
}

```


---

## 3361 — Two Array Average

- **Severity:** `FAIL`

- **Folder:** `Additional Problems I/3361_Two Array Average/`

- **Output file:** `Additional Problems I/3361_Two Array Average/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Manifest uses `floats`, but the statement outputs two prefix sizes, not a floating number. Needs a custom checker that validates the chosen prefixes' average within `1e-6` of optimum.


### statement_en.md


# 3361 - Two Array Average

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given two arrays of $n$ integers.

Your task is to select a nonempty prefix from both arrays such that the average of all selected numbers is as large as possible.

# Input

The first line has an integer $n$.

The second line has $n$ integers $a\_1,a\_2,\dots,a\_n$: the numbers in the first array.

The third line has $n$ integers $b\_1,b\_2,\dots,b\_n$: the numbers in the second array.

# Output

Print two numbers: the prefix sizes.

Your answer is considered correct if the absolute or relative difference to the maximum average is at most $10^{-6}$.

# Constraints

* $1 \le n \le 10^5$
* $1 \le a\_i, b\_i \le 10^9$

# Example

Input:

```cpp
4
1 5 5 2
3 1 3 1
```

Output:

```cpp
3 1
```

Explanation: if you choose the prefixes $[1,5,5]$ and $[3]$, the average is $(1+5+5+3)/4=3.5$ which is the maximum possible average.


### checker.cpp (hiện tại)


*(KHÔNG TỒN TẠI — viết `checker.cpp` mới từ đầu theo đề và `checker_skeleton.cpp`.)*


# Batch 2

**Problem IDs:** 1680, 1711, 2130, 1193

Xử lý toàn bộ batch này; trả về đủ các khối `===CHECKER:ID===` … `===END===` cho mỗi ID.


---

## 1680 — Longest Flight Route

- **Severity:** `FAIL`

- **Folder:** `Graph Algorithms/1680_Longest Flight Route/`

- **Output file:** `Graph Algorithms/1680_Longest Flight Route/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Manifest marks it as generated `bridged`, but `Graph Algorithms/1680_Longest Flight Route/checker.cpp` is missing.


### statement_en.md


# 1680 - Longest Flight Route

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Uolevi has won a contest, and the prize is a free flight trip that can consist of one or more flights through cities. Of course, Uolevi wants to choose a trip that has as many cities as possible.

Uolevi wants to fly from Syrjälä to Lehmälä so that he visits the maximum number of cities. You are given the list of possible flights, and you know that there are no directed cycles in the flight network.

# Input

The first input line has two integers $n$ and $m$: the number of cities and flights. The cities are numbered $1,2,\dots,n$. City $1$ is Syrjälä, and city $n$ is Lehmälä.

After this, there are $m$ lines describing the flights. Each line has two integers $a$ and $b$: there is a flight from city $a$ to city $b$. Each flight is a one-way flight.

# Output

First print the maximum number of cities on the route. After this, print the cities in the order they will be visited. You can print any valid solution.

If there are no solutions, print "IMPOSSIBLE".

# Constraints

* $2 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
5 5
1 2
2 5
1 3
3 4
4 5
```

Output:

```cpp
4
1 3 4 5
```


### checker.cpp (hiện tại)


*(KHÔNG TỒN TẠI — viết `checker.cpp` mới từ đầu theo đề và `checker_skeleton.cpp`.)*


---

## 1711 — Distinct Routes

- **Severity:** `FAIL`

- **Folder:** `Graph Algorithms/1711_Distinct Routes/`

- **Output file:** `Graph Algorithms/1711_Distinct Routes/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Reads path length before bounding and allocates `vector<int> path(len)`, so hostile output can crash/MLE.


### statement_en.md


# 1711 - Distinct Routes

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A game consists of $n$ rooms and $m$ teleporters. At the beginning of each day, you start in room $1$ and you have to reach room $n$.

You can use each teleporter at most once during the game. How many days can you play if you choose your routes optimally?

# Input

The first input line has two integers $n$ and $m$: the number of rooms and teleporters. The rooms are numbered $1,2,\dots,n$.

After this, there are $m$ lines describing the teleporters. Each line has two integers $a$ and $b$: there is a teleporter from room $a$ to room $b$.

There are no two teleporters whose starting and ending room are the same.

# Output

First print an integer $k$: the maximum number of days you can play the game. Then, print $k$ route descriptions according to the example. You can print any valid solution.

# Constraints

* $2 \le n \le 500$
* $1 \le m \le 1000$
* $1 \le a,b \le n$

# Example

Input:

```cpp
6 7
1 2
1 3
2 6
3 4
3 5
4 6
5 6
```

Output:

```cpp
2
3
1 2 6
4
1 3 4 6
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<pair<int, int>> teleporters;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        teleporters.push_back({a, b});
    }

    int maxDays = ans.readInt();
    int k = ouf.readInt();
    if (k < 0 || k > m)
        quitf(_wa, "Number of days %d out of range [0,%d]", k, m);

    if (k != maxDays)
        quitf(_wa, "Found %d day routes but optimal is %d", k, maxDays);

    set<pair<int, int>> usedEdges;
    for (int day = 0; day < k; day++) {
        int len = ouf.readInt();
        if (len < 2)
            quitf(_wa, "Day %d path length %d too short", day + 1, len);

        vector<int> path(len);
        for (int i = 0; i < len; i++) {
            path[i] = ouf.readInt();
            if (path[i] < 1 || path[i] > n)
                quitf(_wa, "Room %d out of range on day %d", path[i], day + 1);
        }

        if (path[0] != 1)
            quitf(_wa, "Day %d path must start at room 1", day + 1);
        if (path[len - 1] != n)
            quitf(_wa, "Day %d path must end at room %d", day + 1, n);

        for (int i = 0; i + 1 < len; i++) {
            int u = path[i], v = path[i + 1];
            pair<int, int> edge = {u, v};
            bool exists = false;
            for (auto tp : teleporters)
                if (tp == edge) {
                    exists = true;
                    break;
                }
            if (!exists)
                quitf(_wa, "No teleporter from %d to %d (day %d)", u, v, day + 1);
            if (usedEdges.count(edge))
                quitf(_wa, "Teleporter %d->%d used more than once", u, v);
            usedEdges.insert(edge);
        }

        int ansLen = ans.readInt();
        for (int i = 0; i < ansLen; i++)
            ans.readInt();
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid %d edge-disjoint routes", k);
}

```


---

## 2130 — Distinct Routes II

- **Severity:** `FAIL`

- **Folder:** `Advanced Techniques/2130_Distinct Routes II/`

- **Output file:** `Advanced Techniques/2130_Distinct Routes II/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Reads `route_len` before bounding and allocates `vector<int> route(route_len)`, so hostile output can crash/MLE.


### statement_en.md


# 2130 - Distinct Routes II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A game consists of $n$ rooms and $m$ teleporters. At the beginning of each day, you start in room $1$ and you have to reach room $n$.

You can use each teleporter at most once during the game. You want to play the game for exactly $k$ days. Every time you use any teleporter you have to pay one coin. What is the minimum number of coins you have to pay during $k$ days if you play optimally?

# Input

The first input line has three integers $n$, $m$ and $k$: the number of rooms, the number of teleporters and the number of days you play the game. The rooms are numbered $1,2,\dots,n$.

After this, there are $m$ lines describing the teleporters. Each line has two integers $a$ and $b$: there is a teleporter from room $a$ to room $b$.

There are no two teleporters whose starting and ending room are the same.

# Output

First print one integer: the minimum number of coins you have to pay if you play optimally. Then, print $k$ route descriptions according to the example. You can print any valid solution.

If it is not possible to play the game for $k$ days, print only -1.

# Constraints

* $2 \le n \le 500$
* $1 \le m \le 1000$
* $1 \le k \le n-1$
* $1 \le a,b \le n$

# Example

Input:

```cpp
8 10 2
1 2
1 3
2 5
2 4
3 5 
3 6
4 8
5 8
6 7 
7 8
```

Output:

```cpp
6
4
1 2 4 8 
4
1 3 5 8
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    int k_req = inf.readInt();
    vector<set<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].insert(b);
    }

    int ans_first = ans.readInt();
    bool impossible = (ans_first == -1);

    int first_val = ouf.readInt();
    if (first_val == -1) {
        if (!impossible)
            quitf(_wa, "Output is -1 but playing for %d days is possible", k_req);
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correctly reported impossible");
    }

    if (impossible)
        quitf(_wa, "Expected -1 (impossible), but contestant claimed %d coins", first_val);

    int total_coins = first_val;
    if (total_coins != ans_first)
        quitf(_wa, "Minimum number of coins is %d, got %d", ans_first, total_coins);
    if (total_coins < 0)
        quitf(_wa, "Total coins must be non-negative");

    set<pair<int, int>> used_edges;
    int actual_total_len = 0;

    for (int day = 0; day < k_req; day++) {
        int route_len = ouf.readInt();
        if (route_len < 1)
            quitf(_wa, "Route length must be at least 1");

        vector<int> route(route_len);
        for (int i = 0; i < route_len; i++) {
            route[i] = ouf.readInt();
            if (route[i] < 1 || route[i] > n)
                quitf(_wa, "Room %d out of range", route[i]);
        }

        if (route[0] != 1)
            quitf(_wa, "Route must start at room 1, starts at %d", route[0]);
        if (route[route_len - 1] != n)
            quitf(_wa, "Route must end at room n, ends at %d", route[route_len - 1]);

        for (int i = 0; i + 1 < route_len; i++) {
            int a = route[i], b = route[i + 1];
            if (!g[a].count(b))
                quitf(_wa, "Teleporter %d -> %d does not exist", a, b);
            pair<int, int> key = {a, b};
            if (used_edges.count(key))
                quitf(_wa, "Teleporter %d -> %d used more than once", a, b);
            used_edges.insert(key);
            actual_total_len++;
        }
    }

    if (actual_total_len != total_coins)
        quitf(_wa, "Claimed total coins %d, but sum of route lengths is %d",
              total_coins, actual_total_len);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal %d routes, total %d coins", k_req, total_coins);
}

```


---

## 1193 — Labyrinth

- **Severity:** `FAIL`

- **Folder:** `Graph Algorithms/1193_Labyrinth/`

- **Output file:** `Graph Algorithms/1193_Labyrinth/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Reads grid with `inf.readLine()` after `readInt`, causing line drift; also has unbounded output reads.


### statement_en.md


# 1193 - Labyrinth

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given a map of a labyrinth, and your task is to find a path from start to end. You can walk left, right, up and down.

# Input

The first input line has two integers $n$ and $m$: the height and width of the map.

Then there are $n$ lines of $m$ characters describing the labyrinth. Each character is `.` (floor), `#` (wall), `A` (start), or `B` (end). There is exactly one `A` and one `B` in the input.

# Output

First print "YES", if there is a path, and "NO" otherwise.

If there is a path, print the length of the shortest such path and its description as a string consisting of characters `L` (left), `R` (right), `U` (up), and `D` (down). You can print any valid solution.

# Constraints

* $1 \le n,m \le 1000$

# Example

Input:

```cpp
5 8
########
#.A#...#
#.##.#B#
#......#
########
```

Output:

```cpp
YES
9
LDDRRRRRU
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<string> grid(n);
    pair<int, int> start, target;
    for (int i = 0; i < n; i++) {
        grid[i] = inf.readLine();
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') start = {i, j};
            if (grid[i][j] == 'B') target = {i, j};
        }
    }

    string ansFlag = ans.readToken();
    if (ansFlag != "YES" && ansFlag != "NO")
        quitf(_fail, "Invalid judge answer token '%s'", ansFlag.c_str());

    string outFlag = ouf.readToken();
    if (outFlag != "YES" && outFlag != "NO")
        quitf(_wa, "Expected YES or NO, got '%s'", outFlag.c_str());

    if (outFlag == "NO") {
        if (ansFlag != "NO")
            quitf(_wa, "Output is NO but a path exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no path");
    }

    if (ansFlag == "NO")
        quitf(_wa, "A path exists but output is NO");

    int minLen = ans.readInt();
    int len = ouf.readInt();
    string path = ouf.readToken();

    if ((int)path.size() != len)
        quitf(_wa, "Path length %d does not match string length %d", len, (int)path.size());
    if (len != minLen)
        quitf(_wa, "Path length %d is not shortest (optimal is %d)", len, minLen);

    int r = start.first, c = start.second;
    for (char ch : path) {
        if (ch == 'L') c--;
        else if (ch == 'R') c++;
        else if (ch == 'U') r--;
        else if (ch == 'D') r++;
        else quitf(_wa, "Invalid direction '%c'", ch);

        if (r < 0 || r >= n || c < 0 || c >= m)
            quitf(_wa, "Path goes out of bounds at step with '%c'", ch);
        if (grid[r][c] == '#')
            quitf(_wa, "Path walks into a wall at (%d,%d)", r + 1, c + 1);
    }

    if (r != target.first || c != target.second)
        quitf(_wa, "Path ends at (%d,%d) instead of target (%d,%d)",
              r + 1, c + 1, target.first + 1, target.second + 1);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid shortest path of length %d", len);
}

```


# Batch 3

**Problem IDs:** 1640, 1070, 1111, 2075, 2106

Xử lý toàn bộ batch này; trả về đủ các khối `===CHECKER:ID===` … `===END===` cho mỗi ID.


---

## 1640 — Sum of Two Values

- **Severity:** `FAIL`

- **Folder:** `Sorting and Searching/1640_Sum of Two Values/`

- **Output file:** `Sorting and Searching/1640_Sum of Two Values/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Uses `stoi` on contestant token and `ouf.readEoln()`, so it can crash or reject valid whitespace.


### statement_en.md


# 1640 - Sum of Two Values

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array of $n$ integers, and your task is to find two values (at distinct positions) whose sum is $x$.

# Input

The first input line has two integers $n$ and $x$: the array size and the target sum.

The second line has $n$ integers $a\_1,a\_2,\dots,a\_n$: the array values.

# Output

Print two integers: the positions of the values. If there are several solutions, you may print any of them. If there are no solutions, print `IMPOSSIBLE`.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le x,a\_i \le 10^9$

# Example

Input:

```cpp
4 8
2 7 5 1
```

Output:

```cpp
2 4
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int x = inf.readInt();
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        a[i] = inf.readInt();
    string ans_first = ans.readToken();
    string ouf_first = ouf.readToken();

    if (ans_first == "IMPOSSIBLE") {
        if (ouf_first != "IMPOSSIBLE")
            quitf(_wa, "No valid pair exists but contestant printed '%s'", ouf_first.c_str());
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no pair");
    }

    if (ouf_first == "IMPOSSIBLE")
        quitf(_wa, "A valid pair exists but contestant printed IMPOSSIBLE");

    int i = stoi(ouf_first);
    int j = ouf.readInt();
    ouf.readEoln();
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    if (i < 1 || i > n)
        quitf(_wa, "First position %d out of range [1,%d]", i, n);
    if (j < 1 || j > n)
        quitf(_wa, "Second position %d out of range [1,%d]", j, n);
    if (i == j)
        quitf(_wa, "Positions must be distinct, got %d and %d", i, j);
    if ((long long)a[i - 1] + a[j - 1] != x)
        quitf(_wa, "Values at positions %d and %d sum to %lld, expected %d",
              i, j, (long long)a[i - 1] + a[j - 1], x);

    quitf(_ok, "Valid pair (%d, %d)", i, j);
}

```


---

## 1070 — Permutations

- **Severity:** `FAIL`

- **Folder:** `Introductory Problems/1070_Permutations/`

- **Output file:** `Introductory Problems/1070_Permutations/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Uses `atoi` on contestant token; malformed tokens like `4abc` can be accepted as `4`.


### statement_en.md


# 1070 - Permutations

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A permutation of integers $1,2,\ldots,n$ is called *beautiful* if there are no adjacent elements whose difference is $1$.

Given $n$, construct a beautiful permutation if such a permutation exists.

# Input

The only input line contains an integer $n$.

# Output

Print a beautiful permutation of integers $1,2,\ldots,n$. If there are several solutions, you may print any of them. If there are no solutions, print "NO SOLUTION".

# Constraints

* $1 \le n \le 10^6$

# Example 1

Input:

```cpp
5
```

Output:

```cpp
4 2 5 3 1
```

# Example 2

Input:

```cpp
3
```

Output:

```cpp
NO SOLUTION
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <cstdlib>
#include <vector>
using namespace std;

static void consume_permutation(int n, InStream& stream) {
    for (int i = 1; i < n; i++)
        stream.readInt();
}

static void check_permutation(int n, const vector<int>& perm) {
    if ((int)perm.size() != n)
        quitf(_wa, "Expected %d numbers, got %d", n, (int)perm.size());

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; i++) {
        int x = perm[i];
        if (x < 1 || x > n)
            quitf(_wa, "Value %d out of range [1,%d]", x, n);
        if (seen[x])
            quitf(_wa, "Duplicate value %d", x);
        seen[x] = true;
    }

    for (int i = 0; i + 1 < n; i++) {
        if (abs(perm[i] - perm[i + 1]) == 1)
            quitf(_wa, "Adjacent elements %d and %d differ by 1", perm[i], perm[i + 1]);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    string ans_first = ans.readToken();
    if (ans_first == "NO") {
        string ans_second = ans.readToken();
        if (ans_second != "SOLUTION")
            quitf(_fail, "Judge answer malformed: expected NO SOLUTION");

        string ouf_first = ouf.readToken();
        if (ouf_first != "NO")
            quitf(_wa, "No beautiful permutation exists but contestant printed '%s'", ouf_first.c_str());
        string ouf_second = ouf.readToken();
        if (ouf_second != "SOLUTION")
            quitf(_wa, "Expected 'NO SOLUTION' but got 'NO %s'", ouf_second.c_str());
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no solution for n=%d", n);
    }

    consume_permutation(n, ans);

    string ouf_first = ouf.readToken();
    if (ouf_first == "NO")
        quitf(_wa, "A beautiful permutation exists but contestant printed NO SOLUTION");

    vector<int> perm;
    perm.push_back(atoi(ouf_first.c_str()));
    for (int i = 1; i < n; i++)
        perm.push_back(ouf.readInt());
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    check_permutation(n, perm);
    quitf(_ok, "Valid beautiful permutation of length %d", n);
}

```


---

## 1111 — Longest Palindrome

- **Severity:** `FAIL`

- **Folder:** `String Algorithms/1111_Longest Palindrome/`

- **Output file:** `String Algorithms/1111_Longest Palindrome/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Uses `s.find(out)` at `n <= 1e6`; this is the v2 forbidden O(nm) substring pattern.


### statement_en.md


# 1111 - Longest Palindrome

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given a string, your task is to determine the longest palindromic substring of the string. For example, the longest palindrome in `aybabtu` is `bab`.

# Input

The only input line contains a string of length $n$. Each character is one of a–z.

# Output

Print the longest palindrome in the string. If there are several solutions, you may print any of them.

# Constraints

* $1 \le n \le 10^6$

# Example

Input:

```cpp
aybabtu
```

Output:

```cpp
bab
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <string>
using namespace std;

bool is_palindrome(const string& t) {
    int l = 0, r = (int)t.size() - 1;
    while (l < r) {
        if (t[l] != t[r]) return false;
        l++;
        r--;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string s = inf.readToken();
    string ref = ans.readToken();
    string out = ouf.readToken();

    int optimal = (int)ref.size();

    for (char c : out) {
        if (c < 'a' || c > 'z')
            quitf(_wa, "Output contains invalid character '%c'", c);
    }

    if (out.empty())
        quitf(_wa, "Output must be non-empty");

    if (!is_palindrome(out))
        quitf(_wa, "Output is not a palindrome");

    if (s.find(out) == string::npos)
        quitf(_wa, "Output is not a substring of the input");

    if ((int)out.size() != optimal)
        quitf(_wa, "Longest palindrome has length %d, got %d",
              optimal, (int)out.size());

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid longest palindrome of length %d", optimal);
}

```


---

## 2075 — Reversal Sorting

- **Severity:** `FAIL`

- **Folder:** `Additional Problems II/2075_Reversal Sorting/`

- **Output file:** `Additional Problems II/2075_Reversal Sorting/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Simulates each reversal with `std::reverse`; with `n, k = 2e5`, valid or hostile outputs can make the checker O(n^2).


### statement_en.md


# 2075 - Reversal Sorting

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You have an array that contains a permutation of integers $1,2,\dots,n$. Your task is to sort the array in increasing order by reversing subarrays. You can construct any solution that has at most $n$ reversals.

# Input

The first input line has an integer $n$: the size of the array. The array elements are numbered $1,2,\dots,n$.

The next line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the contents of the array.

# Output

First print an integer $k$: the number of reversals.

After that, print $k$ lines that describe the reversals. Each line has two integers $a$ and $b$: you reverse a subarray from position $a$ to position $b$.

# Constraints

* $1 \le n \le 2 \cdot 10^5$

# Example

Input:

```cpp
4
2 3 1 4
```

Output:

```cpp
2
1 3
2 3
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> perm(n + 1);
    for (int i = 1; i <= n; i++)
        perm[i] = inf.readInt();

    int k = ouf.readInt();
    if (k < 0 || k > n)
        quitf(_wa, "Number of reversals must be between 0 and %d, got %d", n, k);

    vector<int> cur = perm;
    for (int r = 0; r < k; r++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || b < a || b > n)
            quitf(_wa, "Reversal %d: invalid range [%d, %d]", r + 1, a, b);
        reverse(cur.begin() + a, cur.begin() + b + 1);
    }

    for (int i = 1; i <= n; i++) {
        if (cur[i] != i)
            quitf(_wa, "After all reversals, position %d has value %d, expected %d", i, cur[i], i);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid sorting with %d reversals", k);
}

```


---

## 2106 — Repeating Substring

- **Severity:** `FAIL`

- **Folder:** `String Algorithms/2106_Repeating Substring/`

- **Output file:** `String Algorithms/2106_Repeating Substring/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Uses `ouf.readLine()` and repeated `string::find`, causing whitespace fragility and O(nm) risk.


### statement_en.md


# 2106 - Repeating Substring

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A repeating substring is a substring that occurs in two (or more) locations in the string. Your task is to find the longest repeating substring in a given string.

# Input

The only input line has a string of length $n$ that consists of characters a–z.

# Output

Print the longest repeating substring. If there are several possibilities, you can print any of them. If there is no repeating substring, print $-1$.

# Constraints

* $1 \le n \le 10^5$

# Example

Input:

```cpp
cabababc
```

Output:

```cpp
abab
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <string>
using namespace std;

int count_occurrences(const string& s, const string& t) {
    if (t.empty()) return 0;
    int cnt = 0, pos = 0;
    while (true) {
        pos = (int)s.find(t, pos);
        if (pos == (int)string::npos) break;
        cnt++;
        pos++;
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string s = inf.readToken();
    string ref = ans.readLine();
    string out = ouf.readLine();

    if (ref == "-1") {
        if (out != "-1")
            quitf(_wa, "No repeating substring exists but output is not -1");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no repeating substring");
    }

    if (out == "-1")
        quitf(_wa, "A repeating substring exists but output is -1");

    int optimal = (int)ref.size();

    for (char c : out) {
        if (c < 'a' || c > 'z')
            quitf(_wa, "Output contains invalid character '%c'", c);
    }

    if (out.empty())
        quitf(_wa, "Repeating substring must be non-empty");

    if (s.find(out) == string::npos)
        quitf(_wa, "Output is not a substring of the input");

    if (count_occurrences(s, out) < 2)
        quitf(_wa, "Substring occurs fewer than two times");

    if ((int)out.size() != optimal)
        quitf(_wa, "Longest repeating substring has length %d, got %d",
              optimal, (int)out.size());

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid longest repeating substring of length %d", optimal);
}

```


# Batch 4

**Problem IDs:** 3225, 3355, 1092, 1164

Xử lý toàn bộ batch này; trả về đủ các khối `===CHECKER:ID===` … `===END===` cho mỗi ID.


---

## 3225 — Inverse Suffix Array

- **Severity:** `FAIL`

- **Folder:** `String Algorithms/3225_Inverse Suffix Array/`

- **Output file:** `String Algorithms/3225_Inverse Suffix Array/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Uses one-mod rolling hash for suffix comparison; not deterministic, collision can accept/reject incorrectly.


### statement_en.md


# 3225 - Inverse Suffix Array

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given a suffix array of a string, your task is to reconstruct the string.

The suffix array of a string of length $n$ is a permutation of numbers $1,2,\dots,n$ that presents the lexicographical order of the suffixes.

# Input

The first line has an integer $n$: the length of the string.

The next line has $n$ integers: the suffix array.

# Output

Print a string that corresponds to the suffix array. The string must consist of characters a–z. If there are several possible strings, you can print any of them.

If no string corresponds to the suffix array, print $-1$.

# Constraints

* $1 \le n \le 10^5$

# Example

Input:

```cpp
7
4 1 3 5 6 7 2
```

Output:

```cpp
aybabtu
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

struct RollingHash {
    static const long long base = 911382323;
    static const long long mod = 1000000007;
    vector<long long> pw, h;

    RollingHash(const string& s) {
        int n = (int)s.size();
        pw.resize(n + 1);
        h.resize(n + 1);
        pw[0] = 1;
        for (int i = 0; i < n; i++) {
            pw[i + 1] = pw[i] * base % mod;
            h[i + 1] = (h[i] * base + s[i]) % mod;
        }
    }

    long long get(int l, int r) const {
        return (h[r] - h[l] * pw[r - l] % mod + mod) % mod;
    }
};

bool suffix_less(const string& s, const RollingHash& rh, int i, int j) {
    int ni = (int)s.size() - i;
    int nj = (int)s.size() - j;
    int lo = 0, hi = min(ni, nj);
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (rh.get(i, i + mid) == rh.get(j, j + mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    if (lo == ni && lo == nj) return false;
    if (lo == ni) return true;
    if (lo == nj) return false;
    return s[i + lo] < s[j + lo];
}

bool valid_suffix_array(const string& s, const vector<int>& sa) {
    int n = (int)sa.size();
    vector<int> seen(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (sa[i] < 1 || sa[i] > n) return false;
        if (seen[sa[i]]) return false;
        seen[sa[i]] = 1;
    }

    RollingHash rh(s);
    for (int i = 0; i + 1 < n; i++) {
        int a = sa[i] - 1;
        int b = sa[i + 1] - 1;
        if (!suffix_less(s, rh, a, b))
            return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> given(n);
    for (int i = 0; i < n; i++)
        given[i] = inf.readInt();

    string ref = ans.readToken();
    string first = ouf.readToken();

    if (ref == "-1") {
        if (first != "-1")
            quitf(_wa, "No string corresponds to this suffix array");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: impossible suffix array");
    }

    if (first == "-1")
        quitf(_wa, "A valid string exists for this suffix array");

    string out = first;
    if ((int)out.size() != n)
        quitf(_wa, "String length is %d, expected %d", (int)out.size(), n);

    for (char c : out) {
        if (c < 'a' || c > 'z')
            quitf(_wa, "Output contains invalid character '%c'", c);
    }

    if (!valid_suffix_array(out, given))
        quitf(_wa, "Suffix array of output does not match input");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid string for suffix array");
}

```


---

## 3355 — Sum of Four Squares

- **Severity:** `FAIL`

- **Folder:** `Mathematics/3355_Sum of Four Squares/`

- **Output file:** `Mathematics/3355_Sum of Four Squares/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Không vá checker cũ — viết lại từ đầu.

**Lỗi audit (FAIL):** Reads unbounded longs and squares them in `long long`; overflow/UB can lead to wrong verdicts.


### statement_en.md


# 3355 - Sum of Four Squares

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A well known result in number theory is that every non-negative integer can be represented as the sum of four squares of non-negative integers.

You are given a non-negative integer $n$. Your task is to find four non-negative integers $a$, $b$, $c$ and $d$ such that $n = a^2 + b^2 + c^2 + d^2$.

# Input

The first line has an integer $t$: the number of test cases.

Each of the next $t$ lines has an integer $n$.

# Output

For each test case, print four non-negative integers $a$, $b$, $c$ and $d$ that satisfy $n = a^2 + b^2 + c^2 + d^2$.

# Constraints

* $1 \le t \le 1000$
* $0 \le n \le 10^7$
* the sum of all $n$ is at most $10^7$

# Example

Input:

```cpp
3
5
30
322266
```

Output:

```cpp
2 1 0 0
1 2 3 4
314 159 265 358
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int tc = 1; tc <= t; tc++) {
        long long n = inf.readLong();
        long long a = ouf.readLong();
        long long b = ouf.readLong();
        long long c = ouf.readLong();
        long long d = ouf.readLong();

        if (a < 0 || b < 0 || c < 0 || d < 0)
            quitf(_wa, "Test %d: all four numbers must be non-negative", tc);
        long long sum = a * a + b * b + c * c + d * d;
        if (sum != n)
            quitf(_wa, "Test %d: %lld^2 + %lld^2 + %lld^2 + %lld^2 = %lld, expected %lld",
                  tc, a, b, c, d, sum, n);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid representation for all %d test cases", t);
}

```


---

## 1092 — Two Sets

- **Severity:** `RISK`

- **Folder:** `Introductory Problems/1092_Two Sets/`

- **Output file:** `Introductory Problems/1092_Two Sets/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Semantics OK, but many bare `ouf.readInt()` calls and `std::set` up to `n = 1e6`.


### statement_en.md


# 1092 - Two Sets

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Your task is to divide the numbers $1,2,\ldots,n$ into two sets of equal sum.

# Input

The only input line contains an integer $n$.

# Output

Print "YES", if the division is possible, and "NO" otherwise.

After this, if the division is possible, print an example of how to create the sets. First, print the number of elements in the first set followed by the elements themselves in a separate line, and then, print the second set in a similar way.

# Constraints

* $1 \le n \le 10^6$

# Example 1

Input:

```cpp
7
```

Output:

```cpp
YES
4
1 2 4 7
3
3 5 6
```

# Example 2

Input:

```cpp
6
```

Output:

```cpp
NO
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    string ans_token = ans.readToken();
    string ouf_token = ouf.readToken();

    if (ans_token == "NO") {
        if (ouf_token != "NO")
            quitf(_wa, "No partition exists but contestant printed '%s'", ouf_token.c_str());
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no partition");
    }

    if (ouf_token == "NO")
        quitf(_wa, "A partition exists but contestant printed NO");
    if (ouf_token != "YES")
        quitf(_wa, "Expected YES or NO, got '%s'", ouf_token.c_str());

    int k1 = ouf.readInt();
    if (k1 < 0 || k1 > n)
        quitf(_wa, "First set size %d out of range [0,%d]", k1, n);

    vector<int> set1(k1);
    long long sum1 = 0;
    for (int i = 0; i < k1; i++) {
        set1[i] = ouf.readInt();
        if (set1[i] < 1 || set1[i] > n)
            quitf(_wa, "Value %d out of range [1,%d]", set1[i], n);
        sum1 += set1[i];
    }

    int k2 = ouf.readInt();
    if (k1 + k2 != n)
        quitf(_wa, "Set sizes %d + %d != n=%d", k1, k2, n);

    long long sum2 = 0;
    for (int i = 0; i < k2; i++) {
        int x = ouf.readInt();
        if (x < 1 || x > n)
            quitf(_wa, "Value %d out of range [1,%d]", x, n);
        sum2 += x;
        set1.push_back(x);
    }
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    set<int> seen;
    for (int x : set1) {
        if (seen.count(x))
            quitf(_wa, "Value %d appears more than once", x);
        seen.insert(x);
    }
    if ((int)seen.size() != n)
        quitf(_wa, "Output does not use each number 1..%d exactly once", n);

    if (sum1 != sum2)
        quitf(_wa, "Set sums differ: %lld vs %lld", sum1, sum2);

    quitf(_ok, "Valid partition of 1..%d", n);
}

```


---

## 1164 — Room Allocation

- **Severity:** `RISK`

- **Folder:** `Sorting and Searching/1164_Room Allocation/`

- **Output file:** `Sorting and Searching/1164_Room Allocation/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Semantics OK, but uses `ouf.readEoln()` and can reject harmless whitespace.


### statement_en.md


# 1164 - Room Allocation

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is a large hotel, and $n$ customers will arrive soon. Each customer wants to have a single room.

You know each customer's arrival and departure day. Two customers can stay in the same room if the departure day of the first customer is earlier than the arrival day of the second customer.

What is the minimum number of rooms that are needed to accommodate all customers? And how can the rooms be allocated?

# Input

The first input line contains an integer $n$: the number of customers.

Then there are $n$ lines, each of which describes one customer. Each line has two integers $a$ and $b$: the arrival and departure day.

# Output

Print first an integer $k$: the minimum number of rooms required.

After that, print a line that contains the room number of each customer in the same order as in the input. The rooms are numbered $1,2,\ldots,k$. You can print any valid solution.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a \le b \le 10^9$

# Example

Input:

```cpp
3
1 2
2 4
4 4
```

Output:

```cpp
2
1 2 1
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<pair<int, int>> intervals(n);
    for (int i = 0; i < n; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        intervals[i] = {a, b};
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Minimum rooms is %d, got %d", k_ans, k);
    ouf.readEoln();

    vector<int> room(n);
    for (int i = 0; i < n; i++) {
        room[i] = ouf.readInt();
        if (room[i] < 1 || room[i] > k)
            quitf(_wa, "Room %d for customer %d out of range [1,%d]", room[i], i + 1, k);
    }
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    vector<vector<int>> by_room(k + 1);
    for (int i = 0; i < n; i++)
        by_room[room[i]].push_back(i);

    for (int r = 1; r <= k; r++) {
        auto& cust = by_room[r];
        sort(cust.begin(), cust.end(), [&](int i, int j) {
            if (intervals[i].first != intervals[j].first)
                return intervals[i].first < intervals[j].first;
            return intervals[i].second < intervals[j].second;
        });
        for (int j = 1; j < (int)cust.size(); j++) {
            int prev = cust[j - 1];
            int cur = cust[j];
            if (intervals[prev].second >= intervals[cur].first)
                quitf(_wa,
                      "Customers %d [%d,%d] and %d [%d,%d] overlap in room %d",
                      prev + 1, intervals[prev].first, intervals[prev].second,
                      cur + 1, intervals[cur].first, intervals[cur].second, r);
        }
    }

    quitf(_ok, "Valid allocation with %d rooms", k);
}

```


# Batch 5

**Problem IDs:** 1197, 1666, 1667, 1668, 1678

Xử lý toàn bộ batch này; trả về đủ các khối `===CHECKER:ID===` … `===END===` cho mỗi ID.


---

## 1197 — Cycle Finding

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1197_Cycle Finding/`

- **Output file:** `Graph Algorithms/1197_Cycle Finding/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Negative-cycle check likely OK for normal CSES data, but permits non-simple closed walks and chooses minimum parallel-edge weight by vertex pair.


### statement_en.md


# 1197 - Cycle Finding

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given a directed graph, and your task is to find out if it contains a negative cycle, and also give an example of such a cycle.

# Input

The first input line has two integers $n$ and $m$: the number of nodes and edges. The nodes are numbered $1,2,\ldots,n$.

After this, the input has $m$ lines describing the edges. Each line has three integers $a$, $b$, and $c$: there is an edge from node $a$ to node $b$ whose length is $c$.

# Output

If the graph contains a negative cycle, print first "YES", and then the nodes in the cycle in their correct order. If there are several negative cycles, you can print any of them. If there are no negative cycles, print "NO".

# Constraints

* $1 \le n \le 2500$
* $1 \le m \le 5000$
* $1 \le a,b \le n$
* $-10^9 \le c \le 10^9$

# Example

Input:

```cpp
4 5
1 2 1
2 4 1
3 1 1
4 1 -3
4 3 -2
```

Output:

```cpp
YES
1 2 4 1
```


### checker.cpp (hiện tại)


```cpp

/*
 * Problem:      1197 Cycle Finding
 * Input read:   n, m; m directed edges (a, b, c)
 * Validity:     YES/NO matches existence; if YES: vertex sequence forms a directed
 *               cycle (repeated vertex, first equals last), each arc exists in the
 *               multigraph, total edge weight along cycle is negative
 * Optimality:   any valid negative cycle (no scalar from ans)
 * Complexity:   O(m + cycle length)
 */
#include "testlib.h"
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    map<pair<int, int>, vector<ll>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        ll c = inf.readLong();
        edges[{a, b}].push_back(c);
    }

    string ansToken = ans.readToken();
    if (ansToken != "YES" && ansToken != "NO")
        quitf(_fail, "Invalid judge answer token '%s'", ansToken.c_str());

    string outToken = ouf.readToken();
    if (outToken == "NO") {
        if (ansToken != "NO")
            quitf(_wa, "Contestant printed NO but a negative cycle exists");
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported no negative cycle");
    }

    if (outToken != "YES")
        quitf(_wa, "Expected YES or NO, got '%s'", outToken.c_str());
    if (ansToken == "NO")
        quitf(_wa, "Contestant printed YES but no negative cycle exists");

    vector<int> cycle;
    while (!ouf.seekEof())
        cycle.push_back(ouf.readInt(1, n, "vertex"));

    if ((int)cycle.size() < 2)
        quitf(_wa, "Cycle must have at least 2 vertices");

    int cycleStart = -1;
    vector<int> firstOccurrence(n + 1, -1);
    for (int i = 0; i < (int)cycle.size(); i++) {
        int v = cycle[i];
        if (firstOccurrence[v] != -1) {
            cycleStart = firstOccurrence[v];
            break;
        }
        firstOccurrence[v] = i;
    }
    if (cycleStart == -1)
        quitf(_wa, "Cycle must repeat a vertex");
    if (cycle[cycleStart] != cycle.back())
        quitf(_wa, "First and last vertices of cycle must match");

    vector<int> actualCycle;
    for (int i = cycleStart; i < (int)cycle.size(); i++)
        actualCycle.push_back(cycle[i]);

    ll totalWeight = 0;
    for (int i = 0; i + 1 < (int)actualCycle.size(); i++) {
        int u = actualCycle[i], v = actualCycle[i + 1];
        auto it = edges.find({u, v});
        if (it == edges.end())
            quitf(_wa, "No edge from %d to %d in the cycle", u, v);
        ll best = it->second[0];
        for (ll w : it->second)
            best = min(best, w);
        totalWeight += best;
    }

    if (totalWeight >= 0)
        quitf(_wa, "Sum of edge weights in cycle is %lld, not negative", totalWeight);

    quitf(_ok, "valid negative cycle with total weight %lld", totalWeight);
}

```


---

## 1666 — Building Roads

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1666_Building Roads/`

- **Output file:** `Graph Algorithms/1666_Building Roads/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Semantics OK, but contestant numbers are read unbounded.


### statement_en.md


# 1666 - Building Roads

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Byteland has $n$ cities, and $m$ roads between them. The goal is to construct new roads so that there is a route between any two cities.

Your task is to find out the minimum number of roads required, and also determine which roads should be built.

# Input

The first input line has two integers $n$ and $m$: the number of cities and roads. The cities are numbered $1,2,\dots,n$.

After that, there are $m$ lines describing the roads. Each line has two integers $a$ and $b$: there is a road between those cities.

A road always connects two different cities, and there is at most one road between any two cities.

# Output

First print an integer $k$: the number of required roads.

Then, print $k$ lines that describe the new roads. You can print any valid solution.

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
4 2
1 2
3 4
```

Output:

```cpp
1
2 3
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d roads but optimal is %d", k, k_ans);
    if (k < 0)
        quitf(_wa, "Number of roads must be non-negative, got %d", k);

    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n || b < 1 || b > n)
            quitf(_wa, "Road %d: cities %d %d out of range [1,%d]", i + 1, a, b, n);
        if (a == b)
            quitf(_wa, "Road %d: self-loop %d-%d", i + 1, a, b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 0; i < k_ans; i++)
        ans.readInt(), ans.readInt();

    vector<char> vis(n + 1, 0);
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            quitf(_wa, "City %d is still disconnected after adding roads", i);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid: %d roads make the graph connected", k);
}

```


---

## 1667 — Message Route

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1667_Message Route/`

- **Output file:** `Graph Algorithms/1667_Message Route/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Possible case where contestant prints `IMPOSSIBLE` becomes PE via integer read instead of clear WA.


### statement_en.md


# 1667 - Message Route

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Syrjälä's network has $n$ computers and $m$ connections. Your task is to find out if Uolevi can send a message to Maija, and if it is possible, what is the minimum number of computers on such a route.

# Input

The first input line has two integers $n$ and $m$: the number of computers and connections. The computers are numbered $1,2,\dots,n$. Uolevi's computer is $1$ and Maija's computer is $n$.

Then, there are $m$ lines describing the connections. Each line has two integers $a$ and $b$: there is a connection between those computers.

Every connection is between two different computers, and there is at most one connection between any two computers.

# Output

If it is possible to send a message, first print $k$: the minimum number of computers on a valid route. After this, print an example of such a route. You can print any valid solution.

If there are no routes, print "IMPOSSIBLE".

# Constraints

* $2 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
5 5
1 2
1 3
1 4
2 3
5 4
```

Output:

```cpp
3
1 4 5
```


### checker.cpp (hiện tại)


```cpp

/*
 * HEADER CONTRACT
 * Problem:      1667 Message Route
 * Input read:   n, m; m undirected edges (a, b)
 * Validity:     IMPOSSIBLE if no 1->n path; else k then route of k vertices in [1,n],
 *               route[0]=1, route[k-1]=n, consecutive vertices adjacent in input graph
 * Optimality:   k equals jury optimum (first token of ans)
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        int u = min(a, b), v = max(a, b);
        edges.insert({u, v});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a route exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    int kAns = stoi(ansTok);
    int k = ouf.readInt(2, n, "k");
    vector<int> route(k);
    for (int i = 0; i < k; i++)
        route[i] = ouf.readInt(1, n, format("route[%d]", i + 1).c_str());

    if (k != kAns)
        quitf(_wa, "not optimal: contestant k = %d, jury k = %d", k, kAns);

    if (route[0] != 1)
        quitf(_wa, "route must start at computer 1, contestant starts at %d", route[0]);
    if (route[k - 1] != n)
        quitf(_wa, "route must end at computer %d, contestant ends at %d", n, route[k - 1]);

    for (int i = 0; i + 1 < k; i++) {
        int u = route[i], v = route[i + 1];
        int a = min(u, v), b = max(u, v);
        if (!edges.count({a, b}))
            quitf(_wa, "no connection between %d and %d on route step %d", u, v, i + 1);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid shortest route of length %d", k);
}

```


---

## 1668 — Building Teams

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1668_Building Teams/`

- **Output file:** `Graph Algorithms/1668_Building Teams/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Same sentinel/verdict risk as `1667`.


### statement_en.md


# 1668 - Building Teams

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ pupils in Uolevi's class, and $m$ friendships between them. Your task is to divide the pupils into two teams in such a way that no two pupils in a team are friends. You can freely choose the sizes of the teams.

# Input

The first input line has two integers $n$ and $m$: the number of pupils and friendships. The pupils are numbered $1,2,\dots,n$.

Then, there are $m$ lines describing the friendships. Each line has two integers $a$ and $b$: pupils $a$ and $b$ are friends.

Every friendship is between two different pupils. You can assume that there is at most one friendship between any two pupils.

# Output

Print an example of how to build the teams. For each pupil, print "1" or "2" depending on to which team the pupil will be assigned. You can print any valid team.

If there are no solutions, print "IMPOSSIBLE".

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
5 3
1 2
1 3
4 5
```

Output:

```cpp
1 2 2 1 2
```


### checker.cpp (hiện tại)


```cpp

/*
 * HEADER CONTRACT
 * Problem:      1668 Building Teams
 * Input read:   n, m; m undirected friendships (a, b)
 * Validity:     IMPOSSIBLE if not 2-colorable; else n team labels in {1,2},
 *               no friendship connects two pupils in the same team
 * Optimality:   any valid 2-coloring (no scalar from ans)
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<pair<int, int>> friendships;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        friendships.push_back({a, b});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a valid team assignment exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    vector<int> team(n + 1);
    team[1] = ouf.readInt(1, 2, "team[1]");
    for (int i = 2; i <= n; i++)
        team[i] = ouf.readInt(1, 2, format("team[%d]", i).c_str());

    for (auto [a, b] : friendships) {
        if (team[a] == team[b])
            quitf(_wa, "friendship %d-%d connects pupils in the same team %d", a, b, team[a]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid 2-coloring for %d pupils", n);
}

```


---

## 1678 — Round Trip II

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1678_Round Trip II/`

- **Output file:** `Graph Algorithms/1678_Round Trip II/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Lower bound should defensively be `k >= 3`; valid input excludes self-loops, so this is not a confirmed semantic false-AC. Also has possible `IMPOSSIBLE` -> PE branch.


### statement_en.md


# 1678 - Round Trip II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Byteland has $n$ cities and $m$ flight connections. Your task is to design a round trip that begins in a city, goes through one or more other cities, and finally returns to the starting city. Every intermediate city on the route has to be distinct.

# Input

The first input line has two integers $n$ and $m$: the number of cities and flights. The cities are numbered $1,2,\dots,n$.

Then, there are $m$ lines describing the flights. Each line has two integers $a$ and $b$: there is a flight connection from city $a$ to city $b$. All connections are one-way flights from a city to another city.

# Output

First print an integer $k$: the number of cities on the route. Then print $k$ cities in the order they will be visited. You can print any valid solution.

If there are no solutions, print "IMPOSSIBLE".

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
4 5
1 3
2 1
2 4
3 2
3 4
```

Output:

```cpp
4
2 1 3 2
```


### checker.cpp (hiện tại)


```cpp

/*
 * HEADER CONTRACT
 * Problem:      1678 Round Trip II
 * Input read:   n, m; m directed flights (a, b)
 * Validity:     IMPOSSIBLE if no directed cycle; else k then k cities in [1,n],
 *               first equals last, intermediate cities distinct,
 *               each consecutive pair is a directed flight in the input
 * Optimality:   any valid directed cycle (no scalar from ans)
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    multiset<pair<int, int>> flights;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        flights.insert({a, b});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a directed cycle exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    int k = ouf.readInt(2, n + 1, "k");
    vector<int> cycle(k);
    for (int i = 0; i < k; i++)
        cycle[i] = ouf.readInt(1, n, format("city[%d]", i + 1).c_str());

    if (cycle[0] != cycle[k - 1])
        quitf(_wa, "cycle must start and end at the same city (got %d and %d)",
              cycle[0], cycle[k - 1]);

    multiset<pair<int, int>> remaining = flights;
    for (int i = 0; i + 1 < k; i++) {
        int u = cycle[i], v = cycle[i + 1];
        auto it = remaining.find({u, v});
        if (it == remaining.end())
            quitf(_wa, "no directed flight from %d to %d on cycle step %d", u, v, i + 1);
        remaining.erase(it);
    }

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < k - 1; i++) {
        if (seen[cycle[i]])
            quitf(_wa, "city %d appears more than once among intermediate cities", cycle[i]);
        seen[cycle[i]] = true;
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid directed cycle of length %d", k);
}

```


# Batch 6

**Problem IDs:** 1679, 1682, 1683, 1685, 1689

Xử lý toàn bộ batch này; trả về đủ các khối `===CHECKER:ID===` … `===END===` cho mỗi ID.


---

## 1679 — Course Schedule

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1679_Course Schedule/`

- **Output file:** `Graph Algorithms/1679_Course Schedule/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Same sentinel/verdict risk as `1667`.


### statement_en.md


# 1679 - Course Schedule

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You have to complete $n$ courses. There are $m$ requirements of the form "course $a$ has to be completed before course $b$". Your task is to find an order in which you can complete the courses.

# Input

The first input line has two integers $n$ and $m$: the number of courses and requirements. The courses are numbered $1,2,\dots,n$.

After this, there are $m$ lines describing the requirements. Each line has two integers $a$ and $b$: course $a$ has to be completed before course $b$.

# Output

Print an order in which you can complete the courses. You can print any valid order that includes all the courses.

If there are no solutions, print "IMPOSSIBLE".

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
5 3
1 2
3 1
4 5
```

Output:

```cpp
3 4 1 5 2
```


### checker.cpp (hiện tại)


```cpp

/*
 * HEADER CONTRACT
 * Problem:      1679 Course Schedule
 * Input read:   n, m; m requirements (a, b): course a before course b
 * Validity:     IMPOSSIBLE if no topological order; else permutation of 1..n
 *               with pos[a] < pos[b] for every requirement
 * Optimality:   any valid topological order (no scalar from ans)
 * Complexity:   O(n + m) time, O(n + m) memory
 */
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<pair<int, int>> requirements;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        requirements.push_back({a, b});
    }

    string ansTok = ans.readToken();
    if (ansTok == "IMPOSSIBLE") {
        string oufTok = ouf.readToken();
        if (oufTok != "IMPOSSIBLE")
            quitf(_wa, "jury answer is IMPOSSIBLE but contestant printed \"%s\" "
                       "(claims a valid course order exists)",
                  compress(oufTok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    vector<int> order(n);
    order[0] = ouf.readInt(1, n, "course[1]");
    for (int i = 1; i < n; i++)
        order[i] = ouf.readInt(1, n, format("course[%d]", i + 1).c_str());

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; i++) {
        if (seen[order[i]])
            quitf(_wa, "course %d appears more than once in the order", order[i]);
        seen[order[i]] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!seen[i])
            quitf(_wa, "course %d is missing from the order", i);
    }

    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++)
        pos[order[i]] = i;

    for (auto [a, b] : requirements) {
        if (pos[a] >= pos[b])
            quitf(_wa, "requirement violated: course %d must come before course %d", a, b);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid topological order of %d courses", n);
}

```


---

## 1682 — Flight Routes Check

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1682_Flight Routes Check/`

- **Output file:** `Graph Algorithms/1682_Flight Routes Check/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Counterexample vertices are read unbounded.


### statement_en.md


# 1682 - Flight Routes Check

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ cities and $m$ flight connections. Your task is to check if you can travel from any city to any other city using the available flights.

# Input

The first input line has two integers $n$ and $m$: the number of cities and flights. The cities are numbered $1,2,\dots,n$.

After this, there are $m$ lines describing the flights. Each line has two integers $a$ and $b$: there is a flight from city $a$ to city $b$. All flights are one-way flights.

# Output

Print "YES" if all routes are possible, and "NO" otherwise. In the latter case also print two cities $a$ and $b$ such that you cannot travel from city $a$ to city $b$. If there are several possible solutions, you can print any of them.

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
4 5
1 2
2 3
3 1
1 4
3 4
```

Output:

```cpp
NO
4 2
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> g(n + 1), rg(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    string ansFlag = ans.readToken();
    if (ansFlag != "YES" && ansFlag != "NO")
        quitf(_fail, "Invalid judge answer token '%s'", ansFlag.c_str());

    string outFlag = ouf.readToken();
    if (outFlag != "YES" && outFlag != "NO")
        quitf(_wa, "Expected YES or NO, got '%s'", outFlag.c_str());

    if (outFlag == "NO") {
        if (ansFlag != "NO")
            quitf(_wa, "Output is NO but all routes are possible");
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n || b < 1 || b > n)
            quitf(_wa, "Cities %d %d out of range [1,%d]", a, b, n);

        vector<char> vis(n + 1, 0);
        queue<int> q;
        q.push(a);
        vis[a] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
        if (vis[b])
            quitf(_wa, "Path from %d to %d exists but output is NO", a, b);

        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correct: no path from %d to %d", a, b);
    }

    if (ansFlag == "NO")
        quitf(_wa, "All routes are possible but output is YES");

    vector<char> vis1(n + 1, 0), vis2(n + 1, 0);
    queue<int> q;
    q.push(1);
    vis1[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (!vis1[v]) {
                vis1[v] = 1;
                q.push(v);
            }
        }
    }
    q.push(1);
    vis2[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : rg[u]) {
            if (!vis2[v]) {
                vis2[v] = 1;
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis1[i])
            quitf(_wa, "City %d not reachable from 1", i);
        if (!vis2[i])
            quitf(_wa, "City 1 not reachable from %d", i);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Graph is strongly connected");
}

```


---

## 1683 — Planets and Kingdoms

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1683_Planets and Kingdoms/`

- **Output file:** `Graph Algorithms/1683_Planets and Kingdoms/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Contestant component labels are read unbounded; DFS recursion on `n = 1e5` risks stack overflow.


### statement_en.md


# 1683 - Planets and Kingdoms

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A game has $n$ planets, connected by $m$ teleporters. Two planets $a$ and $b$ belong to the same kingdom exactly when there is a route both from $a$ to $b$ and from $b$ to $a$. Your task is to determine for each planet its kingdom.

# Input

The first input line has two integers $n$ and $m$: the number of planets and teleporters. The planets are numbered $1,2,\dots,n$.

After this, there are $m$ lines describing the teleporters. Each line has two integers $a$ and $b$: you can travel from planet $a$ to planet $b$ through a teleporter.

# Output

First print an integer $k$: the number of kingdoms. After this, print for each planet a kingdom label between $1$ and $k$. You can print any valid solution.

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
5 6
1 2
2 3
3 1
3 4
4 5
5 4
```

Output:

```cpp
2
1 1 1 2 2
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> g, rg;
vector<int> order, comp;
vector<char> seen;
int n;

void dfs1(int u) {
    seen[u] = 1;
    for (int v : g[u]) {
        if (!seen[v])
            dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u, int id) {
    comp[u] = id;
    for (int v : rg[u]) {
        if (!comp[v])
            dfs2(v, id);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    int m = inf.readInt();
    g.assign(n + 1, {});
    rg.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d kingdoms but optimal is %d", k, k_ans);
    if (k < 1 || k > n)
        quitf(_wa, "Number of kingdoms %d out of range [1,%d]", k, n);

    vector<int> label(n + 1);
    vector<bool> used(k + 1, false);
    for (int i = 1; i <= n; i++) {
        label[i] = ouf.readInt();
        if (label[i] < 1 || label[i] > k)
            quitf(_wa, "Kingdom label for planet %d is %d, must be in [1,%d]", i, label[i], k);
        used[label[i]] = true;
    }

    for (int j = 1; j <= k; j++) {
        if (!used[j])
            quitf(_wa, "Kingdom %d is not assigned to any planet", j);
    }

    for (int i = 1; i <= n; i++)
        ans.readInt();

    order.clear();
    seen.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (!seen[i])
            dfs1(i);
    }
    reverse(order.begin(), order.end());

    comp.assign(n + 1, 0);
    int compCnt = 0;
    for (int u : order) {
        if (!comp[u])
            dfs2(u, ++compCnt);
    }

    vector<int> compLabel(compCnt + 1, -1);
    vector<int> labelComp(k + 1, -1);
    for (int i = 1; i <= n; i++) {
        int c = comp[i];
        int l = label[i];
        if (compLabel[c] == -1)
            compLabel[c] = l;
        else if (compLabel[c] != l)
            quitf(_wa, "Planets in the same kingdom (SCC) have different labels");
        if (labelComp[l] == -1)
            labelComp[l] = c;
        else if (labelComp[l] != c)
            quitf(_wa, "Planets in the same labeled kingdom belong to different SCCs");
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid kingdom assignment: %d kingdoms", k);
}

```


---

## 1685 — New Flight Routes

- **Severity:** `RISK`

- **Folder:** `Advanced Graph Problems/1685_New Flight Routes/`

- **Output file:** `Advanced Graph Problems/1685_New Flight Routes/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Semantics OK, but SCC DFS recursion on `n = 1e5` and unbounded output reads.


### statement_en.md


# 1685 - New Flight Routes

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ cities and $m$ flight connections between them. Your task is to add new flights so that it will be possible to travel from any city to any other city. What is the minimum number of new flights required?

# Input

The first input line has two integers $n$ and $m$: the number of cities and flights. The cities are numbered $1,2,\dots,n$.

After this, there are $m$ lines describing the flights. Each line has two integers $a$ and $b$: there is a flight from city $a$ to city $b$. All flights are one-way flights.

# Output

First print an integer $k$: the required number of new flights. After this, print $k$ lines describing the new flights. You can print any valid solution.

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
4 5
1 2
2 3
3 1
1 4
3 4
```

Output:

```cpp
1
4 2
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
using namespace std;

void dfs1(int u, const vector<vector<int>>& g, vector<bool>& vis, vector<int>& order) {
    vis[u] = true;
    for (int v : g[u])
        if (!vis[v])
            dfs1(v, g, vis, order);
    order.push_back(u);
}

void dfs2(int u, const vector<vector<int>>& rg, vector<bool>& vis, int& cnt) {
    vis[u] = true;
    ++cnt;
    for (int v : rg[u])
        if (!vis[v])
            dfs2(v, rg, vis, cnt);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> g(n + 1), rg(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d new flights but optimal is %d", k, k_ans);
    if (k < 0)
        quitf(_wa, "k=%d is negative", k);

    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n)
            quitf(_wa, "City %d out of range", a);
        if (b < 1 || b > n)
            quitf(_wa, "City %d out of range", b);
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    vector<bool> vis(n + 1, false);
    vector<int> order;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs1(i, g, vis, order);

    fill(vis.begin(), vis.end(), false);
    int scc = 0;
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];
        if (!vis[v]) {
            int cnt = 0;
            dfs2(v, rg, vis, cnt);
            if (cnt > 0)
                ++scc;
        }
    }
    if (scc != 1)
        quitf(_wa, "Resulting graph has %d SCCs (not strongly connected)", scc);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid minimum solution with %d new flights", k);
}

```


---

## 1689 — Knights Tour

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1689_Knights Tour/`

- **Output file:** `Graph Algorithms/1689_Knights Tour/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Board values are read with bare `ouf.readInt()` before range checks.


### statement_en.md


# 1689 - Knights Tour

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given a starting position of a knight on an $8 \times 8$ chessboard, your task is to find a sequence of moves such that it visits every square exactly once.

On each move, the knight may either move two steps horizontally and one step vertically, or one step horizontally and two steps vertically.

# Input

The only line has two integers $x$ and $y$: the knight's starting position.

# Output

Print a grid that shows how the knight moves (according to the example). You can print any valid solution.

# Constraints

* $1 \le x,y \le 8$

# Example

Input:

```cpp
2 1
```

Output:

```cpp
8 1 10 13 6 3 20 17 
11 14 7 2 19 16 23 4 
26 9 12 15 24 5 18 21 
49 58 25 28 51 22 33 30 
40 27 50 59 32 29 52 35 
57 48 41 44 37 34 31 62 
42 39 46 55 60 63 36 53 
47 56 43 38 45 54 61 64
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int x = inf.readInt();
    int y = inf.readInt();
    vector<vector<int>> grid(8, vector<int>(8));
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            grid[r][c] = ouf.readInt();
            if (grid[r][c] < 1 || grid[r][c] > 64)
                quitf(_wa, "Grid value %d out of range [1,64] at (%d,%d)", grid[r][c], r + 1, c + 1);
        }
    }
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    vector<bool> seen(65, false);
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            int val = grid[r][c];
            if (seen[val])
                quitf(_wa, "Number %d appears more than once", val);
            seen[val] = true;
        }
    }

    vector<pair<int, int>> pos(65);
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++)
            pos[grid[r][c]] = {r, c};
    }

    if (pos[1].first != y - 1 || pos[1].second != x - 1)
        quitf(_wa, "Starting position must be (%d,%d), got (%d,%d)",
              x, y, pos[1].second + 1, pos[1].first + 1);

    for (int step = 1; step < 64; step++) {
        int r1 = pos[step].first, c1 = pos[step].second;
        int r2 = pos[step + 1].first, c2 = pos[step + 1].second;
        int dr = abs(r1 - r2), dc = abs(c1 - c2);
        if (!((dr == 2 && dc == 1) || (dr == 1 && dc == 2)))
            quitf(_wa,
                  "Move from step %d to %d ((%d,%d) to (%d,%d)) is not a valid knight move",
                  step, step + 1, c1 + 1, r1 + 1, c2 + 1, r2 + 1);
    }

    quitf(_ok, "Valid knight's tour");
}

```


# Batch 7

**Problem IDs:** 1695, 1696, 1698, 1704, 1709

Xử lý toàn bộ batch này; trả về đủ các khối `===CHECKER:ID===` … `===END===` cho mỗi ID.


---

## 1695 — Police Chase

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1695_Police Chase/`

- **Output file:** `Graph Algorithms/1695_Police Chase/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Cut size/endpoints are read unbounded.


### statement_en.md


# 1695 - Police Chase

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Kaaleppi has just robbed a bank and is now heading to the harbor. However, the police wants to stop him by closing some streets of the city.

What is the minimum number of streets that should be closed so that there is no route between the bank and the harbor?

# Input

The first input line has two integers $n$ and $m$: the number of crossings and streets. The crossings are numbered $1,2,\dots,n$. The bank is located at crossing $1$, and the harbor is located at crossing $n$.

After this, there are $m$ lines that describing the streets. Each line has two integers $a$ and $b$: there is a street between crossings $a$ and $b$. All streets are two-way streets, and there is at most one street between two crossings.

# Output

First print an integer $k$: the minimum number of streets that should be closed. After this, print $k$ lines describing the streets. You can print any valid solution.

# Constraints

* $2 \le n \le 500$
* $1 \le m \le 1000$
* $1 \le a,b \le n$

# Example

Input:

```cpp
4 5
1 2
1 3
2 3
3 4
1 4
```

Output:

```cpp
2
3 4
1 4
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges.push_back({a, b});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d streets but optimal is %d", k, k_ans);
    if (k < 0 || k > m)
        quitf(_wa, "k=%d out of range [0,%d]", k, m);

    set<pair<int, int>> closedEdges;
    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n || b < 1 || b > n)
            quitf(_wa, "Edge %d-%d out of range", a, b);
        int mn = min(a, b), mx = max(a, b);
        bool found = false;
        for (auto [u, v] : edges) {
            if ((u == a && v == b) || (u == b && v == a)) {
                found = true;
                break;
            }
        }
        if (!found)
            quitf(_wa, "Street %d-%d does not exist in the city", a, b);
        if (closedEdges.count({mn, mx}))
            quitf(_wa, "Street %d-%d listed twice", mn, mx);
        closedEdges.insert({mn, mx});
    }

    vector<bool> vis(n + 1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == n)
            break;
        for (int v : adj[u]) {
            int mn = min(u, v), mx = max(u, v);
            if (!vis[v] && !closedEdges.count({mn, mx})) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    if (vis[n])
        quitf(_wa, "Route from 1 to %d still exists after closing %d streets", n, k);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid minimum cut of size %d", k);
}

```


---

## 1696 — School Dance

- **Severity:** `RISK`

- **Folder:** `Graph Algorithms/1696_School Dance/`

- **Output file:** `Graph Algorithms/1696_School Dance/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Matching size/endpoints are read unbounded.


### statement_en.md


# 1696 - School Dance

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There are $n$ boys and $m$ girls in a school. Next week a school dance will be organized. A dance pair consists of a boy and a girl, and there are $k$ potential pairs.

Your task is to find out the maximum number of dance pairs and show how this number can be achieved.

# Input

The first input line has three integers $n$, $m$ and $k$: the number of boys, girls, and potential pairs. The boys are numbered $1,2,\dots,n$, and the girls are numbered $1,2,\dots,m$.

After this, there are $k$ lines describing the potential pairs. Each line has two integers $a$ and $b$: boy $a$ and girl $b$ are willing to dance together.

# Output

First print one integer $r$: the maximum number of dance pairs. After this, print $r$ lines describing the pairs. You can print any valid solution.

# Constraints

* $1 \le n,m \le 500$
* $1 \le k \le 1000$
* $1 \le a \le n$
* $1 \le b \le m$

# Example

Input:

```cpp
3 2 4
1 1
1 2
2 1
3 1
```

Output:

```cpp
2
1 2
3 1
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    int k = inf.readInt();
    set<pair<int, int>> possiblePairs;
    for (int i = 0; i < k; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        possiblePairs.insert({a, b});
    }

    int r_ans = ans.readInt();
    int r = ouf.readInt();
    if (r != r_ans)
        quitf(_wa, "Claimed %d pairs but optimal is %d", r, r_ans);
    if (r < 0 || r > min(n, m))
        quitf(_wa, "Number of pairs %d out of range [0,%d]", r, min(n, m));

    set<int> usedBoys, usedGirls;
    set<pair<int, int>> answerPairs;
    for (int i = 0; i < r; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n)
            quitf(_wa, "Boy %d out of range [1,%d]", a, n);
        if (b < 1 || b > m)
            quitf(_wa, "Girl %d out of range [1,%d]", b, m);
        if (!possiblePairs.count({a, b}))
            quitf(_wa, "Pair (%d,%d) is not a potential pair", a, b);
        if (usedBoys.count(a))
            quitf(_wa, "Boy %d paired more than once", a);
        if (usedGirls.count(b))
            quitf(_wa, "Girl %d paired more than once", b);
        if (answerPairs.count({a, b}))
            quitf(_wa, "Duplicate pair (%d,%d)", a, b);
        usedBoys.insert(a);
        usedGirls.insert(b);
        answerPairs.insert({a, b});
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid maximum matching of size %d", r);
}

```


---

## 1698 — Swap Round Sorting

- **Severity:** `RISK`

- **Folder:** `Additional Problems II/1698_Swap Round Sorting/`

- **Output file:** `Additional Problems II/1698_Swap Round Sorting/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** `k`, round sizes, and swaps are read unbounded; hostile `cnt` can drive huge loops.


### statement_en.md


# 1698 - Swap Round Sorting

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given an array containing a permutation of numbers $1,2,\dots,n$, and your task is to sort the array using *swap rounds*. On each swap round, you can choose any number of distinct pairs of elements and swap each pair.

Your task is to find the minimum number of rounds and show how you can choose the pairs in each round.

# Input

The first input line has an integer $n$: the size of the array.

The second line has $n$ integers $x\_1,x\_2,\dots,x\_n$: the initial permutation.

# Output

First print an integer $k$: the minimum number of rounds.

Then, for each round, print the number of swaps and the indices of each swap. You can print any valid solution.

# Constraints

* $1 \le n \le 2 \cdot 10^5$

# Example

Input:

```cpp
5
5 2 1 3 4
```

Output:

```cpp
2
2
1 3
4 5
1
3 5
```

*Explanation*: The initial array is $[5,2,1,3,4]$. After round $1$, the array becomes $[1,2,5,4,3]$. After round $2$, the array becomes $[1,2,3,4,5]$.


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> perm(n + 1);
    for (int i = 1; i <= n; i++)
        perm[i] = inf.readInt();

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Minimum rounds is %d, got %d", k_ans, k);
    if (k < 0)
        quitf(_wa, "Number of rounds must be non-negative, got %d", k);

    vector<int> cur = perm;
    for (int round = 0; round < k; round++) {
        int cnt = ouf.readInt();
        if (cnt < 0)
            quitf(_wa, "Round %d: number of swaps must be non-negative, got %d", round + 1, cnt);

        vector<bool> used(n + 1, false);
        for (int s = 0; s < cnt; s++) {
            int i = ouf.readInt();
            int j = ouf.readInt();
            if (i < 1 || i > n)
                quitf(_wa, "Round %d swap %d: index i=%d out of bounds", round + 1, s + 1, i);
            if (j < 1 || j > n)
                quitf(_wa, "Round %d swap %d: index j=%d out of bounds", round + 1, s + 1, j);
            if (i == j)
                quitf(_wa, "Round %d swap %d: cannot swap same index", round + 1, s + 1);
            if (used[i] || used[j])
                quitf(_wa, "Round %d swap %d: index %d or %d already used in this round",
                      round + 1, s + 1, i, j);
            used[i] = used[j] = true;
            swap(cur[i], cur[j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (cur[i] != i)
            quitf(_wa, "After all rounds, position %d has value %d, expected %d", i, cur[i], i);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal sorting with %d rounds", k);
}

```


---

## 1704 — Network Renovation

- **Severity:** `RISK`

- **Folder:** `Advanced Graph Problems/1704_Network Renovation/`

- **Output file:** `Advanced Graph Problems/1704_Network Renovation/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Semantics OK, but Tarjan recursion on `n = 1e5` and unbounded output reads.


### statement_en.md


# 1704 - Network Renovation

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Syrjälä's network consists of $n$ computers and $n-1$ connections between them. It is possible to send data between any two computers.

However, if any connection breaks down, it will no longer be possible to send data between some computers. Your task is to add the minimum number of new connections in such a way that you can still send data between any two computers even if any single connection breaks down.

# Input

The first input line has an integer $n$: the number of computers. The computers are numbered $1,2,\dots,n$.

After this, there are $n-1$ lines describing the connections. Each line has two integers $a$ and $b$: there is a connection between computers $a$ and $b$.

# Output

First print an integer $k$: the minimum number of new connections. After this, print $k$ lines describing the connections. You can print any valid solution.

# Constraints

* $3 \le n \le 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
5
1 2
1 3
3 4
3 5
```

Output:

```cpp
2
2 4
4 5
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct BridgeChecker {
    vector<vector<int>> g;
    vector<pair<int, int>> edges;
    vector<int> tin, low;
    int timer = 0;
    bool has_bridge = false;

    void add_edge(int a, int b) {
        int id = (int)edges.size();
        edges.push_back({a, b});
        g[a].push_back(id);
        g[b].push_back(id);
    }

    int other(int u, int ei) const {
        return edges[ei].first ^ edges[ei].second ^ u;
    }

    void dfs(int u, int pe) {
        tin[u] = low[u] = ++timer;
        for (int ei : g[u]) {
            if (ei == pe)
                continue;
            int v = other(u, ei);
            if (tin[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, ei);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u])
                    has_bridge = true;
            }
        }
    }

    void run(int n) {
        tin.assign(n + 1, 0);
        low.assign(n + 1, 0);
        timer = 0;
        has_bridge = false;
        dfs(1, -1);
    }
};

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    BridgeChecker bc;
    bc.g.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        bc.add_edge(a, b);
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d new connections but optimal is %d", k, k_ans);
    if (k < 0)
        quitf(_wa, "k=%d is negative", k);

    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n)
            quitf(_wa, "Computer %d out of range", a);
        if (b < 1 || b > n)
            quitf(_wa, "Computer %d out of range", b);
        if (a == b)
            quitf(_wa, "Cannot connect a computer to itself");
        bc.add_edge(a, b);
    }

    bc.run(n);
    if (bc.has_bridge)
        quitf(_wa, "Graph still has bridges after adding new connections");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid minimum solution with %d new connections", k);
}

```


---

## 1709 — Coin Grid

- **Severity:** `RISK`

- **Folder:** `Additional Problems II/1709_Coin Grid/`

- **Output file:** `Additional Problems II/1709_Coin Grid/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Move count/type/index are read unbounded.


### statement_en.md


# 1709 - Coin Grid

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is an $n \times n$ grid whose each square is empty or has a coin. On each move, you can remove all coins in a row or column.

What is the minimum number of moves after which the grid is empty?

# Input

The first input line has an integer $n$: the size of the grid. The rows and columns are numbered $1,2,\dots,n$.

After this, there are $n$ lines describing the grid. Each line has $n$ characters: each character is either `.` (empty) or `o` (coin).

# Output

First print an integer $k$: the minimum number of moves. After this, print $k$ lines describing the moves.

On each line, first print $1$ (row) or $2$ (column), and then the number of a row or column. You can print any valid solution.

# Constraints

* $1 \le n \le 100$

# Example

Input:

```cpp
3
..o
o.o
...
```

Output:

```cpp
2
1 2
2 3
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
        grid[i] = inf.readToken();

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Minimum number of moves is %d, got %d", k_ans, k);
    if (k < 0)
        quitf(_wa, "Number of moves must be non-negative, got %d", k);

    vector<vector<bool>> removed(n, vector<bool>(n, false));
    for (int move = 0; move < k; move++) {
        int type = ouf.readInt();
        int idx = ouf.readInt();
        if (type != 1 && type != 2)
            quitf(_wa, "Move %d: type must be 1 (row) or 2 (column), got %d", move + 1, type);
        if (idx < 1 || idx > n)
            quitf(_wa, "Move %d: index out of bounds [1,%d], got %d", move + 1, n, idx);
        idx--;

        if (type == 1) {
            for (int j = 0; j < n; j++) removed[idx][j] = true;
        } else {
            for (int i = 0; i < n; i++) removed[i][idx] = true;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'o' && !removed[i][j])
                quitf(_wa, "Coin at row %d, column %d not removed", i + 1, j + 1);
        }
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "All coins removed in optimal %d moves", k);
}

```


# Batch 8

**Problem IDs:** 1756, 2079, 2129, 2131, 2165

Xử lý toàn bộ batch này; trả về đủ các khối `===CHECKER:ID===` … `===END===` cho mỗi ID.


---

## 1756 — Acyclic Graph Edges

- **Severity:** `RISK`

- **Folder:** `Advanced Graph Problems/1756_Acyclic Graph Edges/`

- **Output file:** `Advanced Graph Problems/1756_Acyclic Graph Edges/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Edge endpoints are read unbounded.


### statement_en.md


# 1756 - Acyclic Graph Edges

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given an undirected graph, your task is to choose a direction for each edge so that the resulting directed graph is acyclic.

# Input

The first input line has two integers $n$ and $m$: the number of nodes and edges. The nodes are numbered $1,2,\dots,n$.

After this, there are $m$ lines describing the edges. Each line has two distinct integers $a$ and $b$: there is an edge between nodes $a$ and $b$.

# Output

Print $m$ lines describing the directions of the edges. Each line has two integers $a$ and $b$: there is an edge from node $a$ to node $b$. You can print any valid solution.

# Constraints

* $1 \le n \le 10^5$
* $1 \le m \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
3 3
1 2
2 3
3 1
```

Output:

```cpp
1 2
3 2
3 1
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    map<pair<int, int>, int> edgeCnt;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        pair<int, int> key = {min(a, b), max(a, b)};
        edgeCnt[key]++;
    }

    vector<vector<int>> dg(n + 1);
    for (int i = 0; i < m; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n || b < 1 || b > n)
            quitf(_wa, "Node %d or %d out of range [1,%d]", a, b, n);
        if (a == b)
            quitf(_wa, "Self-loop not allowed: %d %d", a, b);

        pair<int, int> key = {min(a, b), max(a, b)};
        if (!edgeCnt.count(key) || edgeCnt[key] == 0)
            quitf(_wa, "Edge %d %d does not exist in the original graph", a, b);
        edgeCnt[key]--;
        dg[a].push_back(b);
    }

    for (auto [key, cnt] : edgeCnt) {
        if (cnt != 0)
            quitf(_wa, "Not all original edges are oriented");
    }

    for (int i = 0; i < m; i++)
        ans.readInt(), ans.readInt();

    vector<int> state(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (state[i] != 0)
            continue;
        vector<int> stack = {i};
        while (!stack.empty()) {
            int u = stack.back();
            if (state[u] == 0) {
                state[u] = 1;
                for (int v : dg[u]) {
                    if (state[v] == 1)
                        quitf(_wa, "Directed graph contains a cycle");
                    if (state[v] == 0)
                        stack.push_back(v);
                }
            } else if (state[u] == 1) {
                state[u] = 2;
                stack.pop_back();
            } else {
                stack.pop_back();
            }
        }
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid acyclic orientation of %d edges", m);
}

```


---

## 2079 — Finding a Centroid

- **Severity:** `RISK`

- **Folder:** `Tree Algorithms/2079_Finding a Centroid/`

- **Output file:** `Tree Algorithms/2079_Finding a Centroid/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Centroid invariant OK, but output node is unbounded and recursive DFS may overflow stack at `n = 2e5`.


### statement_en.md


# 2079 - Finding a Centroid

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given a tree of $n$ nodes, your task is to find a *centroid*, i.e., a node such that when it is appointed the root of the tree, each subtree has at most $\lfloor n/2 \rfloor$ nodes.

# Input

The first input line contains an integer $n$: the number of nodes. The nodes are numbered $1,2,…,n$.

Then there are $n-1$ lines describing the edges. Each line contains two integers $a$ and $b$: there is an edge between nodes $a$ and $b$.

# Output

Print one integer: a centroid node. If there are several possibilities, you can choose any of them.

# Constraints

* $1 \le n \le 2 \cdot 10^5$
* $1 \le a,b \le n$

# Example

Input:

```cpp
5
1 2
2 3
3 4
3 5
```

Output:

```cpp
3
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int c = ouf.readInt();
    if (c < 1 || c > n)
        quitf(_wa, "Node %d out of range [1,%d]", c, n);

    vector<int> sz(n + 1, 0);
    function<void(int, int)> dfs = [&](int u, int p) {
        sz[u] = 1;
        for (int v : g[u]) {
            if (v == p) continue;
            dfs(v, u);
            sz[u] += sz[v];
        }
    };
    dfs(c, -1);

    for (int v : g[c]) {
        if (sz[v] > n / 2)
            quitf(_wa, "Node %d is not a centroid: subtree through neighbor %d has size %d",
                  c, v, sz[v]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid centroid %d", c);
}

```


---

## 2129 — Task Assignment

- **Severity:** `RISK`

- **Folder:** `Advanced Techniques/2129_Task Assignment/`

- **Output file:** `Advanced Techniques/2129_Task Assignment/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Assignment semantics OK, but cost/employee/task are read unbounded.


### statement_en.md


# 2129 - Task Assignment

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

A company has $n$ employees and there are $n$ tasks that need to be done. We know for each employee the cost of carrying out each task. Every employee should be assigned to exactly one task. What is the minimum total cost if we assign the tasks optimally and how could they be assigned?

# Input

The first input line has one integer $n$: the number of employees and the number of tasks that need to be done.

After this, there are $n$ lines each consisting of $n$ integers. The $i$th line consists of integers $c\_{i1},c\_{i2},\ldots,c\_{in}$: the cost of each task when it is assigned to the $i$th employee.

# Output

First print the minimum total cost.

Then print $n$ lines each consisting of two integers $a$ and $b$: you assign the $b$th task to the $a$th employee.

If there are multiple solutions you can print any of them.

# Constraints

* $1 \le n \le 200$
* $1 \le c\_{ij} \le 1000$

# Example

Input:

```cpp
4
17 8 16 9
7 15 12 19
6 9 10 11
14 7 13 10
```

Output:

```cpp
33
1 4
2 1
3 3
4 2
```

Explanation: The minimum total cost is $33$. We can reach this by assigning employee 1 task 4, employee 2 task 1, employee 3 task 3 and employee 4 task 2. This will cost $9 + 7 + 10 + 7 = 33$.


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cost[i][j] = inf.readInt();
    }

    long long optimal = ans.readInt();
    int claimed_cost = ouf.readInt();
    if ((long long)claimed_cost != optimal)
        quitf(_wa, "Minimum total cost is %lld, got %d", optimal, claimed_cost);

    vector<int> emp_of_task(n, 0);
    vector<int> task_of_emp(n, 0);
    long long total = 0;

    for (int i = 0; i < n; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > n)
            quitf(_wa, "Employee %d out of range", a);
        if (b < 1 || b > n)
            quitf(_wa, "Task %d out of range", b);
        if (task_of_emp[a - 1] != 0)
            quitf(_wa, "Employee %d assigned more than one task", a);
        if (emp_of_task[b - 1] != 0)
            quitf(_wa, "Task %d assigned to more than one employee", b);
        task_of_emp[a - 1] = b;
        emp_of_task[b - 1] = a;
        total += cost[a - 1][b - 1];
    }

    if (total != optimal)
        quitf(_wa, "Claimed total cost %d, but actual sum of assignments is %lld",
              claimed_cost, total);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal assignment with total cost %lld", total);
}

```


---

## 2131 — Grid Puzzle II

- **Severity:** `RISK`

- **Folder:** `Additional Problems II/2131_Grid Puzzle II/`

- **Output file:** `Additional Problems II/2131_Grid Puzzle II/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Grid puzzle semantics OK, but `k` is read unbounded.


### statement_en.md


# 2131 - Grid Puzzle II

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

There is an $n \times n$ grid whose each square has some number of coins in it.

You know for each row and column how many squares you must choose from that row or column. You get all coins from every square you choose. What is the maximum number of coins you can collect and how could you choose the squares so that the given conditions are satisfied?

# Input

The first input line has an integer $n$: the size of the grid. The rows and columns are numbered $1,2,\dots,n$.

The next line has $n$ integers $a\_1,a\_2,\ldots,a\_n$: You must choose exactly $a\_i$ squares from the $i$th row.

The next line has $n$ integers $b\_1,b\_2,\ldots,b\_n$: You must choose exactly $b\_j$ squares from the $j$th column.

Finally, there are $n$ lines describing the grid. You can assume that the sums of $a\_1,a\_2,\ldots,a\_n$ and $b\_1,b\_2,\ldots,b\_n$ are equal.

# Output

First print an integer $k$: the maximum number of coins you can collect. After this print $n$ lines describing which squares you choose (`X` means that you choose a square, `.` means that you don't choose it).

If it is not possible to satisfy the conditions print only $-1$.

# Constraints

* $1 \le n \le 50$
* $0 \le a\_i \le n$
* $0 \le b\_j \le n$
* $0 \le c\_{ij} \le 1000$

# Example

Input:

```cpp
5
0 1 3 2 0
1 2 2 0 1
2 5 1 5 1
0 2 5 1 2
3 8 9 3 5
1 4 3 7 3
0 3 6 2 8
```

Output:

```cpp
32
.....
..X..
.XX.X
XX...
.....
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> a(n), b(n);
    vector<vector<int>> coins(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        a[i] = inf.readInt();
    for (int i = 0; i < n; i++)
        b[i] = inf.readInt();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            coins[i][j] = inf.readInt();

    int k_ans = ans.readInt();
    int k = ouf.readInt();

    if (k == -1) {
        if (k_ans != -1)
            quitf(_wa, "Output is -1 but a valid selection exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correctly reported impossible");
    }

    if (k_ans == -1)
        quitf(_wa, "Expected -1 (impossible), but contestant claimed %d coins", k);

    if (k != k_ans)
        quitf(_wa, "Claimed %d coins but optimal is %d", k, k_ans);

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        grid[i] = ouf.readToken();
        if ((int)grid[i].size() != n)
            quitf(_wa, "Row %d has length %d, expected %d", i + 1, (int)grid[i].size(), n);
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        int rowCnt = 0;
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != 'X' && grid[i][j] != '.')
                quitf(_wa, "Invalid character '%c' at (%d,%d)", grid[i][j], i + 1, j + 1);
            if (grid[i][j] == 'X') {
                rowCnt++;
                total += coins[i][j];
            }
        }
        if (rowCnt != a[i])
            quitf(_wa, "Row %d has %d selected squares, expected %d", i + 1, rowCnt, a[i]);
    }

    for (int j = 0; j < n; j++) {
        int colCnt = 0;
        for (int i = 0; i < n; i++)
            if (grid[i][j] == 'X')
                colCnt++;
        if (colCnt != b[j])
            quitf(_wa, "Column %d has %d selected squares, expected %d", j + 1, colCnt, b[j]);
    }

    if (total != k)
        quitf(_wa, "Claimed maximum %d but selected squares sum to %lld", k, total);

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal selection with %d coins", k);
}

```


---

## 2165 — Tower of Hanoi

- **Severity:** `RISK`

- **Folder:** `Introductory Problems/2165_Tower of Hanoi/`

- **Output file:** `Introductory Problems/2165_Tower of Hanoi/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Hanoi simulation OK, but `k`, `a`, `b` are read unbounded.


### statement_en.md


# 2165 - Tower of Hanoi

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

The Tower of Hanoi game consists of three stacks (left, middle and right) and $n$ round disks of different sizes. Initially, the left stack has all the disks, in increasing order of size from top to bottom.

The goal is to move all the disks to the right stack using the middle stack. On each move you can move the uppermost disk from a stack to another stack. In addition, it is not allowed to place a larger disk on a smaller disk.

Your task is to find a solution that minimizes the number of moves.

# Input

The only input line has an integer $n$: the number of disks.

# Output

First print an integer $k$: the minimum number of moves.

After this, print $k$ lines that describe the moves. Each line has two integers $a$ and $b$: you move a disk from stack $a$ to stack $b$.

# Constraints

* $1 \le n \le 16$

# Example

Input:

```cpp
2
```

Output:

```cpp
3
1 2
1 3
2 3
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int optimal = ans.readInt();

    int k = ouf.readInt();
    if (k != optimal)
        quitf(_wa, "Minimum number of moves is %d, got %d", optimal, k);

    vector<vector<int>> pegs(4);
    for (int d = n; d >= 1; d--)
        pegs[1].push_back(d);

    for (int i = 0; i < k; i++) {
        int a = ouf.readInt();
        int b = ouf.readInt();
        if (a < 1 || a > 3 || b < 1 || b > 3)
            quitf(_wa, "Stack numbers must be between 1 and 3");
        if (a == b)
            quitf(_wa, "Move %d: source and destination are the same", i + 1);
        if (pegs[a].empty())
            quitf(_wa, "Move %d: stack %d is empty", i + 1, a);

        int disk = pegs[a].back();
        if (!pegs[b].empty() && pegs[b].back() < disk)
            quitf(_wa, "Move %d: cannot place disk %d on a smaller disk",
                  i + 1, disk);

        pegs[a].pop_back();
        pegs[b].push_back(disk);
    }

    if ((int)pegs[3].size() != n)
        quitf(_wa, "All disks must end on stack 3");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal Tower of Hanoi solution");
}

```


# Batch 9

**Problem IDs:** 2214, 3294, 3308, 3399, 3403

Xử lý toàn bộ batch này; trả về đủ các khối `===CHECKER:ID===` … `===END===` cho mỗi ID.


---

## 2214 — Inverse Inversions

- **Severity:** `RISK`

- **Folder:** `Construction Problems/2214_Inverse Inversions/`

- **Output file:** `Construction Problems/2214_Inverse Inversions/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Inversion construction semantics OK, but output values are read unbounded.


### statement_en.md


# 2214 - Inverse Inversions

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Your task is to create a permutation of numbers $1,2,\dots,n$ that has exactly $k$ inversions.

An inversion is a pair $(a,b)$ where $a<b$ and $p\_a>p\_b$ where $p\_i$ denotes the number at position $i$ in the permutation.

# Input

The only input line has two integers $n$ and $k$.

# Output

Print a line that contains the permutation. You can print any valid solution.

# Constraints

* $1 \le n \le 10^6$
* $0 \le k \le \frac{n(n-1)}{2}$

# Example

Input:

```cpp
5 4
```

Output:

```cpp
1 5 2 4 3
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
using namespace std;
using ll = long long;

static ll count_inversions(const vector<int>& p) {
    int n = (int)p.size();
    vector<int> bit(n + 1, 0);
    auto add = [&](int i) {
        for (; i <= n; i += i & -i)
            bit[i]++;
    };
    auto sum = [&](int i) {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    };

    ll inv = 0;
    for (int x : p) {
        inv += sum(n) - sum(x);
        add(x);
    }
    return inv;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    ll k = inf.readLong();
    vector<int> p(n);
    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; i++) {
        p[i] = ouf.readInt();
        if (p[i] < 1 || p[i] > n)
            quitf(_wa, "Value %d out of range [1,%d]", p[i], n);
        if (seen[p[i]])
            quitf(_wa, "Value %d appears more than once", p[i]);
        seen[p[i]] = true;
    }
    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");

    ll inv = count_inversions(p);
    if (inv != k)
        quitf(_wa, "Permutation has %lld inversions, expected %lld", inv, k);

    quitf(_ok, "Valid permutation with %lld inversions", k);
}

```


---

## 3294 — Subarray Sum Constraints

- **Severity:** `RISK`

- **Folder:** `Additional Problems I/3294_Subarray Sum Constraints/`

- **Output file:** `Additional Problems I/3294_Subarray Sum Constraints/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Semantics OK, but output longs are read unbounded.


### statement_en.md


# 3294 - Subarray Sum Constraints

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Your task is to construct an array $x\_1,x\_2,\dots,x\_n$ consisting of $n$ integers.

The array must satisfy $m$ constraints of the form $(l,r,s)$: the sum $x\_l + x\_{l+1} + \dots + x\_r$ must equal $s$.

# Input

The first line has two integers $n$ and $m$: the length of the array and the number of constraints.

The next $m$ lines each have three integers $l$, $r$ and $s$: the description of the constraints.

# Output

If a solution exists, print `YES` on the first line.

On the second line, print $n$ integers $x\_1, x\_2,\dots, x\_n$: the contents of the array. All elements of the array must satisfy $-10^{15} \le x\_i \le 10^{15}$ and the array must satisfy all given constraints. You can print any valid solution.

If no solution exists, just print `NO`.

# Constraints

* $1 \le n \le 5000$
* $0 \le m \le 2 \cdot 10^5$
* $1 \le l \le r \le n$
* $-10^9 \le s \le 10^9$

# Example

Input:

```cpp
5 3
1 3 3
3 5 3
4 4 -1
```

Output:

```cpp
YES
0 2 1 -1 3
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
#include <string>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();

    vector<int> L(m), R(m);
    vector<ll> S(m);
    for (int i = 0; i < m; i++) {
        L[i] = inf.readInt();
        R[i] = inf.readInt();
        S[i] = inf.readLong();
    }

    string ans_token = ans.readToken();
    bool ans_yes = (ans_token == "YES");

    string out_token = ouf.readToken();
    if (out_token == "NO") {
        if (ans_yes)
            quitf(_wa, "Output is NO but a solution exists");
        if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
        quitf(_ok, "Correctly reported no solution");
    }

    if (out_token != "YES")
        quitf(_wa, "Expected YES or NO, got '%s'", out_token.c_str());
    if (!ans_yes)
        quitf(_wa, "No solution exists but output is YES");

    vector<ll> x(n + 1);
    for (int i = 1; i <= n; i++) {
        x[i] = ouf.readLong();
        if (x[i] < -1000000000000000LL || x[i] > 1000000000000000LL)
            quitf(_wa, "x[%d] = %lld out of bounds [-10^15, 10^15]", i, x[i]);
    }

    vector<ll> pref(n + 1, 0);
    for (int i = 1; i <= n; i++)
        pref[i] = pref[i - 1] + x[i];

    for (int i = 0; i < m; i++) {
        ll sum = pref[R[i]] - pref[L[i] - 1];
        if (sum != S[i])
            quitf(_wa, "Constraint %d: sum[%d..%d] = %lld, expected %lld",
                  i + 1, L[i], R[i], sum, S[i]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid solution");
}

```


---

## 3308 — Graph Coloring

- **Severity:** `RISK`

- **Folder:** `Advanced Graph Problems/3308_Graph Coloring/`

- **Output file:** `Advanced Graph Problems/3308_Graph Coloring/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Graph coloring semantics OK, but `k` and colors are read unbounded.


### statement_en.md


# 3308 - Graph Coloring

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given a simple graph with $n$ nodes and $m$ edges. Your task is to use the minimum possible number of colors to color each node such that no edge connects two nodes of the same color.

# Input

The first line has two integers $n$ and $m$: the number of nodes and edges. The nodes are numbered $1, 2,\dots, n$.

Then there are $m$ lines describing the edges. Each line has two integers $a$ and $b$: there is an edge connecting nodes $a$ and $b$.

# Output

First, print an integer $k$: the minimum number of colors.

After this, print $n$ integers $c\_1, c\_2,\dots, c\_n$: the colors of the nodes. The colors should satisfy $1 \le c\_i \le k$.

You may print any valid solution.

# Constraints

* $1 \le n \le 16$
* $0 \le m \le \frac{n(n-1)}{2}$

# Example

Input:

```cpp
4 4
1 2
2 3
3 4
4 1
```

Output:

```cpp
2
1 2 1 2
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        adj[a][b] = adj[b][a] = true;
    }

    int k_ans = ans.readInt();
    int k = ouf.readInt();
    if (k != k_ans)
        quitf(_wa, "Claimed %d colors but optimal is %d", k, k_ans);
    if (k < 1 || k > n)
        quitf(_wa, "Number of colors %d out of range [1,%d]", k, n);

    vector<int> col(n + 1);
    for (int i = 1; i <= n; i++) {
        col[i] = ouf.readInt();
        if (col[i] < 1 || col[i] > k)
            quitf(_wa, "Node %d has color %d (must be 1..%d)", i, col[i], k);
    }

    for (int i = 1; i <= n; i++)
        ans.readInt();

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (adj[i][j] && col[i] == col[j])
                quitf(_wa, "Edge %d-%d connects nodes of same color %d", i, j, col[i]);
        }
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid optimal coloring with %d colors", k);
}

```


---

## 3399 — Raab Game I

- **Severity:** `RISK`

- **Folder:** `Introductory Problems/3399_Raab Game I/`

- **Output file:** `Introductory Problems/3399_Raab Game I/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Raab game semantics OK, but both output permutations use bare reads.


### statement_en.md


# 3399 - Raab Game I

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Consider a two player game where each player has $n$ cards numbered $1,2,\dots,n$. On each turn both players place one of their cards on the table. The player who placed the higher card gets one point. If the cards are equal, neither player gets a point. The game continues until all cards have been played.

You are given the number of cards $n$ and the players' scores at the end of the game, $a$ and $b$. Your task is to give an example of how the game could have played out.

# Input

The first line contains one integer $t$: the number of tests.

Then there are $t$ lines, each with three integers $n$, $a$ and $b$.

# Output

For each test case print `YES` if there is a game with the given outcome and `NO` otherwise.

If the answer is `YES`, print an example of one possible game. Print two lines representing the order in which the players place their cards. You can give any valid example.

# Constraints

* $1 \le t \le 1000$
* $1 \le n \le 100$
* $0 \le a,b \le n$

# Example

Input:

```cpp
5
4 1 2
2 0 1
3 0 0
2 1 1
4 4 1
```

Output:

```cpp
YES
1 4 3 2
2 1 3 4
NO
YES
1 2 3
1 2 3
YES
1 2
2 1
NO
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
using namespace std;

static void consume_game(int n, InStream& stream) {
    for (int i = 0; i < n; i++)
        stream.readInt();
    for (int i = 0; i < n; i++)
        stream.readInt();
}

static void validate_game(int n, int a, int b) {
    vector<int> p1(n), p2(n);
    for (int i = 0; i < n; i++)
        p1[i] = ouf.readInt();
    for (int i = 0; i < n; i++)
        p2[i] = ouf.readInt();

    vector<bool> seen1(n + 1, false), seen2(n + 1, false);
    for (int i = 0; i < n; i++) {
        if (p1[i] < 1 || p1[i] > n)
            quitf(_wa, "P1[%d]=%d out of range [1,%d]", i + 1, p1[i], n);
        if (seen1[p1[i]])
            quitf(_wa, "P1 duplicate value %d", p1[i]);
        seen1[p1[i]] = true;

        if (p2[i] < 1 || p2[i] > n)
            quitf(_wa, "P2[%d]=%d out of range [1,%d]", i + 1, p2[i], n);
        if (seen2[p2[i]])
            quitf(_wa, "P2 duplicate value %d", p2[i]);
        seen2[p2[i]] = true;
    }

    int s1 = 0, s2 = 0;
    for (int i = 0; i < n; i++) {
        if (p1[i] > p2[i])
            s1++;
        else if (p1[i] < p2[i])
            s2++;
    }

    if (s1 != a || s2 != b)
        quitf(_wa, "Expected scores (%d,%d) but got (%d,%d)", a, b, s1, s2);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int tc = 0; tc < t; tc++) {
        int n = inf.readInt();
        int a = inf.readInt();
        int b = inf.readInt();
        string ans_flag = ans.readToken();
        string ouf_flag = ouf.readToken();

        if (ans_flag == "NO") {
            if (ouf_flag != "NO")
                quitf(_wa, "Test %d: no valid game exists but contestant printed '%s'", tc + 1, ouf_flag.c_str());
            continue;
        }

        if (ans_flag != "YES")
            quitf(_fail, "Test %d: judge answer malformed, expected YES or NO", tc + 1);

        if (ouf_flag == "NO")
            quitf(_wa, "Test %d: a valid game exists but contestant printed NO", tc + 1);
        if (ouf_flag != "YES")
            quitf(_wa, "Test %d: expected YES or NO, got '%s'", tc + 1, ouf_flag.c_str());

        consume_game(n, ans);
        validate_game(n, a, b);
    }

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid for %d test cases", t);
}

```


---

## 3403 — Longest Common Subsequence

- **Severity:** `RISK`

- **Folder:** `Dynamic Programming/3403_Longest Common Subsequence/`

- **Output file:** `Dynamic Programming/3403_Longest Common Subsequence/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** LCS invariant OK, but output coordinates/length are read unbounded.


### statement_en.md


# 3403 - Longest Common Subsequence

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given two arrays of integers, find their longest common subsequence.

A subsequence is a sequence of array elements from left to right that can contain gaps. A common subsequence is a subsequence that appears in both arrays.

# Input

The first line has two integers $n$ and $m$: the sizes of the arrays.

The second line has $n$ integers $a\_1,a\_2,\dots,a\_n$: the contents of the first array.

The third line has $m$ integers $b\_1,b\_2,\dots,b\_m$: the contents of the second array.

# Output

First print the length of the longest common subsequence.

After that, print an example of such a sequence. If there are several solutions, you can print any of them.

# Constraints

* $1 \le n,m \le 1000$
* $1 \le a\_i, b\_i \le 10^9$

# Example

Input:

```cpp
8 6
3 1 3 2 7 4 8 2
6 5 1 2 3 4
```

Output:

```cpp
3
1 2 4
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
using namespace std;

bool is_subseq(const vector<int>& arr, const vector<int>& sub) {
    int j = 0;
    for (int i = 0; i < (int)arr.size() && j < (int)sub.size(); i++) {
        if (arr[i] == sub[j]) j++;
    }
    return j == (int)sub.size();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) a[i] = inf.readInt();
    for (int i = 0; i < m; i++) b[i] = inf.readInt();

    int optimal = ans.readInt();
    int k = ouf.readInt();

    if (k != optimal)
        quitf(_wa, "Longest common subsequence has length %d, got %d", optimal, k);

    vector<int> sub(k);
    for (int i = 0; i < k; i++)
        sub[i] = ouf.readInt();

    if (!is_subseq(a, sub))
        quitf(_wa, "Output is not a subsequence of the first array");

    if (!is_subseq(b, sub))
        quitf(_wa, "Output is not a subsequence of the second array");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid longest common subsequence of length %d", k);
}

```


# Batch 10

**Problem IDs:** 3404, 3422, 3423, 3424

Xử lý toàn bộ batch này; trả về đủ các khối `===CHECKER:ID===` … `===END===` cho mỗi ID.


---

## 3404 — Permutation Subsequence

- **Severity:** `RISK`

- **Folder:** `Additional Problems I/3404_Permutation Subsequence/`

- **Output file:** `Additional Problems I/3404_Permutation Subsequence/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Subsequence semantics OK, but output values are read unbounded.


### statement_en.md


# 3404 - Permutation Subsequence

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given two arrays which are permutations, find their longest common subsequence.

A subsequence is a sequence of array elements from left to right that can contain gaps. A common subsequence is a subsequence that appears in both arrays.

# Input

The first line has two integers $n$ and $m$: the sizes of the arrays.

The second line has $n$ integers $a\_1,a\_2,\dots,a\_n$: the contents of the first array.

The third line has $m$ integers $b\_1,b\_2,\dots,b\_m$: the contents of the second array.

# Output

First print the length of the longest common subsequence.

After that, an example of such a sequence. If there are several solutions, you can print any of them.

# Constraints

* $1 \le n,m \le 2 \cdot 10^5$
* $1 \le a\_i \le n$
* $1 \le b\_i \le m$

# Example

Input:

```cpp
8 6
3 1 2 8 5 7 6 4
6 5 1 2 3 4
```

Output:

```cpp
3
1 2 4
```


### checker.cpp (hiện tại)


```cpp

#include "testlib.h"
#include <vector>
using namespace std;

bool is_subseq(const vector<int>& arr, const vector<int>& sub) {
    int j = 0;
    for (int i = 0; i < (int)arr.size() && j < (int)sub.size(); i++) {
        if (arr[i] == sub[j]) j++;
    }
    return j == (int)sub.size();
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) a[i] = inf.readInt();
    for (int i = 0; i < m; i++) b[i] = inf.readInt();

    int optimal = ans.readInt();
    int k = ouf.readInt();

    if (k != optimal)
        quitf(_wa, "Longest common subsequence has length %d, got %d", optimal, k);

    vector<int> sub(k);
    for (int i = 0; i < k; i++)
        sub[i] = ouf.readInt();

    if (!is_subseq(a, sub))
        quitf(_wa, "Output is not a subsequence of the first array");

    if (!is_subseq(b, sub))
        quitf(_wa, "Output is not a subsequence of the second array");

    if (!ouf.seekEof())
        quitf(_wa, "Extra information in the output file");
    quitf(_ok, "Valid longest common subsequence of length %d", k);
}

```


---

## 3422 — Third Permutation

- **Severity:** `RISK`

- **Folder:** `Construction Problems/3422_Third Permutation/`

- **Output file:** `Construction Problems/3422_Third Permutation/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Semantics OK, but possible case plus contestant `IMPOSSIBLE` becomes PE instead of WA.


### statement_en.md


# 3422 - Third Permutation

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

You are given two permutations $a$ and $b$ such that $a\_i \neq b\_i$ in every position. Create a third permutation $c$ such that $a\_i \neq c\_i$ and $b\_i \neq c\_i$ in every position.

# Input

The first line has an integer $n$: the permutation size.

The second line has $n$ integers $a\_1,a\_2,\dots,a\_n$.

The third line has $n$ integers $b\_1,b\_2,\dots,b\_n$.

# Output

Print $n$ integers $c\_1,c\_2,\dots,c\_n$. You can print any valid solution. If there are no solutions, print `IMPOSSIBLE`.

# Constraints

* $2 \le n \le 10^5$

# Example

Input:

```cpp
5
1 3 2 5 4
4 1 3 2 5
```

Output:

```cpp
3 2 5 4 1
```


### checker.cpp (hiện tại)


```cpp

/*
 * Problem:      3422 Third Permutation
 * Input read:   n; permutations a[1..n], b[1..n]
 * Validity:     IMPOSSIBLE iff no permutation c exists; else c is a permutation of
 *               1..n with c_i != a_i and c_i != b_i for all i
 * Optimality:   any valid permutation (no scalar from ans)
 * Complexity:   O(n)
 */
#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        a[i] = inf.readInt();
    for (int i = 0; i < n; i++)
        b[i] = inf.readInt();

    string ansFirst = ans.readToken();
    if (ansFirst == "IMPOSSIBLE") {
        string tok = ouf.readToken();
        if (tok != "IMPOSSIBLE")
            quitf(_wa, "Jury answer is IMPOSSIBLE but contestant printed \"%s\"",
                  compress(tok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    vector<int> c(n);
    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; i++) {
        c[i] = ouf.readInt(1, n, format("c[%d]", i + 1).c_str());
        if (seen[c[i]])
            quitf(_wa, "Value %d appears more than once", c[i]);
        seen[c[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        if (c[i] == a[i])
            quitf(_wa, "Position %d: c=%d equals a=%d", i + 1, c[i], a[i]);
        if (c[i] == b[i])
            quitf(_wa, "Position %d: c=%d equals b=%d", i + 1, c[i], b[i]);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid third permutation");
}

```


---

## 3423 — Permutation Prime Sums

- **Severity:** `RISK`

- **Folder:** `Construction Problems/3423_Permutation Prime Sums/`

- **Output file:** `Construction Problems/3423_Permutation Prime Sums/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Semantics OK, same sentinel/verdict risk; primality loop is not ideal but constraints are small.


### statement_en.md


# 3423 - Permutation Prime Sums

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Given $n$, create two permutations $a$ and $b$ of size $n$ such that $a\_i+b\_i$ is prime for $i=1,2,\dots,n$.

# Input

The only line has an integer $n$.

# Output

Print two permutations. You can print any valid solution. If there are no solutions, print `IMPOSSIBLE`.

# Constraints

* $1 \le n \le 10^5$

# Example

Input:

```cpp
5
```

Output:

```cpp
2 1 3 5 4
5 1 4 2 3
```

*Explanation*: The sums are $2+5=7$, $1+1=2$, $3+4=7$, $5+2=7$ and $4+3=7$ which all are primes.


### checker.cpp (hiện tại)


```cpp

/*
 * Problem:      3423 Permutation Prime Sums
 * Input read:   n
 * Validity:     IMPOSSIBLE iff no pair exists; else two permutations of 1..n with
 *               a_i + b_i prime for every position i
 * Optimality:   any valid pair (no scalar from ans)
 * Complexity:   O(n sqrt n)
 */
#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

static bool is_prime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    string ansFirst = ans.readToken();
    if (ansFirst == "IMPOSSIBLE") {
        string tok = ouf.readToken();
        if (tok != "IMPOSSIBLE")
            quitf(_wa, "Jury answer is IMPOSSIBLE but contestant printed \"%s\"",
                  compress(tok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    vector<int> a(n), b(n);
    vector<bool> seen_a(n + 1, false), seen_b(n + 1, false);

    for (int i = 0; i < n; i++) {
        a[i] = ouf.readInt(1, n, format("a[%d]", i + 1).c_str());
        if (seen_a[a[i]])
            quitf(_wa, "Value %d appears more than once in first permutation", a[i]);
        seen_a[a[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        b[i] = ouf.readInt(1, n, format("b[%d]", i + 1).c_str());
        if (seen_b[b[i]])
            quitf(_wa, "Value %d appears more than once in second permutation", b[i]);
        seen_b[b[i]] = true;
    }

    for (int i = 0; i < n; i++) {
        int sum = a[i] + b[i];
        if (!is_prime(sum))
            quitf(_wa, "a[%d]+b[%d] = %d+%d = %d is not prime",
                  i + 1, i + 1, a[i], b[i], sum);
    }

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid prime-sum permutations");
}

```


---

## 3424 — Distinct Sums Grid

- **Severity:** `RISK`

- **Folder:** `Construction Problems/3424_Distinct Sums Grid/`

- **Output file:** `Construction Problems/3424_Distinct Sums Grid/checker.cpp`


**Yêu cầu:** Sinh checker mới với testlib.h theo `CHECKER_STRATEGY_V2.md` và mẫu `checker_skeleton.cpp`. Giữ đúng semantics hiện tại nhưng sửa hardening theo v2.

**Rủi ro audit (RISK):** Semantics OK, same sentinel/verdict risk.


### statement_en.md


# 3424 - Distinct Sums Grid

* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

Create an $n \times n$ grid that fulfills the following requirements:

1. Each integer $1 \dots n$ appears $n$ times in the grid.
2. If we create a set that consists of all sums in rows and columns, there are $2n$ distinct values.

# Input

The only line has an integer $n$.

# Output

Print a grid that fulfills the requirements. You can print any valid solution. If there are no solutions, print `IMPOSSIBLE`.

# Constraints

* $1 \le n \le 1000$

# Example

Input:

```cpp
5
```

Output:

```cpp
2 3 1 1 1 
1 5 5 3 3 
2 3 5 2 4 
5 4 5 4 1 
2 3 4 4 2
```

*Explanation*: Each integer $1 \dots 5$ appears $5$ times, and the sums in rows and columns are $\{8,11,12,14,15,16,17,18,19,20\}$.


### checker.cpp (hiện tại)


```cpp

/*
 * Problem:      3424 Distinct Sums Grid
 * Input read:   n
 * Validity:     IMPOSSIBLE iff no grid exists; else n x n grid with each value
 *               1..n appearing exactly n times and exactly 2n distinct row+column
 *               sums
 * Optimality:   any valid grid (no scalar from ans)
 * Complexity:   O(n^2)
 */
#include "testlib.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    string ansFirst = ans.readToken();
    if (ansFirst == "IMPOSSIBLE") {
        string tok = ouf.readToken();
        if (tok != "IMPOSSIBLE")
            quitf(_wa, "Jury answer is IMPOSSIBLE but contestant printed \"%s\"",
                  compress(tok).c_str());
        if (!ouf.seekEof())
            quitf(_wa, "extra information in the output file");
        quitf(_ok, "correctly reported IMPOSSIBLE");
    }

    vector<vector<int>> grid(n, vector<int>(n));
    vector<int> freq(n + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = ouf.readInt(1, n, format("grid[%d][%d]", i + 1, j + 1).c_str());
            freq[grid[i][j]]++;
        }
    }

    for (int v = 1; v <= n; v++) {
        if (freq[v] != n)
            quitf(_wa, "Value %d appears %d times, must appear exactly %d times", v, freq[v], n);
    }

    set<int> sums;
    for (int i = 0; i < n; i++) {
        int row_sum = 0;
        for (int j = 0; j < n; j++)
            row_sum += grid[i][j];
        sums.insert(row_sum);
    }
    for (int j = 0; j < n; j++) {
        int col_sum = 0;
        for (int i = 0; i < n; i++)
            col_sum += grid[i][j];
        sums.insert(col_sum);
    }

    if ((int)sums.size() != 2 * n)
        quitf(_wa, "Got %d distinct row+column sums, expected %d", (int)sums.size(), 2 * n);

    if (!ouf.seekEof())
        quitf(_wa, "extra information in the output file");
    quitf(_ok, "valid grid with %d distinct sums", (int)sums.size());
}

```

