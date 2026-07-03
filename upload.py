#!/usr/bin/env python3
"""
Upload CSES problems to a DMOJ / VNOJ / CHT-oj site purely over HTTP, from your
own machine (no SSH / no manage.py needed). You only need an admin account.

It reproduces, request-by-request, exactly what an admin does in the browser:

  1. log in                       -> POST /accounts/login/
  2. create the problem           -> POST /problems/create        (ProblemEditForm)
  3. upload the test data + cases -> POST /problem/<code>/test_data (ProblemDataView)
  4. (optional) publish in bulk   -> admin action make_public_and_update_publish_date

Problems created via the public form are HIDDEN by default (the form drops the
`is_public` field), so step 4 flips every cses_* problem to public in one POST.

--------------------------------------------------------------------------------
INSTALL (on your machine):
    pip install requests beautifulsoup4

RUN:
    # dry run first - just parses local files, no network:
    python cses_http_upload.py --root /path/to/CSES-Problems-set --dry-run

    # real upload (will prompt for password if --password is omitted):
    python cses_http_upload.py \
        --site https://oj.thptchuyenhatinh.edu.vn \
        --user YOUR_ADMIN_USERNAME \
        --root /path/to/CSES-Problems-set \
        --only 1068 1083            # optional: a subset; omit to do all

    python cses_http_upload.py --help     # all options
--------------------------------------------------------------------------------
Notes
* Scoring mirrors CSES (binary AC): partial OFF, every case worth 1 point,
  problem worth --points (default 1.0, the VNOJ scale).
* `group` and `types` must already exist on the site; the script reads the
  dropdowns on the create page and matches by name (falls back to a default).
* 2FA is NOT supported by this script. If your admin account has 2FA, make a
  dedicated staff account without 2FA that has add_problem / change_problem.
* Re-running is safe: existing problems are skipped unless --overwrite (which
  re-uploads their test data).
* Problems needing a non-standard checker (floating point tolerance, "multiple
  valid answer", "any order") are driven by an optional CHECKER_MANIFEST.json
  at the repo root - see load_checker_manifest() / CHECKER_MODES below. A
  problem with no entry keeps today's plain token-compare checker, unchanged.
  Run `python upload.py --inspect-fields <existing-code>` once against any
  already-uploaded problem to confirm the live checker/grader field names
  before trusting this on a real batch.
"""

import argparse
import datetime
import getpass
import json
import os
import re
import sys
import time
import traceback
import zipfile
from urllib.parse import quote

try:
    import requests
    from bs4 import BeautifulSoup
except ImportError:
    sys.exit('Missing deps. Run:  pip install requests beautifulsoup4')

# Prefer the more robust lxml parser if available (the create page embeds a
# Martor markdown editor whose HTML can confuse the built-in parser).
try:
    import lxml  # noqa: F401
    _PARSER = 'lxml'
except Exception:
    _PARSER = 'html.parser'

# --------------------------------------------------------------------------- #
# Parsing helpers (same logic as the server-side importer)
# --------------------------------------------------------------------------- #
TIME_RE = re.compile(r'Time limit:\*\*\s*([0-9.]+)\s*s', re.I)
MEM_RE = re.compile(r'Memory limit:\*\*\s*([0-9.]+)\s*(GB|MB|KB)', re.I)
FOLDER_RE = re.compile(r'^\s*(\d+)[_\-\s]+(.+?)\s*$')
CASE_RE = re.compile(r'(?:^|/)(\d+)\.(in|out)$', re.I)
MEM_FACTOR = {'GB': 1024 * 1024, 'MB': 1024, 'KB': 1}

# Testcase visibility choices on the Problem form:
#   'A' = always visible      ("Co the xem")
#   'C' = visible out-contest  ("Hien thi khi khong o trong ky thi")
#   'O' = authors only         ("Chi tac gia co the xem")  -- the site default
TESTCASE_VIS = {'visible': 'A', 'out-contest': 'C', 'authors': 'O'}

# --------------------------------------------------------------------------- #
# Checker support (CHECKER_MANIFEST.json)
# --------------------------------------------------------------------------- #
# CHT-oj is a VNOJ/DMOJ fork. The live ProblemData model (judge/models/problem_data.py)
# defines exactly these choices - confirmed by reading the VNOI-Admin/OJ source, which
# CHT-oj forked from:
#
#   CHECKERS = (('standard', 'Standard'), ('bridged', 'Custom checker'),
#               ('floats', 'Floats'), ('floatsabs', 'Floats (absolute)'),
#               ('floatsrel', 'Floats (relative)'), ('identical', 'Byte identical'),
#               ('linecount', 'Line-by-line'))
#   CUSTOM_CHECKERS = (('themis', ...), ('testlib', 'Testlib checker'), ('cms', ...),
#                       ('coci', ...), ('peg', ...), ('default', 'DMOJ checker'))
#   GRADERS = (('standard', ...), ('interactive', 'Interactive'),
#              ('signature', 'IOI-style'), ('output_only', ...))
#
# NOTE: this fork's CHECKERS list has NO 'sorted'/'unordered' option (stock DMOJ has
# one, this fork dropped it) - so "any order" problems need a bridged/testlib checker
# too, same as "multiple valid answer" problems. There is no built-in shortcut for them.
#
# We resolve the actual <option value=...> the same way group/type are already
# resolved: by matching the VISIBLE LABEL text on the live page (Vietnamese first,
# English/slug as fallback), never by hardcoding a guessed value. This survives
# translation/relabeling differences between CHT-oj and upstream VNOJ.
CHECKER_LABELS = {
    'standard':  ['Mặc định', 'Standard'],
    'bridged':   ['Trình chấm ngoài', 'Custom checker'],
    'floats':    ['Số thực', 'Floats'],
    'floatsabs': ['Số thực (tuyệt đối)', 'Floats (absolute)'],
    'floatsrel': ['Số thực (tương đối)', 'Floats (relative)'],
    'identical': ['So sánh byte', 'Byte identical'],
    'linecount': ['Dòng với dòng', 'Line-by-line'],
}
# Sub-format, only used/shown when checker == 'bridged'.
CHECKER_TYPE_LABELS = {
    'testlib': ['Testlib checker', 'testlib'],
    'themis':  ['Themis checker', 'themis'],
    'cms':     ['CMS checker', 'cms'],
    'coci':    ['COCI checker', 'coci'],
    'peg':     ['PEG checker', 'peg'],
    'default': ['DMOJ checker', 'default'],
}
# Not wired up to a POST path yet (see --inspect-fields) - kept here for the
# follow-up that adds interactive-problem support.
GRADER_LABELS = {
    'standard':    ['Standard', 'Mặc định'],
    'interactive': ['Interactive', 'Tương tác'],
    'signature':   ['Function Signature Grading (IOI-style)', 'Signature'],
    'output_only': ['Output Only'],
}

# VNOJ/DMOJ markdown uses ~...~ for INLINE math and $$...$$ for DISPLAY math.
# CSES uses $...$ inline, so rewrite inline $...$ -> ~...~ (display $$...$$ kept).
# Code blocks/spans and escaped \$ are preserved.
_FENCE_RE = re.compile(r'```.*?```|~~~.*?~~~', re.S)
_INLINE_CODE_RE = re.compile(r'`[^`\n]*`')
_DISPLAY_RE = re.compile(r'\$\$.+?\$\$', re.S)
_INLINE_MATH_RE = re.compile(r'\$(.+?)\$', re.S)


def convert_math(text):
    stash = []

    def keep(m):
        stash.append(m.group(0))
        return '\x00%d\x00' % (len(stash) - 1)

    text = _FENCE_RE.sub(keep, text)
    text = _INLINE_CODE_RE.sub(keep, text)
    text = text.replace('\\$', '\x00ESC\x00')
    text = _DISPLAY_RE.sub(keep, text)
    text = _INLINE_MATH_RE.sub(lambda m: '~%s~' % m.group(1), text)
    text = text.replace('\x00ESC\x00', '\\$')
    text = re.sub(r'\x00(\d+)\x00', lambda m: stash[int(m.group(1))], text)
    return text


# A redundant time/memory bullet at the top of a CSES statement, e.g.
#   * **Time limit:** 1.00 s      /  * **Giới hạn bộ nhớ:** 512 MB
# Language-agnostic: a bulleted, bolded "label:" followed by a number and one
# short unit token, then end of line. The real limits live in the side panel.
LIMIT_LINE_RE = re.compile(r'^\s*[*+\-]\s+\*\*[^*]+:\*\*\s*[0-9.]+\s*\S{0,5}\s*$')

# CSES images are stored as hash-named files in the problem folder and referenced
# as ![alt](<64-hex-hash>). We upload the file and rewrite the reference.
IMG_RE = re.compile(r'!\[([^\]]*)\]\(([0-9a-fA-F]{16,})\)')

_FENCE_TOGGLE_RE = re.compile(r'^\s*(```|~~~)')
_ATX_RE = re.compile(r'^(#{1,6})(\s)')


def downshift_headers(text):
    """Push every ATX heading one level deeper (# -> ##), so the CSES section
    headers (Input/Output/Constraints/Example) render a bit smaller. Code
    fences are left untouched."""
    out, in_fence = [], False
    for line in text.splitlines():
        if _FENCE_TOGGLE_RE.match(line):
            in_fence = not in_fence
            out.append(line)
            continue
        if not in_fence:
            m = _ATX_RE.match(line)
            if m and len(m.group(1)) < 6:
                line = '#' + line
        out.append(line)
    return '\n'.join(out)


def parse_statement(text, limits_text=None):
    """Return (time_limit_seconds, memory_kb, body_markdown).

    Time/memory limits are read from `limits_text` when given (always pass the
    English statement_en.md there, since translated statements rename the
    labels). The redundant limit bullets and the title H1 are stripped from the
    body, headings are pushed down one level, and inline math is converted.
    """
    src = limits_text if limits_text is not None else text
    tl = mem = None
    m = TIME_RE.search(src)
    if m:
        tl = float(m.group(1))
    m = MEM_RE.search(src)
    if m:
        mem = int(round(float(m.group(1)) * MEM_FACTOR[m.group(2).upper()]))

    body, dropped_title = [], False
    for line in text.splitlines():
        if not dropped_title and line.lstrip().startswith('# '):
            dropped_title = True
            continue
        if LIMIT_LINE_RE.match(line):
            continue
        body.append(line)
    return tl, mem, convert_math(downshift_headers('\n'.join(body).strip()))


def read_cases(zip_path):
    """Return sorted [(order, in_name, out_name)] from a tests zip."""
    pairs = {}
    with zipfile.ZipFile(zip_path) as zf:
        names = zf.namelist()
        for entry in names:
            m = CASE_RE.search(entry)
            if m:
                pairs.setdefault(int(m.group(1)), {})[m.group(2).lower()] = entry
    cases, order = [], 0
    for num in sorted(pairs):
        c = pairs[num]
        if 'in' in c and 'out' in c:
            order += 1
            cases.append((order, c['in'], c['out']))
    return cases, set(names)


# --------------------------------------------------------------------------- #
# Checker manifest: CHECKER_MANIFEST.json at the repo root, keyed by CSES id.
# --------------------------------------------------------------------------- #
# {
#   "1618": {"checker": "floats", "checker_args": {"precision": 6}},
#   "1625": {"checker": "bridged", "checker_type": "testlib", "checker_file": "checker.cpp"}
# }
# A problem with no entry (the vast majority) keeps today's behaviour: 'standard'.
# checker_file is a path relative to the problem's own folder (next to solution.cpp).
CHECKER_MODES = ('standard', 'bridged', 'floats', 'floatsabs', 'floatsrel', 'identical', 'linecount')


def load_checker_manifest(root, path=None):
    path = path or os.path.join(root, 'CHECKER_MANIFEST.json')
    if not os.path.exists(path):
        return {}
    with open(path, encoding='utf-8') as f:
        raw = json.load(f)
    manifest = {}
    for pid, spec in raw.items():
        if not isinstance(spec, dict):
            continue          # skip metadata keys like _comment, _status
        pid = str(pid)
        mode = spec.get('checker', 'standard')
        if mode not in CHECKER_MODES:
            sys.exit('CHECKER_MANIFEST.json: problem %s has unknown checker %r (must be one of %s)'
                     % (pid, mode, ', '.join(CHECKER_MODES)))
        args = spec.get('checker_args')
        if args is not None and not isinstance(args, dict):
            sys.exit('CHECKER_MANIFEST.json: problem %s checker_args must be a JSON object/dict' % pid)
        if mode == 'bridged':
            ctype = spec.get('checker_type', 'testlib')
            if ctype not in CHECKER_TYPE_LABELS:
                sys.exit('CHECKER_MANIFEST.json: problem %s has unknown checker_type %r (must be one of %s)'
                         % (pid, ctype, ', '.join(CHECKER_TYPE_LABELS)))
            spec.setdefault('checker_type', ctype)
            spec.setdefault('checker_file', 'checker.cpp')
        manifest[pid] = spec
    return manifest


# --------------------------------------------------------------------------- #
# Small HTML-form helpers
# --------------------------------------------------------------------------- #
def form_containing(soup, field_name):
    """Return the <form> element that contains an input/select/textarea
    whose name == field_name."""
    for form in soup.find_all('form'):
        if form.find(attrs={'name': field_name}):
            return form
    return None


def form_defaults(form):
    """Collect name -> default value for all controls in a form."""
    data = {}
    for el in form.find_all(['input', 'select', 'textarea']):
        name = el.get('name')
        if not name:
            continue
        tag = el.name
        if tag == 'textarea':
            data[name] = el.text or ''
        elif tag == 'select':
            opt = el.find('option', selected=True) or el.find('option')
            data[name] = (opt.get('value', '') if opt else '')
        else:  # input
            itype = (el.get('type') or 'text').lower()
            if itype in ('checkbox', 'radio'):
                if el.has_attr('checked'):
                    data[name] = el.get('value', 'on')
            elif itype in ('submit', 'button', 'file', 'image', 'reset'):
                continue
            else:
                data[name] = el.get('value', '')
    return data


def select_options(form, field_name):
    """Return {visible_label_lower: value} for a <select name=field_name>."""
    out = {}
    sel = form.find('select', attrs={'name': field_name})
    if sel:
        for opt in sel.find_all('option'):
            label = opt.get_text(strip=True).lower()
            out[label] = opt.get('value', '')
    return out


def show_errors(html):
    soup = BeautifulSoup(html, _PARSER)
    errs = [e.get_text(' ', strip=True) for e in soup.select('.errorlist, .alert-danger, ul.errorlist li')]
    return ' | '.join(e for e in errs if e)[:500] or '(no parseable error; check perms/fields)'


def form_payload_multi(form):
    """Like form_defaults but returns a LIST of (name, value) tuples and keeps
    ALL selected options of multiple selects. Required for the admin problem
    form, which has M2M fields (e.g. allowed_languages) that would otherwise be
    truncated to a single value and silently wipe the others."""
    items = []
    for el in form.find_all(['input', 'select', 'textarea']):
        name = el.get('name')
        if not name:
            continue
        tag = el.name
        if tag == 'textarea':
            items.append((name, el.text or ''))
        elif tag == 'select':
            selected = el.find_all('option', selected=True)
            if selected:
                for opt in selected:
                    items.append((name, opt.get('value', '')))
            elif not el.has_attr('multiple'):
                first = el.find('option')
                if first is not None:
                    items.append((name, first.get('value', '')))
        else:
            itype = (el.get('type') or 'text').lower()
            if itype in ('checkbox', 'radio'):
                if el.has_attr('checked'):
                    items.append((name, el.get('value', 'on')))
            elif itype in ('submit', 'button', 'file', 'image', 'reset'):
                continue
            else:
                items.append((name, el.get('value', '')))
    return items


def items_get(items, key):
    for k, v in items:
        if k == key:
            return v
    return None


def items_set(items, key, value):
    """Replace ALL existing pairs for key with a single (key, value)."""
    items[:] = [(k, v) for (k, v) in items if k != key]
    items.append((key, value))


def items_del(items, key):
    """Delete ALL pairs for key from a list-style payload."""
    items[:] = [(k, v) for (k, v) in items if k != key]


def first_nonempty(options):
    for v in options.values():
        if v:
            return v
    return ''


def resolve_option(options, *labels):
    """Return the value of the first option whose label matches; else the first
    non-empty option. Never returns an empty string if any real option exists."""
    for lab in labels:
        if lab and options.get(lab.lower()):
            return options[lab.lower()]
    return first_nonempty(options)


def resolve_strict(options, *labels, field=''):
    """Like resolve_option, but NEVER silently falls back to "the first option
    on the page" - for fields like checker/checker_type/grader, guessing wrong
    doesn't just fail loudly, it uploads with the WRONG checker and grades
    silently incorrectly. Raises with the full option list if nothing matches."""
    for lab in labels:
        if lab and options.get(lab.lower()):
            return options[lab.lower()]
    raise RuntimeError(
        'could not resolve option for %s: tried %r, available labels: %s'
        % (field, list(labels), sorted(options.keys()) or '(none found - is this the right field name?)'))


# magic-byte image type detection (CSES images are hash-named, no extension)
def detect_image(file_path):
    with open(file_path, 'rb') as f:
        sig = f.read(12)
    if sig[:8] == b'\x89PNG\r\n\x1a\n':
        return 'png', 'image/png'
    if sig[:3] == b'\xff\xd8\xff':
        # CHT-OJ settings accidentally omit .jpg from MARTOR_UPLOAD_SAFE_EXTS
        # ('.py' '.jpg' is concatenated into '.py.jpg'), while .jpeg is allowed.
        return 'jpeg', 'image/jpeg'
    if sig[:6] in (b'GIF87a', b'GIF89a'):
        return 'gif', 'image/gif'
    if sig[:4] == b'RIFF' and sig[8:12] == b'WEBP':
        return 'webp', 'image/webp'
    return 'png', 'image/png'   # sensible default


# --------------------------------------------------------------------------- #
# The uploader
# --------------------------------------------------------------------------- #
class Uploader:
    def __init__(self, base, debug=False):
        self.base = base.rstrip('/')
        self.debug = debug
        self.s = requests.Session()
        self.s.headers['User-Agent'] = 'cses-http-uploader/1.0'

    def url(self, path):
        return self.base + path

    def _diagnose(self, label, resp, soup):
        """Print why a page didn't contain the expected form, and save it."""
        title = soup.find('title')
        title = title.get_text(strip=True) if title else '(no title)'
        html = resp.text
        markers = {
            'status': resp.status_code,
            'final_url': resp.url,
            'title': title,
            'has name="code"': 'name="code"' in html,
            'has csrf token': 'csrfmiddlewaretoken' in html,
            'looks 403/denied': any(w in html.lower() for w in
                                    ('403', 'forbidden', 'permission', 'không có quyền', 'denied')),
            'looks like login page': 'name="password"' in html,
        }
        fname = 'debug_%s.html' % label
        try:
            with open(fname, 'w', encoding='utf-8') as f:
                f.write(html)
        except Exception:
            fname = '(could not save)'
        print('  --- DEBUG (%s) ---' % label)
        for k, v in markers.items():
            print('    %-22s %s' % (k + ':', v))
        print('    saved page to:        %s' % fname)
        print('  --- end DEBUG ---')

    def _get_soup(self, path):
        r = self.s.get(self.url(path), timeout=60)
        r.raise_for_status()
        return r, BeautifulSoup(r.text, _PARSER)

    def _csrf(self, soup):
        el = soup.find('input', attrs={'name': 'csrfmiddlewaretoken'})
        if el:
            return el.get('value')
        return self.s.cookies.get('csrftoken', '')

    def login(self, username, password):
        path = '/accounts/login/'
        r, soup = self._get_soup(path)
        form = form_containing(soup, 'password') or soup.find('form')
        payload = form_defaults(form) if form else {}
        payload['csrfmiddlewaretoken'] = self._csrf(soup)
        payload['username'] = username
        payload['password'] = password
        payload.setdefault('next', '/')
        resp = self.s.post(self.url(path), data=payload,
                           headers={'Referer': self.url(path)},
                           allow_redirects=False, timeout=60)
        if resp.status_code not in (301, 302):
            if 'two_factor' in resp.text or '2fa' in resp.text.lower():
                raise RuntimeError('Login hit a 2FA step - this script does not support 2FA.')
            raise RuntimeError('Login failed (status %s). Check username/password.' % resp.status_code)
        # confirm we are actually authenticated
        who = self.s.get(self.url('/'), timeout=60).text
        if 'logout' not in who.lower() and username.lower() not in who.lower():
            raise RuntimeError('Login appeared to redirect but session is not authenticated.')

    def problem_exists(self, code):
        r = self.s.get(self.url('/problem/%s' % code), allow_redirects=True, timeout=60)
        return r.status_code == 200

    # -- step 2: create ----------------------------------------------------- #
    def create_problem(self, code, name, body, tl, mem_kb, points, partial,
                       source, group_label, type_label, default_type_label,
                       testcase_visibility):
        path = '/problems/create'
        r, soup = self._get_soup(path)
        form = form_containing(soup, 'code')
        if form is None:
            if self.debug:
                self._diagnose('create', r, soup)
            raise RuntimeError('Could not find the create-problem form (permission denied?).')

        payload = form_defaults(form)

        # Resolve group + type to their primary keys via the on-page dropdowns.
        # Labels are matched case-insensitively; we NEVER submit an empty value
        # (an empty group/type is what caused the "this field is required" error).
        groups = select_options(form, 'group')
        types = select_options(form, 'types')

        group_pk = resolve_option(groups, group_label)
        type_pk = resolve_option(types, type_label, default_type_label)
        if not group_pk:
            raise RuntimeError('no usable "group" option found; available: %s'
                               % ', '.join(sorted(k for k in groups)) or '(none)')
        if not type_pk:
            raise RuntimeError('no usable "type" option found; available: %s'
                               % ', '.join(sorted(k for k in types)) or '(none)')

        payload['csrfmiddlewaretoken'] = self._csrf(soup)
        payload['code'] = code
        payload['name'] = name
        payload['description'] = body
        payload['time_limit'] = ('%g' % tl)
        payload['memory_limit'] = str(mem_kb)
        payload['points'] = ('%g' % points)
        payload['source'] = source
        payload['group'] = group_pk
        payload['types'] = type_pk
        payload['testcase_visibility_mode'] = testcase_visibility   # 'A' = always visible
        payload.setdefault('submission_source_visibility_mode', 'F')
        # partial is a checkbox: present => True. We want CSES-binary => off.
        payload.pop('partial', None)
        if partial:
            payload['partial'] = 'on'
        # never send a file statement / testers list
        payload.pop('statement_file', None)
        payload.pop('testers', None)

        resp = self.s.post(self.url(path), data=payload,
                           headers={'Referer': self.url(path)},
                           allow_redirects=False, timeout=120)
        if resp.status_code in (301, 302):
            return True
        raise RuntimeError('create failed: %s' % show_errors(resp.text))

    # -- step 3: test data + cases ------------------------------------------ #
    def upload_data(self, code, zip_path, cases, checker_spec=None, pdir=None):
        path = '/problem/%s/test_data' % code
        r, soup = self._get_soup(path)
        form = form_containing(soup, 'problem-data-zipfile') or soup.find('form')
        if form is None:
            if self.debug:
                self._diagnose('test_data', r, soup)
            raise RuntimeError('could not open the test_data form for %s' % code)
        defaults = form_defaults(form) if form else {}

        data = {}
        # carry over hidden/select defaults that belong to the data form
        for k, v in defaults.items():
            if k.startswith('problem-data-') or k == 'csrfmiddlewaretoken':
                data[k] = v
        data['csrfmiddlewaretoken'] = self._csrf(soup)
        data['problem-data-checker'] = 'standard'      # token compare, matches CSES
        data['problem-data-grader'] = 'standard'
        data.setdefault('problem-data-io_method', 'standard')
        data.setdefault('problem-data-checker_type', 'default')
        data.setdefault('problem-data-checker_args', '')
        data.setdefault('problem-data-grader_args', '')
        data.setdefault('problem-data-output_limit', '')
        data.setdefault('problem-data-io_input_file', '')
        data.setdefault('problem-data-io_output_file', '')

        # ---- optional custom checker (CHECKER_MANIFEST.json entry) --------- #
        # Only ~85/400 problems need this; everything else keeps the untouched
        # 'standard' path above. See CHECKER_MODES / CHECKER_LABELS up top.
        checker_file_path = None
        if checker_spec:
            mode = checker_spec.get('checker', 'standard')
            checker_opts = select_options(form, 'problem-data-checker')
            data['problem-data-checker'] = resolve_strict(
                checker_opts, *CHECKER_LABELS[mode], field='problem-data-checker (mode=%s, problem=%s)' % (mode, code))

            if mode == 'bridged':
                ctype = checker_spec.get('checker_type', 'testlib')
                ctype_opts = select_options(form, 'problem-data-checker_type')
                data['problem-data-checker_type'] = resolve_strict(
                    ctype_opts, *CHECKER_TYPE_LABELS[ctype],
                    field='problem-data-checker_type (type=%s, problem=%s)' % (ctype, code))
                fname = checker_spec.get('checker_file', 'checker.cpp')
                if not pdir:
                    raise RuntimeError('bridged checker for %s needs pdir to locate %s' % (code, fname))
                checker_file_path = os.path.join(pdir, fname)
                if not os.path.exists(checker_file_path):
                    raise RuntimeError('checker file not found for %s: %s' % (code, checker_file_path))
                # CONFIRMED BY A REAL FAILED SUBMISSION (Necessary Cities / cses_2077):
                # picking 'checker_type' on the form is NOT enough on its own - the
                # judge-server's bridged checker crashes at grading time with
                #   TypeError: check() missing 1 required positional argument: 'files'
                # (judge/graders/standard.py -> checker(...)) unless checker_args
                # ITSELF also carries 'files' (docs.dmoj.ca: files/type/lang/... are
                # all read from checker_args, not from the uploaded file's name alone).
                # 'type' wasn't flagged as missing in that traceback, but we set it
                # explicitly too rather than rely on an unconfirmed auto-merge from
                # the checker_type dropdown - cheap insurance against the same class
                # of bug. Anything the manifest put under "checker_args" is layered
                # on top (e.g. for a checker that also wants custom time_limit/flags).
                bridged_args = {'files': fname, 'type': ctype}
                bridged_args.update(checker_spec.get('checker_args') or {})
                data['problem-data-checker_args'] = json.dumps(bridged_args, ensure_ascii=False)
            else:
                args = checker_spec.get('checker_args')
                if args is not None:
                    data['problem-data-checker_args'] = json.dumps(args, ensure_ascii=False)

        # Cases formset. On a fresh problem INITIAL_FORMS=0. On --overwrite,
        # the page already contains the old testcases as initial forms. If we post
        # INITIAL_FORMS=0 unconditionally, Django adds the new cases without
        # deleting the old ones, so init.yml is generated from duplicated cases.
        # Preserve existing initial rows and mark them DELETE, then append the new
        # cases after them. Deleted rows keep their original fields so the formset
        # can validate them before deletion.
        old_initial = int(defaults.get('cases-INITIAL_FORMS', '0') or '0')
        n = len(cases)
        data['cases-TOTAL_FORMS'] = str(old_initial + n)
        data['cases-INITIAL_FORMS'] = str(old_initial)
        data['cases-MIN_NUM_FORMS'] = defaults.get('cases-MIN_NUM_FORMS', '0') or '0'
        data['cases-MAX_NUM_FORMS'] = defaults.get('cases-MAX_NUM_FORMS', '10000') or '10000'

        for i in range(old_initial):
            p = 'cases-%d-' % i
            for k, v in defaults.items():
                if k.startswith(p):
                    data[k] = v
            data[p + 'DELETE'] = 'on'

        for j, (order, in_name, out_name) in enumerate(cases):
            i = old_initial + j
            p = 'cases-%d-' % i
            data[p + 'id'] = ''
            data[p + 'order'] = str(order)
            data[p + 'type'] = 'C'
            data[p + 'input_file'] = in_name
            data[p + 'output_file'] = out_name
            data[p + 'points'] = '1'
            data[p + 'checker'] = ''
            data[p + 'checker_args'] = ''
            data[p + 'generator_args'] = ''
            # is_pretest / public / DELETE: unchecked => omit entirely

        with open(zip_path, 'rb') as zf:
            files = {'problem-data-zipfile': (os.path.basename(zip_path), zf, 'application/zip')}
            if checker_file_path:
                with open(checker_file_path, 'rb') as cf:
                    files['problem-data-custom_checker'] = (os.path.basename(checker_file_path), cf, 'text/x-c++src')
                    resp = self.s.post(self.url(path), data=data, files=files,
                                       headers={'Referer': self.url(path)},
                                       allow_redirects=False, timeout=600)
            else:
                resp = self.s.post(self.url(path), data=data, files=files,
                                   headers={'Referer': self.url(path)},
                                   allow_redirects=False, timeout=600)
        if resp.status_code in (301, 302):
            return True
        if self.debug:
            self._diagnose('test_data_post', resp, BeautifulSoup(resp.text, _PARSER))
        raise RuntimeError('test_data failed: %s' % show_errors(resp.text))

    # -- diagnostic: dump every checker/grader-related field on the live form  #
    def inspect_fields(self, code):
        """GET /problem/<code>/test_data and print every field whose name looks
        checker/grader/io-related, with (for selects) every visible label and
        its real option value. Use this once against any existing problem to
        confirm exact field names before wiring up new behaviour (e.g. the
        'grader'/'custom_grader'/'custom_header' fields needed for interactive
        problems, which this script does not yet touch)."""
        path = '/problem/%s/test_data' % code
        r, soup = self._get_soup(path)
        form = form_containing(soup, 'problem-data-zipfile') or soup.find('form')
        if form is None:
            if self.debug:
                self._diagnose('test_data', r, soup)
            raise RuntimeError('could not open the test_data form for %s' % code)
        print('Fields on %s matching /check|grad|io_method|custom/i :' % path)
        for el in form.find_all(['input', 'select', 'textarea']):
            name = el.get('name') or ''
            if not re.search(r'check|grad|io_method|custom', name, re.I):
                continue
            if el.name == 'select':
                opts = [(o.get_text(strip=True), o.get('value', '')) for o in el.find_all('option')]
                print('  SELECT   %-38s %s' % (name, opts))
            else:
                itype = el.get('type') or el.name
                print('  %-8s %-38s type=%-8s value=%r' % (el.name.upper(), name, itype, el.get('value', '')))



    # -- images: upload hash files and rewrite references -------------------- #
    def _ensure_csrf(self):
        token = self.s.cookies.get('csrftoken')
        if not token:
            self.s.get(self.url('/'), timeout=60)
            token = self.s.cookies.get('csrftoken', '')
        return token

    def upload_image(self, file_path):
        """Upload one image via Martor's uploader; return its media URL."""
        token = self._ensure_csrf()
        ext, mime = detect_image(file_path)
        with open(file_path, 'rb') as f:
            files = {'markdown-image-upload':
                     (os.path.basename(file_path) + '.' + ext, f, mime)}
            resp = self.s.post(self.url('/widgets/martor/upload-image'),
                               files=files,
                               data={'csrfmiddlewaretoken': token},
                               headers={'Referer': self.url('/'),
                                        'X-Requested-With': 'XMLHttpRequest',
                                        'X-CSRFToken': token},
                               timeout=180)
        try:
            j = resp.json()
        except Exception:
            raise RuntimeError('image upload returned non-JSON (status %s): %s'
                               % (resp.status_code, resp.text[:160].replace('\n', ' ')))
        link = j.get('link') or j.get('url')
        if not link or not (str(link).startswith('/') or str(link).startswith('http://') or str(link).startswith('https://')):
            raise RuntimeError('image upload failed or returned a non-URL link: %s' % str(j)[:200])
        return link

    def process_images(self, body, pdir, cache):
        """Replace ![alt](<hash>) with a centered <img> pointing at the uploaded
        media URL. Each hash is uploaded once per run (cached)."""
        def repl(m):
            alt, h = m.group(1), m.group(2)
            fp = os.path.join(pdir, h)
            if not os.path.exists(fp):
                return m.group(0)               # not a local hash image; leave as-is
            if h not in cache:
                cache[h] = self.upload_image(fp)
            return '<center><img src="%s" alt="%s"></center>' % (cache[h], alt)
        return IMG_RE.sub(repl, body)

    # -- update an existing problem's statement/limits via the edit form ----- #
    def update_problem(self, code, body, tl, mem_kb, points, partial, testcase_visibility,
                       group_label, type_label, default_type_label):
        path = '/problem/%s/edit' % code
        r, soup = self._get_soup(path)
        form = form_containing(soup, 'code')
        if form is None:
            if self.debug:
                self._diagnose('edit', r, soup)
            raise RuntimeError('could not open the edit form (not editable?)')
        # Use list-style serialization to preserve multi-value fields such as
        # `types`; a dict would silently keep only one selected value.
        payload = form_payload_multi(form)
        items_set(payload, 'csrfmiddlewaretoken', self._csrf(soup))
        items_del(payload, 'statement_file')
        items_del(payload, 'testers')
        items_set(payload, 'description', body)
        items_set(payload, 'time_limit', ('%g' % tl))
        items_set(payload, 'memory_limit', str(mem_kb))
        items_set(payload, 'points', ('%g' % points))
        items_set(payload, 'testcase_visibility_mode', testcase_visibility)
        # Keep overwrite semantics aligned with create_problem: CSES is binary by
        # default, so unchecked partial must be omitted from the POST.
        items_del(payload, 'partial')
        if partial:
            items_set(payload, 'partial', 'on')
        # Old problems may have no group/type set, which the edit form would
        # otherwise resubmit empty ("" is not a valid value). Re-resolve them.
        groups = select_options(form, 'group')
        types = select_options(form, 'types')
        gpk = resolve_option(groups, group_label)
        tpk = resolve_option(types, type_label, default_type_label)
        if gpk:
            items_set(payload, 'group', gpk)
        if tpk:
            items_set(payload, 'types', tpk)
        if not items_get(payload, 'submission_source_visibility_mode'):
            items_set(payload, 'submission_source_visibility_mode', 'F')
        resp = self.s.post(self.url(path), data=payload,
                           headers={'Referer': self.url(path)},
                           allow_redirects=False, timeout=120)
        if resp.status_code in (301, 302):
            return True
        raise RuntimeError('update failed: %s' % show_errors(resp.text))

    # -- step 3b: editorial (Solution) via the front-end edit page ----------- #
    def add_editorial(self, code, content, publish_date, is_public):
        """Attach an editorial by re-submitting the problem edit form with one
        solution-formset row filled in. The edit page (/problem/<code>/edit)
        renders the main form + a Solution formset in a single <form>, so we
        GET it, keep every existing value, inject the editorial row, and POST."""
        path = '/problem/%s/edit' % code
        r, soup = self._get_soup(path)
        form = form_containing(soup, 'code')
        if form is None:
            if self.debug:
                self._diagnose('edit', r, soup)
            raise RuntimeError('could not open the edit form (not editable?)')

        # Preserve multi-value fields and both management forms
        # (language-limit + solution formsets) while injecting the editorial.
        payload = form_payload_multi(form)
        items_set(payload, 'csrfmiddlewaretoken', self._csrf(soup))
        items_del(payload, 'statement_file')
        items_del(payload, 'testers')

        # locate the Solution formset prefix (the one that has a "...-content" field)
        prefix = None
        for el in form.find_all(['textarea', 'input', 'select']):
            m = re.match(r'(.+)-\d+-content$', el.get('name', ''))
            if m:
                prefix = m.group(1)
                break
        if prefix is None:
            prefix = 'solution'   # Django's default accessor name for this O2O inline

        total = int(items_get(payload, '%s-TOTAL_FORMS' % prefix) or '0')
        if total < 1:
            items_set(payload, '%s-TOTAL_FORMS' % prefix, '1')
        base = '%s-0-' % prefix
        items_set(payload, base + 'content', content)
        items_set(payload, base + 'publish_on', publish_date)          # <input type=date> -> YYYY-MM-DD
        if items_get(payload, base + 'id') is None:
            items_set(payload, base + 'id', '')
        items_del(payload, base + 'authors')                  # optional, leave empty
        items_del(payload, base + 'is_public')
        if is_public:
            items_set(payload, base + 'is_public', 'on')

        resp = self.s.post(self.url(path), data=payload,
                           headers={'Referer': self.url(path)},
                           allow_redirects=False, timeout=120)
        if resp.status_code in (301, 302):
            return True
        if self.debug:
            self._diagnose('edit_post', resp, BeautifulSoup(resp.text, _PARSER))
        raise RuntimeError('add editorial failed: %s' % show_errors(resp.text))

    # -- step 3c: a translation (ProblemTranslation) via the admin form ------ #
    def admin_problem_pk(self, code):
        r, soup = self._get_soup('/admin/judge/problem/?q=%s' % quote(code))
        best = None
        for a in soup.find_all('a', href=re.compile(r'/admin/judge/problem/(\d+)/change/')):
            m = re.search(r'/problem/(\d+)/change/', a['href'])
            if not m:
                continue
            best = best or m.group(1)
            if a.get_text(strip=True) == code:        # exact code match wins
                return m.group(1)
        return best

    def add_translation(self, code, language, name, description):
        """Add (or update) a ProblemTranslation. This goes through the admin
        change form because translations are an admin-only inline. We GET the
        full form, keep every field exactly (incl. multi-value M2M like
        allowed_languages), inject one translation row, and POST it back."""
        pk = self.admin_problem_pk(code)
        if not pk:
            raise RuntimeError('could not find admin pk for %s' % code)
        path = '/admin/judge/problem/%s/change/' % pk
        r, soup = self._get_soup(path)
        form = form_containing(soup, 'code')
        if form is None:
            if self.debug:
                self._diagnose('admin_change', r, soup)
            raise RuntimeError('could not open admin change form for %s' % code)

        items = form_payload_multi(form)
        items_set(items, 'csrfmiddlewaretoken', self._csrf(soup))
        # drop file inputs we must not resend
        items[:] = [(k, v) for (k, v) in items if not k.endswith('-pdf_url') or v]

        # find the translation inline prefix (the one with a "...-language" field)
        prefix = None
        for el in form.find_all(['select', 'input', 'textarea']):
            m = re.match(r'(.+)-\d+-language$', el.get('name', ''))
            if m:
                prefix = m.group(1)
                break
        if prefix is None:
            prefix = 'translations'     # Django accessor name (related_name='translations')

        # is there already a row for this language? -> update it (idempotent)
        existing_idx = None
        for k, v in items:
            m = re.match(re.escape(prefix) + r'-(\d+)-language$', k)
            if m and v == language:
                existing_idx = int(m.group(1))
                break

        if existing_idx is not None:
            base = '%s-%d-' % (prefix, existing_idx)
            items_set(items, base + 'name', name)
            items_set(items, base + 'description', description)
            items_set(items, base + 'language', language)
        else:
            total = int(items_get(items, '%s-TOTAL_FORMS' % prefix) or '0')
            idx = total
            base = '%s-%d-' % (prefix, idx)
            items.append((base + 'id', ''))
            items.append((base + 'problem', pk))
            items.append((base + 'language', language))
            items.append((base + 'name', name))
            items.append((base + 'description', description))
            items_set(items, '%s-TOTAL_FORMS' % prefix, str(idx + 1))

        items.append(('_continue', ''))   # save and stay (302 on success)

        resp = self.s.post(self.url(path), data=items,
                           headers={'Referer': self.url(path)},
                           allow_redirects=False, timeout=180)
        if resp.status_code in (301, 302):
            return True
        if self.debug:
            self._diagnose('admin_change_post', resp, BeautifulSoup(resp.text, _PARSER))
        raise RuntimeError('add translation failed: %s' % show_errors(resp.text))

    # -- step 4: bulk publish / unpublish ----------------------------------- #
    PUBLISH_ACTION = 'make_public_and_update_publish_date'
    UNPUBLISH_ACTION = 'make_private'

    def set_public_prefix(self, prefix, make_public=True):
        """Run the publish/unpublish admin action on ALL problems whose code
        matches `prefix` (via the changelist search + select_across)."""
        path = '/admin/judge/problem/?q=%s' % quote(prefix)
        r, soup = self._get_soup(path)
        if soup.find('form', id='changelist-form') is None and form_containing(soup, 'action') is None:
            raise RuntimeError('Could not open admin changelist (is the account staff/superuser?).')
        payload = {
            'csrfmiddlewaretoken': self._csrf(soup),
            'action': self.PUBLISH_ACTION if make_public else self.UNPUBLISH_ACTION,
            'select_across': '1',
            'index': '0',
            '_selected_action': '0',
        }
        resp = self.s.post(self.url(path), data=payload,
                           headers={'Referer': self.url(path)},
                           allow_redirects=False, timeout=120)
        return resp.status_code in (200, 301, 302)

    def set_public_codes(self, codes, make_public=True):
        """Publish/unpublish a SPECIFIC subset of problems (by code)."""
        pks = []
        for code in codes:
            pk = self.admin_problem_pk(code)
            if pk:
                pks.append(pk)
        if not pks:
            raise RuntimeError('none of the given codes were found in /admin')
        path = '/admin/judge/problem/'
        r, soup = self._get_soup(path)
        payload = [
            ('csrfmiddlewaretoken', self._csrf(soup)),
            ('action', self.PUBLISH_ACTION if make_public else self.UNPUBLISH_ACTION),
            ('select_across', '0'),
            ('index', '0'),
        ]
        for pk in pks:
            payload.append(('_selected_action', pk))
        resp = self.s.post(self.url(path), data=payload,
                           headers={'Referer': self.url(path)},
                           allow_redirects=False, timeout=120)
        return resp.status_code in (200, 301, 302), len(pks)

    # backward-compatible alias used by the end-of-run auto-publish
    def publish_prefix(self, prefix):
        return self.set_public_prefix(prefix, make_public=True)


# --------------------------------------------------------------------------- #
def iter_problems(root, lang, only):
    for category in sorted(os.listdir(root)):
        cat_dir = os.path.join(root, category)
        if not os.path.isdir(cat_dir) or category.startswith('.'):
            continue
        for folder in sorted(os.listdir(cat_dir)):
            pdir = os.path.join(cat_dir, folder)
            m = FOLDER_RE.match(folder)
            if not os.path.isdir(pdir) or not m:
                continue
            pid, name = m.group(1), m.group(2)
            if only and pid not in only:
                continue
            st = None
            for lg in (lang, 'en'):
                cand = os.path.join(pdir, 'statement_%s.md' % lg)
                if os.path.exists(cand):
                    st = cand
                    break
            zips = [f for f in os.listdir(pdir) if re.match(r'tests_.*\.zip$', f, re.I)]
            yield pid, name, category, pdir, st, (os.path.join(pdir, zips[0]) if zips else None)


def main():
    ap = argparse.ArgumentParser(description='Upload CSES problems to a DMOJ/VNOJ site over HTTP.')
    ap.add_argument('--root', required=True, help='Path to the CSES-Problems-set repo.')
    ap.add_argument('--site', default='https://oj.thptchuyenhatinh.edu.vn', help='Base site URL.')
    ap.add_argument('--user', help='Admin username (required unless --dry-run).')
    ap.add_argument('--password', help='Admin password (prompted if omitted).')
    ap.add_argument('--lang', default='en', help='Statement language to prefer (falls back to en).')
    ap.add_argument('--vi', dest='lang', action='store_const', const='vi',
                    help='Shortcut for --lang vi (prefer statement_vi.md, fall back to en).')
    ap.add_argument('--code-prefix', default='cses_', help='Problem code prefix. Default: cses_.')
    ap.add_argument('--points', type=float, default=1.0, help='Points per problem. Default: 1.0.')
    ap.add_argument('--partial', action='store_true', help='Allow partial scoring (default off).')
    ap.add_argument('--group', default='CSES', help='Existing problem group name to use. Default: CSES.')
    ap.add_argument('--type-from-category', action='store_true', default=True,
                    help='Match the CSES category name to an existing problem type (default on).')
    ap.add_argument('--default-type', default='Chưa phân loại',
                    help='Fallback problem-type name if the category has no matching type.')
    ap.add_argument('--testcase-visibility', choices=['visible', 'out-contest', 'authors'],
                    default='visible',
                    help='Testcase visibility. Default: visible ("Co the xem" / always visible).')
    ap.add_argument('--no-publish', action='store_true', help='Do NOT bulk-publish after import.')
    ap.add_argument('--publish-only', action='store_true',
                    help='Do nothing but PUBLISH (make public) the cses_* problems, then exit. '
                         'Use --only to target a specific subset.')
    ap.add_argument('--unpublish-only', action='store_true',
                    help='Do nothing but UNPUBLISH (make private) the cses_* problems, then exit. '
                         'Use --only to target a specific subset.')
    ap.add_argument('--overwrite', action='store_true', help='Re-upload data for problems that already exist.')
    ap.add_argument('--with-editorial', action='store_true',
                    help='Also upload analysis_<lang>.md as the problem editorial (Solution).')
    ap.add_argument('--editorial-public', action='store_true',
                    help='Make the uploaded editorial publicly visible (default: hidden).')
    ap.add_argument('--bilingual', action='store_true',
                    help='Also add the other language as a ProblemTranslation (via admin). '
                         'Primary language (--lang) goes in the main description; the other '
                         'language is added as a translation, e.g. --vi --bilingual keeps vi '
                         'as the main text and adds the English statement as an "en" translation.')
    ap.add_argument('--only', nargs='*', help='Only these CSES IDs (e.g. --only 1068 1083).')
    ap.add_argument('--checker-manifest', default=None,
                    help='Path to CHECKER_MANIFEST.json (default: <root>/CHECKER_MANIFEST.json if present). '
                         'Problems not listed in it keep the standard token-compare checker, unchanged.')
    ap.add_argument('--inspect-fields', metavar='CODE',
                    help='Diagnostic: log in, open /problem/CODE/test_data, print every checker/grader/io '
                         'field name and (for selects) every label->value option, then exit. Use this '
                         'against any existing problem code to confirm real field names before trusting '
                         'new behaviour (e.g. before wiring up interactive-problem support).')
    ap.add_argument('--sleep', type=float, default=0.5, help='Seconds to wait between problems.')
    ap.add_argument('--dry-run', action='store_true', help='Parse locally and report; no network.')
    ap.add_argument('--debug', action='store_true',
                    help='On a "form not found" error, print page status/title and save the HTML.')
    opt = ap.parse_args()

    if not os.path.isdir(opt.root):
        sys.exit('Root not found: %s' % opt.root)
    if not re.match(r'https?://', opt.site):
        sys.exit('--site must be a full URL like https://oj.thptchuyenhatinh.edu.vn '
                 '(you gave: %r). Tip: just omit --site to use the default.' % opt.site)
    only = set(opt.only) if opt.only else None
    manifest = load_checker_manifest(opt.root, opt.checker_manifest)
    if manifest:
        print('Loaded CHECKER_MANIFEST.json: %d problem(s) with a non-standard checker.' % len(manifest))

    # ---- diagnostic mode: dump checker/grader field names, then exit ----
    if opt.inspect_fields:
        if not opt.user:
            sys.exit('--user is required for --inspect-fields.')
        password = opt.password or getpass.getpass('Admin password for %s: ' % opt.user)
        up = Uploader(opt.site, debug=opt.debug)
        up.login(opt.user, password)
        target = opt.inspect_fields
        if not target.startswith(opt.code_prefix):
            target = opt.code_prefix + target
        up.inspect_fields(target)
        return

    # ---- dry run: just validate local files ----
    if opt.dry_run:
        ok = bad = 0
        for pid, name, cat, pdir, st, zp in iter_problems(opt.root, opt.lang, only):
            if not st or not zp:
                print('  [%s] %-40s MISSING %s' % (pid, name[:40], 'statement' if not st else 'zip'))
                bad += 1
                continue
            tl, mem, body = parse_statement(
                open(st, encoding='utf-8').read(),
                limits_text=open(os.path.join(pdir, 'statement_en.md'), encoding='utf-8').read()
                if os.path.exists(os.path.join(pdir, 'statement_en.md')) else None)
            try:
                cases, _ = read_cases(zp)
            except zipfile.BadZipFile:
                print('  [%s] %-40s CORRUPT ZIP (skip)' % (pid, name[:40]))
                bad += 1
                continue
            spec = manifest.get(pid)
            ckr = ''
            if spec:
                ckr = '  <checker=%s%s>' % (spec['checker'],
                                            ':' + spec['checker_type'] if spec.get('checker_type') else '')
            print('  [%s] %-40s %4.2fs %6dKB  %3d cases  [%s]%s'
                  % (pid, name[:40], tl or 0, mem or 0, len(cases), cat, ckr))
            ok += 1
        print('\nDry run: %d ok, %d problem(s) to skip.' % (ok, bad))
        return

    # ---- real run ----
    if not opt.user:
        sys.exit('--user is required for a real run.')
    password = opt.password or getpass.getpass('Admin password for %s: ' % opt.user)

    up = Uploader(opt.site, debug=opt.debug)
    print('Logging in as %s ...' % opt.user)
    up.login(opt.user, password)
    print('  OK\n')

    # ---- publish/unpublish-only modes: just flip visibility, then exit ----
    if opt.publish_only or opt.unpublish_only:
        make_public = opt.publish_only
        verb = 'Publishing' if make_public else 'Unpublishing'
        try:
            if only:
                codes = [opt.code_prefix + i for i in sorted(only)]
                print('%s %d specific problem(s) ...' % (verb, len(codes)))
                ok, n = up.set_public_codes(codes, make_public)
                print('  %s (%d problems).' % ('done' if ok else 'FAILED', n))
            else:
                print('%s all %s* problems ...' % (verb, opt.code_prefix))
                ok = up.set_public_prefix(opt.code_prefix, make_public)
                print('  %s.' % ('done' if ok else 'FAILED'))
        except Exception as e:
            print('  FAILED: %s' % e)
        return

    found = created = skipped = failed = 0
    img_cache = {}
    for pid, name, cat, pdir, st, zp in iter_problems(opt.root, opt.lang, only):
        found += 1
        code = opt.code_prefix + pid
        if not st or not zp:
            print('[%s] %s -> SKIP (missing statement/zip)' % (pid, name))
            skipped += 1
            continue
        try:
            en_st = os.path.join(pdir, 'statement_en.md')
            en_text = open(en_st, encoding='utf-8').read() if os.path.exists(en_st) else None
            tl, mem, body = parse_statement(open(st, encoding='utf-8').read(), limits_text=en_text)
            tl = tl or 1.0
            mem = mem or 256 * 1024
            cases, _ = read_cases(zp)
            if not cases:
                raise RuntimeError('no test cases found in zip')

            exists = up.problem_exists(code)
            # Clean resume: a problem that already exists is skipped entirely
            # (no re-create, no re-upload, no re-touch). Use --overwrite to
            # refresh its statement/limits/test data/editorial.
            if exists and not opt.overwrite:
                print('[%s] %s -> exists, skip (use --overwrite to refresh)' % (pid, name))
                skipped += 1
                continue

            body = up.process_images(body, pdir, img_cache)   # upload images, center them
            source = 'CSES'
            if not exists:
                up.create_problem(code, name, body, tl, mem, opt.points, opt.partial,
                                  source, opt.group,
                                  cat if opt.type_from_category else opt.default_type,
                                  opt.default_type,
                                  TESTCASE_VIS[opt.testcase_visibility])
                print('[%s] %s -> created %s' % (pid, name, code))
            elif opt.overwrite:
                up.update_problem(code, body, tl, mem, opt.points, opt.partial,
                                  TESTCASE_VIS[opt.testcase_visibility],
                                  opt.group,
                                  cat if opt.type_from_category else opt.default_type,
                                  opt.default_type)
                print('[%s] %s -> updated statement/limits' % (pid, name))

            if not exists or opt.overwrite:
                checker_spec = manifest.get(pid)
                up.upload_data(code, zp, cases, checker_spec=checker_spec, pdir=pdir)
                extra = ' [checker=%s]' % checker_spec['checker'] if checker_spec else ''
                print('       uploaded %d test cases (%.2fs, %dKB)%s' % (len(cases), tl, mem, extra))

            if opt.with_editorial:
                an = None
                for lg in (opt.lang, 'en'):
                    cand = os.path.join(pdir, 'analysis_%s.md' % lg)
                    if os.path.exists(cand):
                        an = cand
                        break
                if an:
                    content = convert_math(open(an, encoding='utf-8').read())
                    content = up.process_images(content, pdir, img_cache)
                    up.add_editorial(code, content,
                                     datetime.date.today().isoformat(),
                                     opt.editorial_public)
                    print('       editorial added (%s, %s)'
                          % (os.path.basename(an),
                             'public' if opt.editorial_public else 'hidden'))
                else:
                    print('       no analysis_*.md found, skipping editorial')

            if opt.bilingual:
                secondary = 'en' if opt.lang != 'en' else 'vi'
                spath = os.path.join(pdir, 'statement_%s.md' % secondary)
                if os.path.exists(spath):
                    _, _, sbody = parse_statement(open(spath, encoding='utf-8').read(),
                                                  limits_text=en_text)
                    sbody = up.process_images(sbody, pdir, img_cache)
                    up.add_translation(code, secondary, name, sbody)
                    print('       %s translation added' % secondary)
                else:
                    print('       no statement_%s.md, skipping translation' % secondary)

            created += 1
        except Exception as e:
            failed += 1
            tbs = traceback.extract_tb(e.__traceback__)
            loc = ''
            if tbs:
                last = tbs[-1]
                loc = ' [%s:%d]' % (os.path.basename(last.filename), last.lineno)
            print('[%s] %s -> FAILED: %s%s' % (pid, name, e, loc))
            if failed == 1 or opt.debug:          # show full traceback for the first failure
                traceback.print_exc()
        time.sleep(opt.sleep)

    if not opt.no_publish and created:
        print('\nPublishing all %s* problems ...' % opt.code_prefix)
        try:
            up.publish_prefix(opt.code_prefix)
            print('  publish action sent.')
        except Exception as e:
            print('  publish failed: %s (you can do it manually in /admin)' % e)

    print('\nDone. found=%d uploaded=%d skipped=%d failed=%d' % (found, created, skipped, failed))


if __name__ == '__main__':
    main()