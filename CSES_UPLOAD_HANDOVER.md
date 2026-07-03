# CSES → CHT-oj Bulk Upload — Project Handover

> Hand-off notes so a fresh session (or another developer) can continue without the
> previous chat history. Read this once top-to-bottom; everything needed is here.
> The current source of truth for problem uploading is **`upload_reviewed.py`** (often renamed to `upload.py` locally). The current source of truth for contest creation/management is **`contest_tool_jsonfix.py`** (or the latest `contest_tool.py` after copying that file over). This doc explains why/how.

---

## 1. Goal & context

Upload all **CSES problems** (statements, test data, editorials, images, in Vietnamese)
onto a self-hosted online judge.

- **Target OJ:** `https://oj.thptchuyenhatinh.edu.vn` — a fork of **VNOJ/DMOJ**
  (repo: `ntanthedev/CHT-oj`).
- **Content source:** `ntanthedev/CSES-Problems-set` (~2.9 GB, 400 problems).
- **Operator:** the OJ **superuser** (`ntannn`), **no 2FA**.
- **Hard constraint:** the operator has **no SSH** to the server. Everything is driven
  **over HTTP from the operator's own machine** with an admin login — *not* `manage.py`.

The tool that does problem upload is **`upload_reviewed.py`** (run locally, often renamed `upload.py`). Contest creation is handled separately by **`contest_tool_jsonfix.py`**.

---

## 2. Current status / what's left

Working end-to-end: create problem, test data, editorial, **images** (upload + center),
Vietnamese statement, and bulk-publish. Validated locally; first real problems uploaded fine.

**Final language decision: Vietnamese only.** The Vietnamese statement goes into the
main `description` (`--vi`). The English `ProblemTranslation` step (`--bilingual`) is
**dropped** — bilingual rendering is unstable on this CHTOJ build and the admin route
was fragile. Do **not** use `--bilingual`.

**Left to do:** finish the full 400-problem run, group by group, once each group's
`statement_vi.md` files are generated.

**Latest tool versions after 2026-07-03 review:** use `upload_reviewed.py` for problem upload and `contest_tool_jsonfix.py` for contest creation. Older `contest_tool.py` versions can fail on `format_config` with `" value must be valid JSON."`.

### Recommended run sequence
1. `pip install requests beautifulsoup4 lxml`
2. Dry run (offline parse check): `python upload_reviewed.py --root . --dry-run`
3. Test one *image* problem first: `python upload_reviewed.py --user ntannn --root . --only 1625 --vi --with-editorial --editorial-public --debug`
4. Verify in the UI (see §9), then run a whole group, e.g.:
   `python upload_reviewed.py --user ntannn --root . --only 1068 1069 1070 ... --vi --with-editorial --editorial-public`
5. Re-run any group with `--overwrite` to refresh statements/limits/data in place.

> The script auto-prints a full **traceback on the first failure** (and `[file:line]`
> on every failure). If anything breaks, that traceback pinpoints the exact line.

---

## 3. Source repo layout (`CSES-Problems-set`)

```
<Category>/<ID>_<Name>/
    statement_en.md      # English statement; time/memory limits live INSIDE it
    statement_vi.md      # Vietnamese translation (subagent-generated; may be absent)
    analysis_en.md       # editorial (English)
    analysis_vi.md       # editorial (Vietnamese; optional)
    solution.cpp         # reference solution (not uploaded)
    tests_<ID>.zip       # test data: N.in / N.out at the zip ROOT
    <64-hex-hash>        # image files (PNG/JPEG/…), NO extension, referenced by hash
```

**Statement format** (consistent across all 400):
```
# 1068 - Weird Algorithm
* **Time limit:** 1.00 s
* **Memory limit:** 512 MB

<body...>
# Input
# Output
# Constraints
# Example
```
- Inline math `$...$`, display math `$$...$$`. Section headers are **H1 (`#`)**.
- Time limits: all `1.00 s`. Memory: `128 MB` or `512 MB`.

**Known data facts**
- 400 problems, **4890 test cases** total (2–76 per problem).
- **3 corrupt zips** (broken upstream — missing central directory): IDs
  **`2133`, `3410`, `3411`** → the tool skips them; re-download those test sets.
- **Images:** referenced as `![alt](<hash>)`; the `<hash>` is the filename of an image
  in the same folder, **with no extension** (VS Code previews it; the OS doesn't know
  the type from the name). **12 problems** use images, **29 image files** total
  (e.g. problem **1625**).

---

## 4. What the tool does to each statement (text pipeline)

1. **Limits** are read from `statement_en.md` (stable English labels). This is critical:
   translated `statement_vi.md` renames "Time/Memory limit" to Vietnamese, so reading
   limits from the vi file fails and falls back to 256 MB — wrong.
2. The redundant top limit bullets (`* **... :** 1.00 s`) and the title H1 are
   **stripped** from the body, **language-agnostically** (works even if a subagent
   wrote "1.00 giây").
3. Section headers are **down-shifted `#` → `##`** so they render a notch smaller
   (the renderer also bumps headers +2 internally).
4. **Inline math `$...$` → `~...~`** (VNOJ's markdown only recognizes `~...~` inline and
   `$$...$$` display). Code fences/spans and escaped `\$` are preserved.
5. **Images:** each `![](hash)` → the image file is uploaded and the reference is
   rewritten to `<center><img src="MEDIA_URL"></center>` (centered). The image type is
   detected from magic bytes since the files have no extension.

---

## 5. Key VNOJ/DMOJ endpoints & fields (so you don't re-derive them)

All confirmed by reading the `ntanthedev/CHT-oj` source.

### Auth
- `POST /accounts/login/` with `username`, `password`, `csrfmiddlewaretoken`, and a
  `Referer` header (Django strict-referer on HTTPS). A `requests.Session` keeps the
  `sessionid` cookie. The same session authorizes the front-end **and** `/admin/`.
  **2FA is not supported.**

### Create problem (front-end) — `POST /problems/create`
- View `ProblemCreate`, form `ProblemEditForm`. Needs perm `judge.add_problem`
  (superuser passes). Distinct from `/problems/suggest`.
- `is_public` is **removed** from the global form → new problems are **hidden** until
  the publish step.
- The view auto-adds the creator to curators and sets `allowed_languages` to all
  runtimes flagged `include_in_problem`.
- Fields (input name = model field): `code`, `name`, `description`, `time_limit`
  (seconds), `memory_limit` (**KB**), `points`, `partial` (checkbox; default ON → we
  turn OFF), `source`, `types` (pk; Select2 with options in HTML), `group` (pk; Select2),
  `submission_source_visibility_mode`, `testcase_visibility_mode`, `testers`,
  `statement_file`.
- **Labels are Vietnamese.** Group dropdown contains `Chưa phân loại`, **`CSES`**, …
  We match by label and use group **CSES**; resolution never submits an empty value
  (empty group/type → "Trường này là bắt buộc").
- `testcase_visibility_mode`: **`A` = always visible ("Có thể xem")**, `C` = out-of-contest,
  `O` = authors only (site default). We use `A`.

### Update existing problem — `POST /problem/<code>/edit`
- Same `ProblemEditForm` (front-end edit). Used by `--overwrite` to refresh
  description/limits/points/visibility. It **re-resolves group/type** so old problems
  that were created without a group/type don't resubmit empty (`"" is not a valid value`).

### Test data — `POST /problem/<code>/test_data`  (multipart)
- Data form prefix **`problem-data`**: `problem-data-zipfile` (file),
  `problem-data-checker`=`standard` (token compare, matches CSES),
  `problem-data-grader`=`standard`, `problem-data-checker_type`=`default`,
  `problem-data-io_method`=`standard`; other `*-args`/`*-output_limit` empty.
- Cases formset prefix **`cases`**: `cases-TOTAL_FORMS`/`INITIAL_FORMS`/… and per row
  `cases-<i>-id` (empty), `-order`, `-type`=`C`, `-input_file`=`N.in`,
  `-output_file`=`N.out`, `-points`=`1` (everything else empty/omitted).
- Server generates `init.yml` via `ProblemDataCompiler`. Each case = 1 pt; with
  `partial=False` the problem is all-or-nothing (CSES-style).

### Editorial (Solution) — front-end `POST /problem/<code>/edit`
- `Solution` is admin-inline-only as a model, BUT the front-end edit page renders a
  **solution formset** in the same form. We use the front-end (simpler than admin).
- Fields: `is_public`, `publish_on` (`<input type=date>` → `YYYY-MM-DD`),
  `authors` (optional, leave empty), `content`. Formset prefix **`solution`**.
- Strategy: GET the edit form → keep every field → fill one solution row → POST.

### Publish / unpublish (bulk) — admin actions
- `POST /admin/judge/problem/?q=cses_` with `select_across=1` and action
  `make_public_and_update_publish_date` → publishes **all** `cses_*` at once
  (`is_public=True`, `date=now`, rescore); or action `make_private` → hides them.
- Auto-runs (publish) at the end of an upload unless `--no-publish`.
- Exposed standalone via `--publish-only` / `--unpublish-only` (no upload). With `--only`
  it resolves each problem's admin pk and acts on just that subset
  (`_selected_action=<pk>`); without `--only` it acts on the whole `cses_*` set.

### Markdown / math
- Renderer `markdown2` + `latex` extra: regex `(~.*?~)|(\$\$.*?\$\$)` → inline `~...~`,
  display `$$...$$`. CSES `$...$` inline is converted to `~...~`.
- The `problem` markdown style has **`safe_mode: False`** → raw HTML allowed; bleach
  whitelist permits `<center>`, `<div>`, `<img>` (incl. `align`/`style`) → image
  centering via `<center><img ...></center>` works.

### Images — `POST /widgets/martor/upload-image`
- View `martor_image_uploader`, nested under the `widgets/` include — full path is
  **`/widgets/martor/upload-image`** (NOT `/martor/...`, which 404s). Requires header
  **`X-Requested-With: XMLHttpRequest`**, `csrfmiddlewaretoken`, and the file field
  **`markdown-image-upload`**. Staff users (we are) → stored in local media (permanent
  URL). Returns JSON with a `link`. Files are extensionless → the tool detects the type
  from magic bytes (`detect_image`) and sends a proper filename + MIME.

### Translation (ProblemTranslation) — admin-only, **dropped**
- `ProblemTranslation` is admin-inline-only (`/admin/judge/problem/<pk>/change/`,
  formset prefix `translations`). The admin form also carries the `allowed_languages`
  M2M multi-select, which must be preserved in full or it wipes submission languages.
  This path (`--bilingual`) proved fragile and is **not used** — Vietnamese-only.

---

## 6. CLI reference (`upload_reviewed.py`, usually copied to `upload.py`)

Deps: `pip install requests beautifulsoup4 lxml` (lxml important — the create page's
Martor editor confuses the stdlib HTML parser).

```
--root PATH              (required) path to CSES-Problems-set; "." if the script is inside it
--site URL               default https://oj.thptchuyenhatinh.edu.vn
                         (must be a FULL https:// URL; just omit it to use the default)
--user NAME              admin username (required for a real run)
--password PW            prompted securely if omitted (preferred)
--vi                     prefer statement_vi.md / analysis_vi.md (fallback to en)
--lang CODE              same as --vi but explicit (e.g. --lang vi)
--code-prefix STR        default "cses_"  (-> cses_1068)
--points FLOAT           default 1.0 (VNOJ scale 0–2)
--partial                allow partial scoring (default OFF = CSES binary)
--group NAME             problem group label; default "CSES"
--default-type NAME      fallback problem type; default "Chưa phân loại"
--testcase-visibility {visible|out-contest|authors}   default "visible" (= "Có thể xem")
--with-editorial         upload analysis_<lang>.md as the editorial (Solution)
--editorial-public       make the editorial publicly visible
--no-publish             upload but DON'T publish at the end (problems stay hidden)
--publish-only           don't upload — just make cses_* problems PUBLIC, then exit
--unpublish-only         don't upload — just make cses_* problems PRIVATE, then exit
--overwrite              refresh existing problems (statement/limits + test data + editorial)
--only ID [ID ...]       restrict to specific CSES IDs (also scopes publish/unpublish-only)
--sleep SECONDS          delay between problems (default 0.5)
--dry-run                parse locally and report; no network
--debug                  print full tracebacks and dump pages on form-not-found
--bilingual              (NOT USED) would add the other language as a translation
```

### Decisions baked in
- **Points:** 1.0/problem · **Scoring:** `partial=False`, each case 1 pt (binary AC).
- **Group:** `CSES` · **Testcase visibility:** `visible` ("Có thể xem").
- **Code:** `cses_<ID>` · **Titles:** kept in English (only the body is Vietnamese).
- **Language:** **Vietnamese only** in `description` (`--vi`); no English translation.
- **Editorial:** uploaded and **public** (`--with-editorial --editorial-public`).
- **Auto-publish:** yes.

### Standard command
```bash
python upload_reviewed.py --user ntannn --root . --vi --with-editorial --editorial-public
```
Refresh an already-uploaded group (also repairs old problems missing group/type):
```bash
python upload_reviewed.py --user ntannn --root . --only <IDs...> \
    --vi --with-editorial --editorial-public --overwrite
```

### Resume behaviour (safe to re-run)
A problem that already exists is **skipped entirely** on a normal run — no re-create,
no re-upload, no errors, no duplicates. So you can re-run the standard command as many
times as you like; it only processes the not-yet-uploaded problems. To deliberately
refresh existing ones, add `--overwrite`.

### Visibility control (publish / hide)
Problems are created **hidden**. By default the standard command publishes all `cses_*`
at the end. To control this:
```bash
# Upload but keep everything HIDDEN (don't publish at the end):
python upload_reviewed.py --user ntannn --root . --vi --with-editorial --editorial-public --no-publish

# Later: make them PUBLIC (no re-upload, just flips visibility, then exits):
python upload_reviewed.py --user ntannn --root . --publish-only              # all cses_*
python upload_reviewed.py --user ntannn --root . --only 1068 1069 --publish-only   # a subset

# Hide them again:
python upload_reviewed.py --user ntannn --root . --unpublish-only            # all cses_*
python upload_reviewed.py --user ntannn --root . --only 1068 1069 --unpublish-only # a subset
```
`--no-publish` is a *modifier* on an upload run (upload, stay hidden). `--publish-only`
/ `--unpublish-only` are *standalone* modes that upload nothing and only flip visibility
via the admin actions `make_public_and_update_publish_date` / `make_private`.

### Internal notes (for editing the script)
- `form_defaults(form)` → name→value dict (front-end forms).
- `form_payload_multi(form)` → list of (name,value) tuples preserving multi-select
  values (only needed for the unused admin/translation path).
- `resolve_option(options, *labels)` → never returns empty if a real option exists.
- `convert_math`, `downshift_headers`, `parse_statement`, `process_images`,
  `detect_image`, `LIMIT_LINE_RE`, `IMG_RE` handle text/images.
- CSRF: every POST GETs a fresh token and sets a `Referer` header. Success = 302
  (`allow_redirects=False`); a 200 = form re-rendered with errors → `show_errors()`.

---

## 7. Translation generation (subagents)

The tool does **not** translate; it consumes `statement_vi.md` / `analysis_vi.md` if
present (else falls back to English). Generate them with subagents (Claude Code /
DeepSeek) using a **fixed prompt + glossary + a validation pass**.

**Translator prompt** (writes `<name>_vi.md` next to `_en`):
```
You are a competitive-programming translator. Translate the CSES statement/editorial
from English to Vietnamese, writing <name>_vi.md in the same folder as the _en file.

HARD RULES (violations corrupt the problem):
1. Translate PROSE ONLY. Copy verbatim, unchanged:
   - All math: $...$, $$...$$, ~...~ (incl. \le, \frac, \rightarrow, spacing, indices).
   - All code ```...``` and inline `...`, including sample input/output.
   - All numbers, variables, function names, symbols, links, images ![](...).
   - Markdown structure: heading count/levels (#), bullets, tables, bold/italic.
   - The two top "Time limit / Memory limit" bullet lines — DO NOT translate or alter
     them (keep the English so the uploader can read the limits).
2. Keep section headers in place; translate titles: Input→Dữ liệu vào, Output→Kết quả,
   Constraints→Giới hạn, Example→Ví dụ, Explanation→Giải thích. No added/removed sections.
3. Consistent glossary: array→mảng, string→xâu, prefix sum→tổng tiền tố,
   segment tree→cây phân đoạn, binary search→tìm kiếm nhị phân,
   dynamic programming→quy hoạch động, graph→đồ thị, node/vertex→đỉnh, edge→cạnh,
   tree→cây, subtree→cây con, weight→trọng số, query→truy vấn,
   time/space complexity→độ phức tạp thời gian/bộ nhớ, test case→bộ test.
4. Natural problem-statement tone; neutral address. No commentary, no summary, no
   dropped sentences. Leave image references ![](hash) untouched.
5. Output ONLY the translated Markdown — no explanations, no ```markdown wrapper.

SELF-CHECK before writing: counts of $...$, $$...$$, ~...~ and ``` blocks must equal
the source. If they differ, fix and re-check.
```
**Validation:** for each pair, compare counts of `$...$`, `$$...$$`, inline code, and
code fences between `_en` and `_vi`; re-translate any mismatch. Subagents must NOT add
`<div>`/`<center>` for images — the uploader handles image upload + centering.

---

## 8. Gotchas / troubleshooting

- **`--site ...` → `MissingSchema`**: `...` is a placeholder. Omit `--site` (uses the
  default) or pass the full `https://…` URL. The tool now errors with a clear hint.
- **"Could not find the create-problem form"**: account lacks `judge.add_problem`, or
  the page didn't parse — install `lxml`; run with `--debug` (saves `debug_create.html`).
- **"Trường này là bắt buộc" on create**: group/type label mismatch → now matched to
  Vietnamese labels (`CSES`, `Chưa phân loại`) and never sent empty.
- **Memory shows 256 MB / limit lines in the body**: caused by translated limit labels;
  fixed — limits come from `statement_en.md`, limit bullets stripped language-agnostically.
  Re-run with `--overwrite`.
- **`"" is not a valid value` on overwrite (e.g. old 1068)**: the problem had no
  group/type; `--overwrite` now re-resolves them. Re-run with `--overwrite`.
- **Image `non-JSON (status 404)`**: the endpoint is `/widgets/martor/upload-image`
  (fixed). Extensionless files are handled by magic-byte detection.
- **3 corrupt test zips** (`2133`, `3410`, `3411`): re-download those test sets.
- **Any other failure**: the tool prints a full **traceback on the first failure** and
  `[file:line]` on each — use that to pinpoint, or send it on.
- **`--bilingual` (English translation)**: dropped. The admin route was fragile.

---

## 9. Post-run verification checklist (after the first problem of a batch)

Open the problem on the OJ and confirm:
- [ ] Body shows in **Vietnamese**.
- [ ] Side panel shows correct **time/memory** (e.g. 1.0 s / 512 M), matching the body
      (no duplicate limit lines).
- [ ] Section headers render one level smaller (`##`).
- [ ] Inline math renders (no literal `$` signs).
- [ ] **Submission languages** (C, C++, Python, …) are all present.
- [ ] Editorial appears under "Đọc lời giải" (public).
- [ ] Image problems (e.g. **1625**) show the image, **centered**.
- [ ] Group is **CSES**; testcase visibility is **"Có thể xem"**; code is `cses_<ID>`.
- [ ] Submitting the reference `solution.cpp` gets **AC** (sanity-checks the test data).

---

## 10. Server-side alternative (only if SSH ever returns)

A Django management command **`import_cses.py`** also exists (drop into
`judge/management/commands/`, run `python manage.py import_cses /path/to/repo`). It is
faster and more robust (writes DB + data dir directly via `ProblemDataCompiler`), but
needs shell access, which the operator currently lacks. Same math/header/limit fixes
apply. Keep it for the day SSH returns.

---

## 11. 2026-07-03 update — `contest_tool.py` / contest creation

A separate HTTP admin tool was added/reviewed for creating and editing contests on CHT-OJ:

- Working file after fixes: **`contest_tool_jsonfix.py`**. It may be copied/renamed to `contest_tool.py` locally.
- It uses Django admin, not front-end routes:
  - create: `GET/POST /admin/judge/contest/add/`
  - edit: `GET/POST /admin/judge/contest/<pk>/change/`
- It preserves the full admin form defaults and fills only the intended fields.
- It resolves problem PKs via `/admin/judge/problem/?q=<code>` and the author profile PK via `/admin/judge/profile/?q=<username>`.

### Source files used to verify contest behavior

The following CHT-OJ source files were uploaded/read and used as the basis for the fixes:

```text
judge/admin/contest.py
judge/models/contest.py
judge/contest_format/default.py
judge/contest_format/registry.py
judge/contest_format/vnoj.py
```

Confirmed source facts:

- `ContestAdmin` uses `ContestProblemInline` with fields:
  `problem`, `points`, `partial`, `is_pretested`, `max_submissions`,
  `output_prefix_override`, `order`, plus readonly rejudge/rescore columns.
- The inline formset prefix found on the live site is `contest_problems`.
- `ContestProblem.partial` has `default=True`; for CSES-style binary scoring, the tool
  must remove the `partial` checkbox from real rows unless `--partial` is explicitly used.
- `Contest.format_name` defaults to `default`, but `contest_format.registry.choices()`
  returns sorted choices. The live form may show AtCoder first, so the tool must explicitly
  send `format_name=default` rather than relying on the first `<option>`.
- `Contest.banned_judges` is a ManyToMany to `judge.Judge`, not `Profile`. Do not use
  the `ntannn` option in `banned_judges` as an author/profile.
- `Contest.authors` is a ManyToMany to `Profile`; the tool correctly fills the profile
  PK for the admin user, e.g. `authors -> ntannn (pk 8)`.
- `Contest.format_config` is a `JSONField`. The old dry-run showed `format_config '\n'`,
  which fails on real POST with `" value must be valid JSON."`. The fixed tool sends
  `format_config='null'` for the default format unless `--format-config` is provided.

### Important fixes made to `contest_tool.py`

1. Added explicit `--format`, default `default`.
   - Prevents silent creation as `atcoder` when the form does not render `selected`.
2. Added optional `--partial`.
   - Default behavior removes `contest_problems-<i>-partial` from real rows.
   - `--partial` re-adds `partial=on` for each real row.
3. Kept `TOTAL_FORMS` dynamic but never shrinks below the form's current value.
   - If the add form renders 3 empty rows and you add 3 problems, keep `TOTAL_FORMS=3`.
   - If you add 5 problems, raise `TOTAL_FORMS=5`.
   - The `__prefix__` template row may still contain `partial=on`; this is harmless because
     Django ignores `__prefix__` rows.
4. Fixed `format_config` JSON validation.
   - Send `null` for default format.
   - Added `--format-config` for future custom JSON, e.g. VNOJ penalty config.
5. Normalized empty textareas that were serialized as `\n`:
   - `problem_label_script`, `csv_ranking`, `summary`.
6. Added safer `items_set()` behavior in newer reviewed versions: delete duplicate keys
   before setting a new single value.
7. For `add-problems`, append from `INITIAL_FORMS`, not `TOTAL_FORMS`, so extra blank admin
   rows do not create order gaps.
8. Added sanity checks for real contest rows before POST.

### Known good dry-run for contest create

This dry-run was checked and is expected to be safe:

```powershell
python contest_tool_jsonfix.py create --user ntannn `
  --key luyentap01 `
  --name "test csesssss" `
  --start "2026-07-10 19:00" `
  --end "2026-07-10 22:00" `
  --problems 1068 1083 1625 `
  --points-each 100 `
  --format default `
  --dry-run
```

Expected key payload details:

```text
format_name                              'default'
format_config                            'null'
authors                                  '8'
contest_problems-TOTAL_FORMS             '3'
contest_problems-0-problem               '<pk for cses_1068>'
contest_problems-1-problem               '<pk for cses_1083>'
contest_problems-2-problem               '<pk for cses_1625>'
# no contest_problems-0-partial / 1-partial / 2-partial unless --partial is used
```

If POST returns status 200 with:

```text
" value must be valid JSON.
```

then the operator is still running an older `contest_tool.py`; copy over `contest_tool_jsonfix.py`.

### Contest create command after fixes

```powershell
python contest_tool_jsonfix.py create --user ntannn `
  --key luyentap01 `
  --name "test csesssss" `
  --start "2026-07-10 19:00" `
  --end "2026-07-10 22:00" `
  --problems 1068 1083 1625 `
  --points-each 100 `
  --format default
```

Add `--visible` only if the contest should be public immediately.

---

## 12. 2026-07-03 update — `upload.py` review against full CHT-OJ source

The full CHT-OJ GitHub source was uploaded as `oj-master.zip` and extracted locally. The upload tool was reviewed against the real source, not just upstream assumptions. The reviewed/fixed script is:

```text
upload_reviewed.py
```

This can be copied over local `upload.py` once accepted.

### High-level review result

The core routes and strategy were confirmed as correct:

- Login: `POST /accounts/login/`
- Create problem: `POST /problems/create`
- Edit problem: `POST /problem/<code>/edit`
- Test data: `POST /problem/<code>/test_data`
- Image upload: `POST /widgets/martor/upload-image`
- Publish/unpublish: admin actions on `/admin/judge/problem/`
- Editorial: front-end problem edit form with `solution` formset

`--bilingual` remains intentionally dropped. Do not revive it unless someone wants to rework the fragile admin `ProblemTranslation` inline path carefully.

### Fixes made in `upload_reviewed.py`

1. **Overwrite test data now deletes old cases.**

   In real CHT-OJ, the test-data page has a `cases` formset. If an existing problem has old cases, a naive overwrite that sends `cases-INITIAL_FORMS=0` can append new cases without deleting old ones. The reviewed script now preserves existing initial rows, marks them with `DELETE=on`, and appends new cases after `INITIAL_FORMS`.

   Expected overwrite behavior:

   ```text
   cases-INITIAL_FORMS = <old case count>
   cases-TOTAL_FORMS   = <old case count + new case count>
   cases-0-DELETE      = on
   cases-1-DELETE      = on
   ...
   cases-<old+n>-input_file/output_file/points = new cases
   ```

2. **Overwrite now resets problem `partial`.**

   Create already removed `partial` by default for CSES binary scoring. Older `update_problem()` preserved whatever checkbox state was on the edit form. The reviewed script now removes `partial` on overwrite unless `--partial` is explicitly passed.

3. **JPEG image upload now uses `.jpeg`, not `.jpg`.**

   The CHT-OJ settings contain a subtle safe-extension issue where `.jpg` may not be accepted as expected, while `.jpeg` is safe. The reviewed script maps JPEG magic bytes to `.jpeg` and MIME `image/jpeg`.

4. **Image upload response is now validated.**

   Martor can return JSON with a `link` string that is actually an error message. The reviewed script now checks that `link` looks like a usable URL/path before rewriting Markdown image references.

5. **Problem edit/editorial payloads now preserve multi-value fields.**

   The edit form contains multiple formsets and multi-select fields. The reviewed script uses list-style `(name, value)` payloads where needed instead of lossy dict conversion, reducing the chance of wiping fields such as `types` or language limits.

6. **Admin search query values are URL-encoded.**

   Admin PK lookup and publish-only query building now use safe quoting for search values.

7. **Checker manifest validation is stricter.**

   `checker_args` must be a JSON object/dict. Invalid manifest entries fail early before POSTing to the OJ.

### Offline checks run for `upload_reviewed.py`

```bash
python3 -m py_compile /mnt/data/upload_reviewed.py
```

Additional local tests confirmed:

```text
upload_data overwrite payload OK
jpeg ext OK
```

### Recommended command after this review

Dry-run:

```bash
python upload_reviewed.py --root . --vi --dry-run
```

Test one known image problem:

```bash
python upload_reviewed.py --user ntannn --root . --only 1625 --vi --with-editorial --editorial-public --debug
```

Full/resume run:

```bash
python upload_reviewed.py --user ntannn --root . --vi --with-editorial --editorial-public
```

Overwrite repair for already uploaded problems:

```bash
python upload_reviewed.py --user ntannn --root . --only 1068 1083 1625 \
  --vi --with-editorial --editorial-public --overwrite --debug
```

### What to verify after using `upload_reviewed.py`

For a repaired/uploaded problem, check:

- old duplicate test cases are gone after `--overwrite`;
- problem-level `partial` is off unless `--partial` was intended;
- image problem 1625 displays the image normally;
- editorial still appears and is public if `--editorial-public` was used;
- all submission languages remain available;
- `solution.cpp` still gets AC.

---

*End of handover.*