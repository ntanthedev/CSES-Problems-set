# Checker audit 2026-07-03

Scope: all non-interactive non-standard checkers in `CHECKER_MANIFEST.json`.
Interactive problems are excluded. `solution.cpp` was not treated as ground truth.

Inventory:

- 71 manifest entries are generated `bridged`/`testlib` checkers.
- 70 generated `checker.cpp` files exist; `1680_Longest Flight Route` is missing.
- 4 manifest entries use shared unordered generic checkers: `1134`, `2076`, `2077`, `2195`.
- 5 manifest entries use built-in float checkers: `1725`, `1726`, `1727`, `1728`, `3361`.

Machine checks:

- `validate_checker_v2.py --all .` could not run on native Windows because it imports POSIX-only `resource`.
- WSL is installed as a binary but has no distro, so the POSIX validator could not be run there either.
- `g++ -O2 -std=c++17 -I .` compilation succeeded for all 70 existing generated `checker.cpp` files plus the 3 shared generic checker files.

Legend:

- `BUG`: do not trust/upload as-is.
- `RISK`: semantic check appears mostly right, but violates v2 hardening/performance/verdict rules or has a defensible edge-case risk.
- `OK`: no issue found in this audit.

## Must Fix First

| ID | Problem | Finding |
|---:|---|---|
| 1680 | Longest Flight Route | Manifest marks it as generated `bridged`, but `Graph Algorithms/1680_Longest Flight Route/checker.cpp` is missing. |
| 3361 | Two Array Average | Manifest uses `floats`, but the statement outputs two prefix sizes, not a floating number. Needs a custom checker that validates the chosen prefixes' average within `1e-6` of optimum. |
| 1134 | Prüfer Code | Manifest points to `checker_unordered_pairs_symmetric.cpp`, which expects a leading `k`; statement prints exactly `n-1` edge lines with no `k`. |
| 1070 | Permutations | Uses `atoi` on contestant token; malformed tokens like `4abc` can be accepted as `4`. |
| 1111 | Longest Palindrome | Uses `s.find(out)` at `n <= 1e6`; this is the v2 forbidden O(nm) substring pattern. |
| 1193 | Labyrinth | Reads grid with `inf.readLine()` after `readInt`, causing line drift; also has unbounded output reads. |
| 1640 | Sum of Two Values | Uses `stoi` on contestant token and `ouf.readEoln()`, so it can crash or reject valid whitespace. |
| 1669 | Round Trip | Accepts `k = 3`, so `u v u` is accepted on any valid road, but statement requires going through two or more other cities. |
| 1711 | Distinct Routes | Reads path length before bounding and allocates `vector<int> path(len)`, so hostile output can crash/MLE. |
| 2075 | Reversal Sorting | Simulates each reversal with `std::reverse`; with `n, k = 2e5`, valid or hostile outputs can make the checker O(n^2). |
| 2106 | Repeating Substring | Uses `ouf.readLine()` and repeated `string::find`, causing whitespace fragility and O(nm) risk. |
| 2130 | Distinct Routes II | Reads `route_len` before bounding and allocates `vector<int> route(route_len)`, so hostile output can crash/MLE. |
| 2414 | List of Sums | Does not enforce output values are positive/in `[1, k]`; negative reconstructions can be accepted if pair sums match. |
| 2423 | Filling Trominos | `is_tromino` accepts three collinear cells; statement requires L-trominoes. |
| 3225 | Inverse Suffix Array | Uses one-mod rolling hash for suffix comparison; not deterministic, collision can accept/reject incorrectly. |
| 3355 | Sum of Four Squares | Reads unbounded longs and squares them in `long long`; overflow/UB can lead to wrong verdicts. |

## Generated Checker Status

| Status | IDs |
|---|---|
| BUG | `1070 1111 1193 1640 1669 1680 1711 2075 2106 2130 2414 2423 3225 3355` |
| RISK | `1092 1164 1197 1666 1667 1668 1678 1679 1682 1683 1685 1689 1695 1696 1698 1704 1709 1756 2079 2129 2131 2165 2214 3294 3308 3399 3403 3404 3422 3423 3424` |
| OK | `1087 1194 1641 1642 1684 1691 1692 1693 1697 1752 1755 2177 2179 2205 2215 2402 2418 2427 2430 2432 3154 3159 3213 3311 3312 3358` |

## RISK Details

| ID | Issue |
|---:|---|
| 1092 | Semantics OK, but many bare `ouf.readInt()` calls and `std::set` up to `n = 1e6`. |
| 1164 | Semantics OK, but uses `ouf.readEoln()` and can reject harmless whitespace. |
| 1197 | Negative-cycle check likely OK for normal CSES data, but permits non-simple closed walks and chooses minimum parallel-edge weight by vertex pair. |
| 1666 | Semantics OK, but contestant numbers are read unbounded. |
| 1667 | Possible case where contestant prints `IMPOSSIBLE` becomes PE via integer read instead of clear WA. |
| 1668 | Same sentinel/verdict risk as `1667`. |
| 1678 | Lower bound should defensively be `k >= 3`; valid input excludes self-loops, so this is not a confirmed semantic false-AC. Also has possible `IMPOSSIBLE` -> PE branch. |
| 1679 | Same sentinel/verdict risk as `1667`. |
| 1682 | Counterexample vertices are read unbounded. |
| 1683 | Contestant component labels are read unbounded; DFS recursion on `n = 1e5` risks stack overflow. |
| 1685 | Semantics OK, but SCC DFS recursion on `n = 1e5` and unbounded output reads. |
| 1689 | Board values are read with bare `ouf.readInt()` before range checks. |
| 1695 | Cut size/endpoints are read unbounded. |
| 1696 | Matching size/endpoints are read unbounded. |
| 1698 | `k`, round sizes, and swaps are read unbounded; hostile `cnt` can drive huge loops. |
| 1704 | Semantics OK, but Tarjan recursion on `n = 1e5` and unbounded output reads. |
| 1709 | Move count/type/index are read unbounded. |
| 1756 | Edge endpoints are read unbounded. |
| 2079 | Centroid invariant OK, but output node is unbounded and recursive DFS may overflow stack at `n = 2e5`. |
| 2129 | Assignment semantics OK, but cost/employee/task are read unbounded. |
| 2131 | Grid puzzle semantics OK, but `k` is read unbounded. |
| 2165 | Hanoi simulation OK, but `k`, `a`, `b` are read unbounded. |
| 2214 | Inversion construction semantics OK, but output values are read unbounded. |
| 3294 | Semantics OK, but output longs are read unbounded. |
| 3308 | Graph coloring semantics OK, but `k` and colors are read unbounded. |
| 3399 | Raab game semantics OK, but both output permutations use bare reads. |
| 3403 | LCS invariant OK, but output coordinates/length are read unbounded. |
| 3404 | Subsequence semantics OK, but output values are read unbounded. |
| 3422 | Semantics OK, but possible case plus contestant `IMPOSSIBLE` becomes PE instead of WA. |
| 3423 | Semantics OK, same sentinel/verdict risk; primality loop is not ideal but constraints are small. |
| 3424 | Semantics OK, same sentinel/verdict risk. |

## Generic And Float Entries

| ID | Status | Notes |
|---:|---|---|
| 1134 | BUG | Wrong generic checker; needs a version that reads exactly `n-1` unordered undirected edges from `ouf` and `ans`, no leading `k`. |
| 2076 | OK/RISK | Semantics match Necessary Roads, but generic checker allocates vector using contestant `k` up to `2e9`. |
| 2077 | OK/RISK | Semantics match Necessary Cities, but generic checker allocates vector using contestant `k` up to `2e9`. |
| 2195 | OK/RISK | Semantics match Convex Hull point set, but generic checker allocates vector using contestant `k` up to `2e9`. |
| 1725 | OK | Statement asks probability rounded to six decimals; manifest uses `floats` precision 6. |
| 1726 | OK | Statement asks expected value rounded to six decimals; manifest uses `floats` precision 6. |
| 1727 | OK | Statement asks expected value rounded to six decimals; manifest uses `floats` precision 6. |
| 1728 | OK | Statement asks expected value rounded to six decimals; manifest uses `floats` precision 6. |
| 3361 | BUG | Not a float-output problem; see Must Fix First. |

## Recommended Fix Order

1. Generate/write fresh checkers for `1680` and `3361`.
2. Replace `1134` with a no-leading-`k` unordered-edge checker.
3. Regenerate the BUG list from the v2 skeleton, prioritizing true semantic false-AC cases: `2423`, `2414`, `1669`, then crash/TLE hardening bugs.
4. After fixes, run the POSIX validator in Linux/WSL: `python3 validate_checker_v2.py --all . --skip-solution --json audit_v2_after.json`.
5. Then review remaining `RISK` entries by validator output; most are bounded-read/verdict cleanup rather than statement mismatch.
