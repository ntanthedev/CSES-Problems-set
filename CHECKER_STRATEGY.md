# CSES Checker Strategy — Addendum to CSES_UPLOAD_HANDOVER.md

> Companion to `CSES_UPLOAD_HANDOVER.md`. That doc covers statements/test data/
> editorials; this one covers the 86 problems that need a non-standard checker.
> Source of truth for *how the tool applies this* is `upload.py` itself
> (`CHECKER_MODES`, `CHECKER_LABELS`, `load_checker_manifest`, `Uploader.upload_data`).

---

## 1. What this judge actually supports (confirmed, not guessed)

CHT-oj is a fork of VNOJ, which is a fork of DMOJ. I read VNOJ's actual
`judge/models/problem_data.py` (VNOI-Admin/OJ on GitHub — CHT-oj forked from
this codebase) rather than assuming stock DMOJ behavior, because forks *do*
diverge. The real `ProblemData` model defines:

```python
CHECKERS = (
    ('standard', 'Standard'), ('bridged', 'Custom checker'),
    ('floats', 'Floats'), ('floatsabs', 'Floats (absolute)'),
    ('floatsrel', 'Floats (relative)'),
    ('identical', 'Byte identical'), ('linecount', 'Line-by-line'),
)
CUSTOM_CHECKERS = (   # sub-format, only used when checker == 'bridged'
    ('themis', 'Themis checker'), ('testlib', 'Testlib checker'),
    ('cms', 'CMS checker'), ('coci', 'COCI checker'),
    ('peg', 'PEG checker'), ('default', 'DMOJ checker'),
)
GRADERS = (
    ('standard', 'Standard'), ('interactive', 'Interactive'),
    ('signature', 'Function Signature Grading (IOI-style)'),
    ('output_only', 'Output Only'),
)
```

This maps 1:1 onto the "Trình chấm:" dropdown in your screenshot: Mặc định →
`standard`, Trình chấm ngoài → `bridged`, Số thực → `floats`, Số thực (tuyệt
đối) → `floatsabs`, Số thực (tương đối) → `floatsrel`, So sánh byte →
`identical`, Dòng với dòng → `linecount`.

**Important deviation from stock DMOJ:** this fork's `CHECKERS` list has **no
`sorted`/`unordered` option**. Stock DMOJ has a built-in "ignore order" checker;
this fork dropped it. So "any-order" problems get **no free shortcut** — they
need a `bridged`/`testlib` checker too, exactly like "multiple valid answer"
problems. That collapses two of your four buckets into one implementation path.

Confirmed separately (VNOJ's own `/custom_checkers/` help page, and mirrored
verbatim on at least two other VNOJ-derived judges — HNOJ, oj.vnoi.info): the
`bridged` checker supports **testlib.h C++ checkers directly**, with the
documented contract (from `docs.dmoj.ca`):

- invoked as `checker input_file output_file judge_file` (testlib's normal
  `inf`/`ouf`/`ans` triple — a stock testlib checker needs zero adaptation)
- exit `0` = AC, `1` = WA, `2` = PE, `3` = assertion failed (i.e. `ensuref`/
  `quitf(_wa,...)` all work as-is), `7` + `points X` on stderr = partial

I compiled and ran a real testlib checker against this exact contract locally
(g++, `registerTestlibCmd`, `ensuref`, `quitf`) to confirm the exit codes
before writing any of this up — see `validate_checker.py`, §4 below.

The one caveat VNOJ states explicitly: **testlib checkers only work for
non-interactive problems.** Interactive grading is a separate subsystem
(`grader`, not `checker`) — see §6.

---

## 2. Your 86 problems → mechanism

| Bucket | Count | Mechanism | Manual work needed |
|---|---|---|---|
| Floating-point tolerance | 5 | built-in `floats`/`floatsabs`/`floatsrel` | read each statement's stated epsilon by hand (5 problems — just read them, don't guess) |
| "Print any" / multiple valid | 71 | `bridged` + `testlib` checker.cpp, one per problem | generate + **validate** (§4/§5) |
| "Any order" | 4 | `bridged` + `testlib`, but **3 small generic checkers cover all 4** — no per-problem generation needed, see §2b | none — done, see below |
| Interactive | 6 | `grader=interactive` + compiled `custom_grader` — **not wired into `upload.py` yet** | see §6 — recommend doing these 6 by hand through the browser for now |

75 of the 86 problems (multiple-valid + any-order) go through the **same**
`bridged`/`testlib` mechanism, but the 4 "any order" ones don't need a
model-written checker at all — see §2b.

## 2b. "Any order" (4 problems) — resolved, no generation needed

I checked all four problems' actual output specs against the live CSES
problem statements (not guessed) before assuming a single "ignore order"
checker would be safe for all of them — it isn't:

| Problem | CSES id | Output shape | Safe checker |
|---|---|---|---|
| Necessary Cities | 2077 | `k` then `k` **single** city numbers, any order | `checker_unordered_flat.cpp` |
| Necessary Roads | 2076 | `k` then `k` lines, each an **edge** `a b` (`a-b` = `b-a`), lines in any order | `checker_unordered_pairs_symmetric.cpp` |
| Prüfer Code | 1134 | `n-1` lines, each an **edge** `a b`, lines in any order | `checker_unordered_pairs_symmetric.cpp` |
| Convex Hull | 2195 | `k` lines, each a **point** `x y` (NOT symmetric — `x y` ≠ `y x`), lines in any order | `checker_unordered_pairs_atomic.cpp` |

The reason this needed checking rather than assuming: 3 of the 4 print
**pairs** (edges or points), not single numbers. A naive "sort every
whitespace token and compare" checker — which is exactly what DMOJ's built-in
`sorted`/`unordered` checker does, and the thing you originally asked about
reusing — would incorrectly **accept** a submission that has the right numbers
but paired into the wrong (nonexistent) edges/points, because the flattened
token multiset can be identical even when the pairing is wrong. I confirmed
this concretely: for Necessary Roads, `{1,2},{3,4}` and the wrong `{1,4},{3,2}`
flatten to the same 4 tokens but describe different edges.

So instead of one generic checker, there are three tiny ones (~30 lines each,
all in this delivery), differing only in whether they read 1 or 2 numbers per
item and whether a pair gets canonicalised (`min,max`) before comparing:

- `checker_unordered_flat.cpp` — flat set of numbers (Necessary Cities)
- `checker_unordered_pairs_symmetric.cpp` — set of undirected edges (Necessary
  Roads, Prüfer Code)
- `checker_unordered_pairs_atomic.cpp` — set of points, not swappable (Convex
  Hull)

I compiled all three and ran them against synthetic AC/WA cases, specifically
including the "right numbers, wrong pairing" case for the two pair-based ones
(the case a naive flat checker would get wrong) — all three passed:

```
checker_unordered_flat:              reordered -> AC, missing value -> WA, wrong value -> WA
checker_unordered_pairs_symmetric:   reordered+swapped -> AC, right numbers/wrong pairing -> WA, missing edge -> WA
checker_unordered_pairs_atomic:      reordered only -> AC, x/y swapped in one point -> WA
```

**Manifest entries** (drop the matching `.cpp` into each problem's folder,
named `checker.cpp`, or point `checker_file` at the shared filename):

```json
{
  "2077": {"checker": "bridged", "checker_type": "testlib", "checker_file": "checker_unordered_flat.cpp"},
  "2076": {"checker": "bridged", "checker_type": "testlib", "checker_file": "checker_unordered_pairs_symmetric.cpp"},
  "1134": {"checker": "bridged", "checker_type": "testlib", "checker_file": "checker_unordered_pairs_symmetric.cpp"},
  "2195": {"checker": "bridged", "checker_type": "testlib", "checker_file": "checker_unordered_pairs_atomic.cpp"}
}
```

**Directly answering the "can I just take DMOJ's sorted/unordered checker
code" idea:** no, for two independent reasons, and it wouldn't be fully
correct even if it worked:
1. This fork's `ProblemData.checker` field (the actual Django model, not just
   the UI) has no `sorted`/`unordered` choice at all — it isn't hidden, it
   isn't selectable, full stop.
2. DMOJ's real `sorted`/`unordered` implementation is a **Python** script
   using the `check(process_output, judge_output, **kwargs)` API. This fork's
   `custom_checker` upload field is validated to accept only `.cpp`/`.pas`/
   `.java` — a `.py` file would be rejected by the upload form itself.
3. Even ignoring both of those: as shown above, plain "ignore order of all
   tokens" is the wrong check for 3 of these 4 problems anyway, because it
   doesn't understand that adjacent tokens form a pair. That's the actual
   reason a couple of trivial custom checkers, not a repurposed built-in, is
   the right fix here — not a workaround for a platform limitation.

---

## 3. Is DeepSeek V4 Pro good enough to write these in testlib.h?

Short answer: **yes, for the large majority**, with one structural caveat that
applies to *any* model (including Claude), which is why §4/§5 exist.

- testlib.h checkers for "verify a constructive answer against the input's
  constraints" are one of the best-represented patterns in competitive-
  programming code — small, well-documented API (`inf.readInt()`,
  `ouf.readLong()`, `ensuref`, `quitf(_ok/_wa/_pe, ...)`). A current-generation
  coding model handles the *syntax and idiom* reliably.
- The actual risk is never "does it know testlib syntax" — it's **reading
  comprehension of the problem's exact validity condition** (1-indexed vs
  0-indexed, which endpoint is excluded, whether self-loops are allowed,
  whether the answer must be a permutation vs just distinct values, etc). Any
  model can misread this, and it's a *checker* bug, not a *program* bug — so
  it fails silently: the checker still compiles, still runs, and just quietly
  accepts wrong submissions or rejects right ones.
- Critically, this is **verifiable, not just trustable**. You don't need to
  trust the model's reading comprehension — you need to test it against known
  data, which you already have (`solution.cpp` + `N.out`). That's what
  `validate_checker.py` automates (§5).
- One asymmetry worth knowing: LLM-written checkers skew towards being **too
  lenient** rather than too strict, because "accept anything roughly
  shaped-right" is an easier program to write than "accept exactly the valid
  set" — and a too-lenient checker looks *identical* to a correct one until
  someone submits a wrong answer that happens to pass. This is the single
  most important thing to test for, and it's the reason the validation harness
  runs mutation tests, not just a "does it compile and accept the sample" check.

**Practical recommendation:** batch-generate all 71 (the "any order" 4 are already
done with hand-written generic checkers, §2b), but treat "generated" and
"trusted" as different states. Nothing goes into `CHECKER_MANIFEST.json` until
`validate_checker.py` has run clean (or its warnings have been read by a human).

---

## 3b. Two mistakes in the original prompt (fixed)

The first draft of §4 told models to (a) **avoid `ans`** and recompute optimality from
`inf`, and (b) use **`ensuref`**. Both caused serious production bugs:

1. **No `ans` → heavy algorithms in checkers.** Models copied max-flow, MCMF,
   suffix arrays, brute-force coloring, etc. into `checker.cpp`. Example: Grid
   Puzzle II (2131) ballooned to 230+ lines with a full min-cost max-flow solver
   inside the checker, blowing time limits. **Fix:** read optimal scalars
   (`k`, cost, length, `IMPOSSIBLE` flag, …) from `ans`; only run lightweight
   validity simulation on `ouf`.
2. **`ensuref` → exit code 3, not WA.** DMOJ/VNOJ bridged testlib maps exit 3 to
   "assertion failed", not a normal wrong answer — confusing for contestants and
   breaking mutation tests (`ASSERT-FAIL` instead of `WA`). **Fix:** always
   `if (!cond) quitf(_wa, "...");`.

The generic "any order" checkers (`checker_unordered_*.cpp`) already followed the
correct pattern (read `ans`, `quitf(_wa)`). The per-problem batch did not, until
the §4 rewrite.

---

## 4. Checker-generation prompt (mirrors your existing translator-subagent pattern)

Same shape as the translation prompt in `CSES_UPLOAD_HANDOVER.md` §7: fixed
prompt + reference material + a self-check before it's allowed to finish.

```
You are a competitive-programming problem-setter writing a testlib.h checker
for a CSES problem that accepts multiple valid answers.

INPUT PROVIDED:
- statement_en.md (the full problem statement, constraints included)
- solution.cpp (a reference solution — its output is A valid answer, but may
  differ from the N.out file on disk, which is only ONE valid answer)
- testlib.h is available at the standard include path; do not reproduce it

WRITE checker.cpp that:
1. Reads the input via `inf` (matches statement_en.md's input format exactly).
2. Reads the contestant's output via `ouf`.
3. Reads the judge reference via `ans` (N.out on disk). This is ONE valid answer
   and carries the trusted optimal value(s) for the test case.
4. Verifies EVERY constraint the problem statement states against inf+ouf
   (validity): e.g. a path stays on the grid, a permutation uses 1..n exactly,
   row/column counts match. Accept ANY output shape that satisfies these rules,
   not only the shape solution.cpp happens to produce.
5. For optimality (maximum, minimum, shortest length, min cost, etc.): read the
   target scalar(s) from `ans` with ans.readInt()/readLong()/readToken() and
   require ouf to match. NEVER reimplement heavy algorithms in the checker
   (no max-flow, MCMF, suffix arrays, brute-force chromatic number, full 2-SAT
   solvers, etc.) — the judge answer already computed the optimum; your job is
   cheap validity + compare the optimum to ans. Lightweight checks that only
   VERIFY a claimed structure (simulate a path, check topo order, check a
   matching's edges exist) are fine.
6. When several fields are free (which path, which matching pairs, grid layout)
   but a scalar is fixed (k, cost, distance): compare only that scalar to ans;
   do NOT byte-compare ouf to ans.
7. IMPOSSIBLE / NO / -1 outputs: if ouf reports impossible, ans must too (read
   ans first or compare tokens); if ouf gives a solution, ans must not be impossible.
8. Uses ouf.readInt()/readLong()/readToken() for ouf — never raw cin/scanf on ouf.
9. On failure ALWAYS use quitf(_wa, "..."). NEVER use ensuref (it exits with code
   3 = assertion failed, not WA). On success: quitf(_ok, "..."). Use _pe only for
   genuine format errors distinct from validity.
10. Pattern: if (!cond) quitf(_wa, "..."); throughout.
11. After reading all expected output, reject trailing junk with:
    `if (!ouf.seekEof()) quitf(_wa, "Extra information in the output file");`
    Do NOT call bare `ouf.seekEof();` (ignores the result). Do NOT use `ouf.readEof()`
    (testlib's readEof does not skip trailing whitespace before checking EOF).
12. WA messages must match the branch: if judge answer is impossible (-1 / IMPOSSIBLE)
    but contestant printed a solution, say "Expected -1, but contestant claimed …"
    — never "output is -1" (that describes the opposite mistake).
13. Read `inf` with plain `inf.readInt()` / `readLine()` — no hard bounds on inf,
    no `inf.readEoln()` (jury input is trusted; strict EOL checks cause false jury
    errors on CRLF/LF differences).

SELF-CHECK before finishing:
- Does it use ans for every optimum the statement requires?
- Is the checker free of copied solution algorithms?
- Would solution.cpp's fresh output pass (validity + optimal scalars match ans)?
- No ensuref anywhere?

Output ONLY the C++ source, no explanation, no ```cpp wrapper.
```

Feed it `statement_en.md` + `solution.cpp` per problem, same as the existing
translation pipeline. Write the result to `<problem_dir>/checker.cpp`.

---

## 5. Validate before trusting — `validate_checker.py`

```
pip install requests --break-system-packages   # only needed once, for testlib.h fetch
python validate_checker.py path/to/1625_Labyrinth
```

For each of a few sampled test cases it:
1. compiles `checker.cpp` and `solution.cpp`
2. **must pass:** `checker(input, N.out, N.out)` — sanity check on the checker's own logic
3. **must pass:** `checker(input, solution.cpp's fresh output, N.out)` — the
   actual point of a multi-answer checker; this is the check most likely to
   catch an overly-strict LLM-written checker
4. **should fail:** checker against a couple of heuristically corrupted
   outputs (bump a number, drop a line, reverse token order) — catches an
   overly-*lenient* checker. This one is a heuristic (some mutations are
   legitimately still valid for a given problem), so it prints a WARNING
   rather than a hard failure — read those by hand.

Exit code `0` = safe to add to the manifest; `1` = do not, something's broken.
I built and ran this against a real compiled testlib checker (including
deliberately-broken variants — one "accepts everything", one "too strict") to
confirm it actually catches both failure modes before handing it to you.

---

## 6. Interactive problems (6) — open item, not automated yet

The model shows a **separate** field, `grader` (`standard` / `interactive` /
`signature` / `output_only`), plus a dedicated `custom_grader` file upload
restricted to `.cpp`. This is a genuinely different subsystem from `checker` —
it's not "testlib checker but for interactive," it's a different form section
entirely, and VNOJ's own docs explicitly say the testlib-*checker* path does
**not** cover interactive problems.

I did not find setter-facing documentation for the exact `custom_grader`
contract (arguments, protocol) with enough confidence to wire it into
`upload.py` blind — guessing wrong here doesn't fail loudly, it uploads a
broken interactive problem. Two ways forward, your call:

- **Pragmatic:** it's 6 problems. Do them by hand through the browser once —
  select "Interactive" for the grader, upload a compiled interactor — and
  move on. Not everything needs to be automated.
- **If you want it automated too:** run
  `python upload.py --user ntannn --inspect-fields cses_1068` (or any already-
  uploaded problem code) once. It prints every real field name and dropdown
  option for anything matching `check|grad|io_method|custom` on the live
  `test_data` form. Paste that output back and I'll wire up `grader` +
  `custom_grader` the same way `checker`/`checker_type` are wired now.

---

## 7. `CHECKER_MANIFEST.json` — format the tool reads

One file at the repo root (`<root>/CHECKER_MANIFEST.json`, or point
`--checker-manifest` elsewhere). Keyed by CSES id as a string. A problem with
no entry is completely unaffected — still `standard`, exactly like today.

```json
{
  "1618": {"checker": "floats", "checker_args": {"precision": 6}},
  "1093": {"checker": "floatsabs", "checker_args": {"precision": 4}},
  "1625": {"checker": "bridged", "checker_type": "testlib", "checker_file": "checker.cpp"},
  "1071": {"checker": "bridged", "checker_type": "testlib"}
}
```

- `checker_type`/`checker_file` default to `"testlib"` / `"checker.cpp"` when
  omitted, so most entries can just be `{"checker": "bridged"}` once
  `checker.cpp` sits next to `solution.cpp` in the problem's folder.
- `checker_args` is optional JSON, submitted as-is (mainly useful for the
  `floats` family's `precision`/`error_mode`). For `bridged`, you don't need
  to set this yourself — `upload.py` now builds it automatically as
  `{"files": "<checker_file>", "type": "<checker_type>"}` (merging in
  anything you do specify). This was **not** obvious from the form alone:
  picking "Trình chấm ngoài" + a `checker_type` + uploading the file is not
  sufficient by itself. A real test submission (Necessary Cities / `cses_2077`)
  crashed at grading time with `TypeError: check() missing 1 required
  positional argument: 'files'` (`judge/graders/standard.py`) — the
  judge-server's bridged checker reads `files`/`type` from `checker_args`
  itself, not from the uploaded filename or the `checker_type` dropdown. Fixed
  in `upload.py`; if you ever see that exact traceback again on a *different*
  bridged problem, it means its manifest entry's `checker_file` doesn't match
  the file that actually got uploaded — check for a typo.
- The dropdown value for every mode is resolved **from the live page's actual
  label text** at upload time (`resolve_strict()` in `upload.py`), the same
  way `group`/`type` already are — never a hardcoded slug — so this survives
  any relabeling between this fork and upstream VNOJ. If a label can't be
  matched, it raises loudly instead of silently picking the wrong checker.

---

## 8. Suggested end-to-end order

1. **Any order (4):** done — drop the matching file from §2b into each
   problem's folder as `checker.cpp`, add the 4 manifest lines given there.
2. **Floats (5):** read each statement's tolerance by hand, add 5 lines to
   `CHECKER_MANIFEST.json`. No code generation needed.
3. **Multi-valid (71):** generate `checker.cpp` per problem (§4) →
   `validate_checker.py` every one (§5) → only then add its manifest entry.
4. **Test one of each kind for real** before the batch, per your existing
   handover workflow: `--only <id> --overwrite --debug`, then open it in the
   browser and confirm the "Trình chấm:" dropdown actually shows what you
   expect, submit `solution.cpp` → must be AC, submit a wrong program → must
   be WA/PE. Necessary Cities (2077) is a good first test — smallest of the
   four "any order" problems and needs no LLM generation to try today.
5. Run the batch.
6. **Interactive (6):** by hand for now, or send me `--inspect-fields` output
   to automate.