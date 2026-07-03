#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
contest_tool.py — tạo & quản lý CONTEST trên CHT-oj (VNOJ/DMOJ fork) qua HTTP,
cùng triết lý với upload.py: không SSH, không manage.py, chỉ cần tài khoản
admin; mọi field/option đều được resolve từ FORM THẬT trên trang chứ không
hardcode, nên fork đổi nhãn/không khớp là tool báo lỗi to thay vì đoán bừa.

Contest trong DMOJ/VNOJ không có form front-end như problem — nó đi qua
Django admin: /admin/judge/contest/add/ (tạo) và
/admin/judge/contest/<pk>/change/ (sửa). Danh sách bài của contest là một
INLINE FORMSET (ContestProblem) ngay trong form đó. Tool này:

  * GET form -> giữ nguyên MỌI giá trị mặc định (kể cả M2M multi-select),
  * phát hiện động: prefix của formset bài (quét *-__prefix__-problem),
    widget datetime tách đôi (start_time_0/_1) hay gộp (start_time),
  * điền key/name/thời gian/bài, rồi POST; thành công = HTTP 302.

⚠️  TRƯỚC LẦN CHẠY THẬT ĐẦU TIÊN: chạy
        python contest_tool.py inspect --user ntannn
    để in toàn bộ field thật của form add trên CHT-oj. Field bên dưới được
    suy từ mã nguồn VNOJ upstream; fork CÓ THỂ khác — inspect trước, giống
    hệt cách upload.py có --inspect-fields cho checker/grader. Sau đó chạy
    `create --dry-run` để xem payload trước khi POST thật.

VÍ DỤ
    # 1. soi form (bắt buộc lần đầu)
    python contest_tool.py inspect --user ntannn

    # 2. tạo contest 3 tiếng với 5 bài CSES, xem payload trước:
    python contest_tool.py create --user ntannn \
        --key luyentap01 --name "Luyện tập tuần 1" \
        --start "2026-07-10 19:00" --end "2026-07-10 22:00" \
        --problems 1068 1083 1640 2077 1625 --points-each 100 --dry-run
    # ưng rồi thì bỏ --dry-run; thêm --visible nếu muốn public luôn

    # 3. thêm bài vào contest đã có
    python contest_tool.py add-problems --user ntannn --key luyentap01 \
        --problems 1697 2423 --points-each 100

    # 4. bật/tắt hiển thị
    python contest_tool.py set-visible --user ntannn --key luyentap01
    python contest_tool.py set-hidden  --user ntannn --key luyentap01

    # 5. bật rating cho contest
    python contest_tool.py set-rated --user ntannn --key luyentap01 --rate-all
    python contest_tool.py set-unrated --user ntannn --key luyentap01

GHI CHÚ
  * --problems nhận CSES id trần (1068 -> cses_1068 theo --code-prefix) hoặc
    code đầy đủ (vd. abc_xyz) — cái nào có sẵn trên OJ thì dùng.
  * Bài phải tồn tại trên OJ trước (upload.py lo phần đó).
  * Trường `authors` được tự điền bằng profile của chính --user (form admin
    thường bắt buộc >= 1 author).
  * Format contest được set tường minh bằng --format. Rating có thể bật
    ngay khi tạo bằng --rated/--rate-all, hoặc bật/tắt sau bằng set-rated /
    set-unrated. Các field khác vẫn giữ nguyên default của form admin.
"""
import argparse
import getpass
import json
import re
import sys
from urllib.parse import quote

try:
    import requests
    from bs4 import BeautifulSoup
except ImportError:
    sys.exit('Missing deps. Run:  pip install requests beautifulsoup4 lxml')

try:
    import lxml  # noqa: F401
    _PARSER = 'lxml'
except Exception:
    _PARSER = 'html.parser'

DEFAULT_SITE = 'https://oj.thptchuyenhatinh.edu.vn'


# --------------------------------------------------------------------------- #
# form helpers (giữ nguyên semantics form HTML: checkbox bỏ chọn => không gửi)
# --------------------------------------------------------------------------- #

def serialize_form(form):
    """-> list[(name, value)] đúng như trình duyệt sẽ submit, giữ multi-value."""
    items = []
    for el in form.find_all(['input', 'textarea', 'select']):
        name = el.get('name')
        if not name:
            continue
        if el.name == 'textarea':
            items.append((name, el.get_text()))
        elif el.name == 'select':
            multiple = el.has_attr('multiple')
            picked = False
            for o in el.find_all('option'):
                if o.has_attr('selected'):
                    items.append((name, o.get('value', '')))
                    picked = True
                    if not multiple:
                        break
            if not picked and not multiple:
                o = el.find('option')
                if o is not None:
                    items.append((name, o.get('value', '')))
        else:
            t = (el.get('type') or 'text').lower()
            if t in ('checkbox', 'radio'):
                if el.has_attr('checked'):
                    items.append((name, el.get('value', 'on')))
            elif t in ('file', 'submit', 'button', 'image', 'reset'):
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
    """Set a single-value field exactly once.

    Django forms sometimes render helper/initial controls around widgets. For
    fields we actively control (csrf, key, dates, format_name, inline row fields)
    keeping an older duplicate value is more dangerous than preserving order, so
    replace every existing pair for that key with one final value. Multi-value
    fields that must be preserved are left untouched by this helper.
    """
    items[:] = [(k, v) for (k, v) in items if k != key]
    items.append((key, value))


def items_has(items, key):
    return any(k == key for k, _ in items)


def items_del(items, key):
    items[:] = [(k, v) for (k, v) in items if k != key]


def detect_inline_prefix(form, row_field='problem'):
    """Tìm prefix của formset ContestProblem: quét name khớp
    <prefix>-(<số>|__prefix__)-<row_field>. Django admin luôn render một
    "empty form" template với __prefix__ nên add-form trống vẫn dò được."""
    rx = re.compile(r'^(.+)-(?:\d+|__prefix__)-%s$' % re.escape(row_field))
    for el in form.find_all(['input', 'select', 'textarea']):
        m = rx.match(el.get('name') or '')
        if m:
            return m.group(1)
    return None


def inline_row_template(form, prefix):
    """Lấy mọi field mặc định của 1 row inline từ empty-form (__prefix__),
    -> dict suffix -> default value (checkbox bỏ chọn thì vắng mặt)."""
    tmpl = {}
    marker = '%s-__prefix__-' % prefix
    for el in form.find_all(['input', 'select', 'textarea']):
        name = el.get('name') or ''
        if not name.startswith(marker):
            continue
        suffix = name[len(marker):]
        if el.name == 'textarea':
            tmpl[suffix] = el.get_text()
        elif el.name == 'select':
            o = el.find('option', selected=True) or el.find('option')
            tmpl[suffix] = o.get('value', '') if o is not None else ''
        else:
            t = (el.get('type') or 'text').lower()
            if t in ('checkbox', 'radio'):
                if el.has_attr('checked'):
                    tmpl[suffix] = el.get('value', 'on')
            elif t not in ('file', 'submit', 'button'):
                tmpl[suffix] = el.get('value', '')
    return tmpl



def normalize_key_suggestion(key):
    """Return a safe-looking contest key suggestion for CHT-OJ.

    CHT-OJ Contest.key is constrained by the model validator to
    ^[a-z0-9_]+$ and max_length=32. Hyphens are NOT accepted.
    """
    sug = key.strip().lower()
    sug = re.sub(r'[^a-z0-9_]+', '_', sug)
    sug = re.sub(r'_+', '_', sug).strip('_')
    return sug[:32]


def validate_contest_key(key):
    if not re.fullmatch(r'[a-z0-9_]+', key or ''):
        sug = normalize_key_suggestion(key or '')
        msg = 'Contest key không hợp lệ: %r. CHT-OJ chỉ cho phép regex ^[a-z0-9_]+$ (chữ thường, số, dấu gạch dưới; KHÔNG dùng dấu gạch ngang).'
        if sug and sug != key:
            msg += ' Gợi ý: --key %s' % sug
        raise SystemExit(msg % key)
    if len(key) > 32:
        raise SystemExit('Contest key quá dài: %d ký tự; CHT-OJ Contest.key max_length=32. Gợi ý: --key %s' % (len(key), key[:32]))

def parse_dt(s):
    """'YYYY-MM-DD HH:MM[:SS]' -> ('YYYY-MM-DD', 'HH:MM:SS')"""
    m = re.match(r'^\s*(\d{4}-\d{2}-\d{2})[ T](\d{2}:\d{2})(?::(\d{2}))?\s*$', s)
    if not m:
        raise SystemExit('Bad datetime %r — dùng dạng "YYYY-MM-DD HH:MM"' % s)
    return m.group(1), '%s:%s' % (m.group(2), m.group(3) or '00')


# --------------------------------------------------------------------------- #

class Client:
    def __init__(self, base, debug=False):
        self.base = base.rstrip('/')
        self.debug = debug
        self.s = requests.Session()
        self.s.headers['User-Agent'] = 'cht-contest-tool/1.0'

    def url(self, p):
        return self.base + p

    def get_soup(self, path):
        r = self.s.get(self.url(path), timeout=60)
        r.raise_for_status()
        return r, BeautifulSoup(r.text, _PARSER)

    def csrf(self, soup):
        el = soup.find('input', attrs={'name': 'csrfmiddlewaretoken'})
        return el.get('value') if el else self.s.cookies.get('csrftoken', '')

    def login(self, username, password):
        path = '/accounts/login/'
        r, soup = self.get_soup(path)
        form = None
        for f in soup.find_all('form'):
            if f.find('input', attrs={'name': 'password'}):
                form = f
                break
        payload = dict(serialize_form(form)) if form else {}
        payload.update(csrfmiddlewaretoken=self.csrf(soup),
                       username=username, password=password)
        payload.setdefault('next', '/')
        resp = self.s.post(self.url(path), data=payload,
                           headers={'Referer': self.url(path)},
                           allow_redirects=False, timeout=60)
        if resp.status_code not in (301, 302):
            raise SystemExit('Login failed (status %s).' % resp.status_code)

    # ---- pk lookups qua admin changelist (giống admin_problem_pk bên upload.py)
    def _admin_pk(self, app_model, query, want_text=None):
        r, soup = self.get_soup('/admin/judge/%s/?q=%s' % (app_model, quote(str(query))))
        best = None
        rx = re.compile(r'/admin/judge/%s/(\d+)/change/' % re.escape(app_model))
        for a in soup.find_all('a', href=rx):
            m = rx.search(a['href'])
            if not m:
                continue
            best = best or m.group(1)
            if want_text and a.get_text(strip=True) == want_text:
                return m.group(1)
        return best

    def problem_pk(self, code):
        pk = self._admin_pk('problem', code, want_text=code)
        if not pk:
            raise SystemExit('Không tìm thấy bài %r trên /admin (đã upload chưa?)' % code)
        return pk

    def contest_pk(self, key):
        pk = self._admin_pk('contest', key, want_text=key)
        if not pk:
            raise SystemExit('Không tìm thấy contest key=%r trên /admin' % key)
        return pk

    def profile_pk(self, username):
        pk = self._admin_pk('profile', username, want_text=username)
        return pk  # có thể None -> caller tự xử

    # ---- form pages
    def open_admin_form(self, path):
        r, soup = self.get_soup(path)
        form = None
        for f in soup.find_all('form'):
            if f.find(attrs={'name': 'key'}) is not None or f.find(attrs={'name': re.compile(r'-TOTAL_FORMS$')}):
                form = f
                break
        form = form or soup.find('form', id=re.compile('contest', re.I)) or soup.find('form')
        if form is None or form.find(attrs={'name': 'key'}) is None:
            if self.debug:
                open('debug_contest_form.html', 'w', encoding='utf-8').write(r.text)
                print('  (đã lưu debug_contest_form.html)')
            raise SystemExit('Không mở được form contest tại %s — tài khoản có phải staff/superuser? '
                             'Chạy subcommand `inspect` để xem trang.' % path)
        return soup, form

    def post_admin_form(self, path, items):
        items = list(items) + [('_save', 'Save')]
        resp = self.s.post(self.url(path), data=items,
                           headers={'Referer': self.url(path)},
                           allow_redirects=False, timeout=120)
        if resp.status_code in (301, 302):
            return True
        # in lỗi validation của Django admin cho dễ sửa
        soup = BeautifulSoup(resp.text, _PARSER)
        errs = []
        for e in soup.select('.errornote'):
            txt = e.get_text(' ', strip=True)
            if txt:
                errs.append(txt)
        for e in soup.select('.form-row, .field-box, tr.form-row, .inline-related'):
            err = e.select_one('.errorlist')
            if not err:
                continue
            names = sorted({ctrl.get('name') for ctrl in e.find_all(['input', 'select', 'textarea']) if ctrl.get('name')})
            label = ','.join(names[:3]) or e.get('class') or 'field'
            errs.append('%s: %s' % (label, err.get_text(' ', strip=True)))
        if not errs:
            errs = [e.get_text(' ', strip=True) for e in soup.select('.errorlist, .errornote')]
        if self.debug:
            open('debug_contest_post.html', 'w', encoding='utf-8').write(resp.text)
            print('  (đã lưu debug_contest_post.html)')
        raise SystemExit('POST thất bại (status %s): %s'
                         % (resp.status_code, ' | '.join(errs[:8]) or '(không thấy errorlist — chạy với --debug)'))


# --------------------------------------------------------------------------- #
# subcommands
# --------------------------------------------------------------------------- #

def cmd_inspect(cli, opt):
    soup, form = cli.open_admin_form('/admin/judge/contest/add/')
    print('Fields trên /admin/judge/contest/add/ :\n')
    seen = set()
    for el in form.find_all(['input', 'select', 'textarea']):
        name = el.get('name')
        if not name or name in seen:
            continue
        seen.add(name)
        if el.name == 'select':
            opts = [(('!' if o.has_attr('selected') else '') + o.get_text(strip=True), o.get('value', ''))
                    for o in el.find_all('option')][:12]
            print('  SELECT%s %-42s %s   (! = selected)' % ('*' if el.has_attr('multiple') else ' ', name, opts))
        else:
            t = el.get('type') or el.name
            print('  %-7s %-42s value=%r%s' % (t.upper(), name, (el.get('value', '') or '')[:40],
                                               ' [checked]' if el.has_attr('checked') else ''))
    prefix = detect_inline_prefix(form)
    print('\nInline formset của ContestProblem: prefix = %r' % prefix)
    if prefix:
        print('Row template (field -> default):')
        for k, v in sorted(inline_row_template(form, prefix).items()):
            print('   %-30s %r' % (k, v))
    split = form.find(attrs={'name': 'start_time_0'}) is not None
    print('\nDatetime widget: %s' % ('TÁCH ĐÔI (start_time_0/_1)' if split else 'gộp (start_time)'))


def resolve_codes(cli, ids, prefix):
    pks = []
    for x in ids:
        code = (prefix + x) if re.fullmatch(r'\d+', x) else x
        pks.append((code, cli.problem_pk(code)))
        print('  bài %-14s -> pk %s' % (code, pks[-1][1]))
    return pks


def fill_datetime(items, form, field, dtstr):
    d, t = parse_dt(dtstr)
    if form.find(attrs={'name': field + '_0'}) is not None:
        items_set(items, field + '_0', d)
        items_set(items, field + '_1', t)
    else:
        items_set(items, field, '%s %s' % (d, t))


def normalize_create_only_fields(items, opt=None):
    """Normalize admin-widget defaults that are not safe to POST as-is.

    On CHT-OJ the add-contest form renders the JSONField textarea
    `format_config` as a lone newline. The browser sends that newline, but
    jsonfield's form parser rejects it because it is not valid JSON. Use
    explicit JSON null by default, matching the model help text: "Leave empty
    to use None".
    """
    if items_get(items, 'format_config') is not None:
        cfg = getattr(opt, 'format_config', None) if opt is not None else None
        if cfg is None:
            cfg = items_get(items, 'format_config')
        cfg = '' if cfg is None else str(cfg).strip()
        if not cfg:
            cfg = 'null'
        try:
            json.loads(cfg)
        except Exception as e:
            raise SystemExit('--format-config phải là JSON hợp lệ: %s' % e)
        items_set(items, 'format_config', cfg)

    # These are plain TextField values; blank widgets from Ace/Martor often
    # serialize as "\n". Normalizing avoids dirty data and avoids triggering
    # Lua validation through a meaningless newline script.
    for key in ('problem_label_script', 'csv_ranking', 'summary'):
        if items_get(items, key) is not None and not str(items_get(items, key)).strip():
            items_set(items, key, '')


def resolve_select(form, name, wanted):
    """Khớp `wanted` với VALUE hoặc LABEL (không phân biệt hoa thường) của một
    <select> trên form thật; sai thì liệt kê option và dừng — không đoán bừa."""
    el = form.find('select', attrs={'name': name})
    if el is None:
        return None
    opts = [(o.get_text(strip=True), o.get('value', '')) for o in el.find_all('option')]
    w = wanted.strip().lower()
    for label, value in opts:
        if w in (label.strip().lower(), value.strip().lower()):
            return value
    raise SystemExit('%s: không có option khớp %r. Có: %s'
                     % (name, wanted, ', '.join('%s=%r' % (v, l) for l, v in opts)))


def fill_problem_rows(items, form, prefix, pk_pairs, points, start_index, partial=False):
    tmpl = inline_row_template(form, prefix)
    for i, (code, pk) in enumerate(pk_pairs):
        idx = start_index + i
        base = '%s-%d-' % (prefix, idx)
        for suffix, default in tmpl.items():
            if items_get(items, base + suffix) is None:
                items.append((base + suffix, default))
        items_set(items, base + 'problem', pk)
        items_set(items, base + 'points', str(points))
        items_set(items, base + 'order', str(idx + 1))
        items_set(items, base + 'id', items_get(items, base + 'id') or '')
        # Form thật render partial=CHECKED mặc định; CSES chấm nhị phân nên tắt
        # trừ khi --partial. (Checkbox tắt = KHÔNG gửi field, đúng chuẩn HTML.)
        items_del(items, base + 'partial')
        if partial:
            items_set(items, base + 'partial', 'on')
    # Form add render sẵn 3 row trống (TOTAL_FORMS=3). Không được thu nhỏ con
    # số này khi thêm ít bài hơn — chỉ tăng khi cần; row trống thừa không đổi
    # giá trị sẽ được Django formset bỏ qua.
    current = int(items_get(items, '%s-TOTAL_FORMS' % prefix) or '0')
    items_set(items, '%s-TOTAL_FORMS' % prefix, str(max(current, start_index + len(pk_pairs))))


def sanity_check_problem_rows(items, prefix, pk_pairs, start_index, partial=False):
    """Cheap offline guard before POSTing Django's inline formset.

    It only checks fields this tool is responsible for; server-side validation
    remains the source of truth. The goal is to catch silent payload bugs such
    as wrong TOTAL_FORMS, missing problem pk, or accidental partial scoring.
    """
    total = int(items_get(items, '%s-TOTAL_FORMS' % prefix) or '0')
    need = start_index + len(pk_pairs)
    if total < need:
        raise SystemExit('%s-TOTAL_FORMS=%s nhưng cần ít nhất %s row' % (prefix, total, need))
    for i, (_, pk) in enumerate(pk_pairs):
        idx = start_index + i
        base = '%s-%d-' % (prefix, idx)
        if items_get(items, base + 'problem') != pk:
            raise SystemExit('payload lỗi: %sproblem != %r' % (base, pk))
        if items_get(items, base + 'points') in (None, ''):
            raise SystemExit('payload lỗi: thiếu %spoints' % base)
        has_partial = items_has(items, base + 'partial')
        if partial and not has_partial:
            raise SystemExit('payload lỗi: --partial nhưng thiếu %spartial' % base)
        if not partial and has_partial:
            raise SystemExit('payload lỗi: CSES binary nhưng vẫn gửi %spartial' % base)


def apply_rating_options(items, form, rated=None, rate_all=None, rating_floor=None, rating_ceiling=None,
                         clear_rating_bounds=False, require_fields=False):
    """Apply CHT-OJ Contest rating fields to an admin form payload.

    Checkbox semantics: checked => include field with value "on"; unchecked =>
    omit field entirely. This preserves unrelated rating M2M fields such as
    rate_exclude because we only touch explicitly requested scalar fields.
    """
    if require_fields and form.find(attrs={'name': 'is_rated'}) is None:
        raise SystemExit('Form không có field is_rated. Tài khoản có thiếu permission judge.contest_rating không?')

    if rated is not None and form.find(attrs={'name': 'is_rated'}) is not None:
        items_del(items, 'is_rated')
        if rated:
            items_set(items, 'is_rated', 'on')

    if rate_all is not None and form.find(attrs={'name': 'rate_all'}) is not None:
        items_del(items, 'rate_all')
        if rate_all:
            items_set(items, 'rate_all', 'on')

    if clear_rating_bounds:
        if form.find(attrs={'name': 'rating_floor'}) is not None:
            items_set(items, 'rating_floor', '')
        if form.find(attrs={'name': 'rating_ceiling'}) is not None:
            items_set(items, 'rating_ceiling', '')
    else:
        if rating_floor is not None:
            if form.find(attrs={'name': 'rating_floor'}) is None:
                raise SystemExit('Form không có field rating_floor.')
            items_set(items, 'rating_floor', str(rating_floor))
        if rating_ceiling is not None:
            if form.find(attrs={'name': 'rating_ceiling'}) is None:
                raise SystemExit('Form không có field rating_ceiling.')
            items_set(items, 'rating_ceiling', str(rating_ceiling))


def print_rating_status(items):
    print('  is_rated -> %s' % ('on' if items_has(items, 'is_rated') else 'off'))
    print('  rate_all -> %s' % ('on' if items_has(items, 'rate_all') else 'off'))
    if items_get(items, 'rating_floor') not in (None, ''):
        print('  rating_floor -> %r' % items_get(items, 'rating_floor'))
    if items_get(items, 'rating_ceiling') not in (None, ''):
        print('  rating_ceiling -> %r' % items_get(items, 'rating_ceiling'))

def cmd_create(cli, opt):
    path = '/admin/judge/contest/add/'
    soup, form = cli.open_admin_form(path)
    items = serialize_form(form)
    items_set(items, 'csrfmiddlewaretoken', cli.csrf(soup))

    items_set(items, 'key', opt.key)
    items_set(items, 'name', opt.name)
    if items_get(items, 'description') is not None or True:
        desc = open(opt.description_file, encoding='utf-8').read() if opt.description_file else (opt.description or opt.name)
        items_set(items, 'description', desc)
    fill_datetime(items, form, 'start_time', opt.start)
    fill_datetime(items, form, 'end_time', opt.end)
    normalize_create_only_fields(items, opt)

    # format_name: form thật liệt kê AtCoder ĐẦU TIÊN; nếu Django không render
    # 'selected' thì serialize_form sẽ vớ nhầm 'atcoder'. Set tường minh, khớp
    # theo value hoặc label ('default', 'Mặc định', 'icpc', 'ioi16', 'vnoj'...).
    fmt = resolve_select(form, 'format_name', opt.format)
    if fmt is not None:
        items_set(items, 'format_name', fmt)
        print('  format_name -> %r' % fmt)

    # authors: form admin thường bắt buộc >= 1. Điền profile của chính mình.
    if form.find(attrs={'name': 'authors'}) is not None and not items_get(items, 'authors'):
        ppk = cli.profile_pk(opt.user)
        if ppk:
            items_set(items, 'authors', ppk)
            print('  authors -> %s (pk %s)' % (opt.user, ppk))
        else:
            print('  ! không tự tìm được profile pk của %s — nếu POST báo thiếu authors, '
                  'điền tay trong admin UI' % opt.user)

    # visible
    items_del(items, 'is_visible')
    if opt.visible:
        items_set(items, 'is_visible', 'on')

    # rating. --rate-all implies --rated because rate_all is meaningless when
    # the contest is not rated. Bounds are optional filters.
    rated = bool(opt.rated or opt.rate_all)
    apply_rating_options(items, form,
                         rated=(True if rated else None),
                         rate_all=(True if opt.rate_all else None),
                         rating_floor=opt.rating_floor,
                         rating_ceiling=opt.rating_ceiling,
                         require_fields=rated or opt.rating_floor is not None or opt.rating_ceiling is not None)
    if rated or opt.rating_floor is not None or opt.rating_ceiling is not None:
        print_rating_status(items)

    # problems inline
    prefix = detect_inline_prefix(form)
    if prefix is None:
        raise SystemExit('Không dò được inline formset ContestProblem trên form add — '
                         'chạy `inspect` và gửi output để cập nhật tool.')
    print('  inline prefix = %r' % prefix)
    pk_pairs = resolve_codes(cli, opt.problems, opt.code_prefix)
    fill_problem_rows(items, form, prefix, pk_pairs, opt.points_each, start_index=0, partial=opt.partial)
    sanity_check_problem_rows(items, prefix, pk_pairs, start_index=0, partial=opt.partial)

    if opt.dry_run:
        print('\n--dry-run: payload sẽ POST tới %s:' % path)
        for k, v in items:
            if k == 'description':
                v = (v[:60] + '...') if len(v) > 60 else v
            print('   %-40s %r' % (k, v))
        return
    cli.post_admin_form(path, items)
    print('OK: contest %s đã tạo (%s). URL: %s/contest/%s'
          % (opt.key, 'VISIBLE' if opt.visible else 'hidden', cli.base, opt.key))


def cmd_add_problems(cli, opt):
    pk = cli.contest_pk(opt.key)
    path = '/admin/judge/contest/%s/change/' % pk
    soup, form = cli.open_admin_form(path)
    items = serialize_form(form)
    items_set(items, 'csrfmiddlewaretoken', cli.csrf(soup))
    prefix = detect_inline_prefix(form)
    if prefix is None:
        raise SystemExit('Không dò được inline formset ContestProblem — chạy `inspect`.')
    # On a change form, TOTAL_FORMS includes Django admin's extra blank rows.
    # Append into the first blank row after existing initial rows, not after all
    # rendered blanks; otherwise adding to a 3-problem contest with 3 extra rows
    # would create rows 6.. and orders 7.. instead of rows 3.. and orders 4...
    start = int(items_get(items, '%s-INITIAL_FORMS' % prefix) or '0')
    pk_pairs = resolve_codes(cli, opt.problems, opt.code_prefix)
    fill_problem_rows(items, form, prefix, pk_pairs, opt.points_each, start_index=start, partial=opt.partial)
    sanity_check_problem_rows(items, prefix, pk_pairs, start_index=start, partial=opt.partial)
    if opt.dry_run:
        print('\n--dry-run: sẽ thêm %d bài (row %d..%d) vào %s' % (len(pk_pairs), start, start + len(pk_pairs) - 1, opt.key))
        return
    cli.post_admin_form(path, items)
    print('OK: đã thêm %d bài vào contest %s' % (len(pk_pairs), opt.key))


def cmd_set_visible(cli, opt, visible):
    pk = cli.contest_pk(opt.key)
    path = '/admin/judge/contest/%s/change/' % pk
    soup, form = cli.open_admin_form(path)
    items = serialize_form(form)
    items_set(items, 'csrfmiddlewaretoken', cli.csrf(soup))
    items_del(items, 'is_visible')
    if visible:
        items_set(items, 'is_visible', 'on')
    cli.post_admin_form(path, items)
    print('OK: contest %s -> %s' % (opt.key, 'VISIBLE' if visible else 'HIDDEN'))


def cmd_set_rated(cli, opt, rated):
    pk = cli.contest_pk(opt.key)
    path = '/admin/judge/contest/%s/change/' % pk
    soup, form = cli.open_admin_form(path)
    items = serialize_form(form)
    items_set(items, 'csrfmiddlewaretoken', cli.csrf(soup))

    if rated:
        # None means preserve the current checkbox value. Explicit flags control
        # whether rate_all is changed.
        rate_all = None
        if getattr(opt, 'rate_all', False):
            rate_all = True
        if getattr(opt, 'no_rate_all', False):
            rate_all = False
        apply_rating_options(items, form,
                             rated=True,
                             rate_all=rate_all,
                             rating_floor=getattr(opt, 'rating_floor', None),
                             rating_ceiling=getattr(opt, 'rating_ceiling', None),
                             clear_rating_bounds=bool(getattr(opt, 'clear_rating_bounds', False)),
                             require_fields=True)
    else:
        # Turning rating off should also clear rate_all to avoid stale confusing
        # state in the admin form. Bounds are preserved unless the user asks to
        # clear them, so re-enabling later can reuse the same thresholds.
        apply_rating_options(items, form,
                             rated=False,
                             rate_all=False,
                             clear_rating_bounds=bool(getattr(opt, 'clear_rating_bounds', False)),
                             require_fields=True)

    print_rating_status(items)
    if getattr(opt, 'dry_run', False):
        print('\n--dry-run: payload sẽ POST tới %s:' % path)
        for k, v in items:
            if k in ('is_rated', 'rate_all', 'rating_floor', 'rating_ceiling', 'csrfmiddlewaretoken'):
                print('   %-40s %r' % (k, v))
        return
    cli.post_admin_form(path, items)
    print('OK: contest %s -> %s' % (opt.key, 'RATED' if rated else 'UNRATED'))


def main():
    # Các tham số chung nằm trong một "parent parser" và được gắn vào CẢ parser
    # gốc LẪN mọi subcommand, nên `--user/--password/--site/...` chạy được ở cả
    # hai vị trí: trước HOẶC sau tên lệnh. (argparse chỉ nhận option của parser
    # gốc TRƯỚC tên subcommand — đó là lý do `inspect --user ntannn` báo lỗi.)
    # Hai bẫy argparse chồng nhau khi muốn option chung dùng được ở CẢ hai vị
    # trí (trước/sau tên lệnh):
    #  (1) required=True trên parent -> parser GỐC đòi --user trước khi đọc tới
    #      subcommand -> `inspect --user ntannn` lỗi. Nên KHÔNG required ở đây.
    #  (2) mặc định thường (vd None) trên subparser -> khi bạn đặt --user TRƯỚC
    #      lệnh, subparser (cũng có --user) ghi đè lại bằng None. Dùng
    #      default=SUPPRESS: tầng nào không thấy option thì KHÔNG chạm giá trị
    #      tầng kia. Ta tự áp default + tự kiểm tra bắt buộc sau parse_args.
    S = argparse.SUPPRESS
    common = argparse.ArgumentParser(add_help=False)
    common.add_argument('--site', default=S)
    common.add_argument('--user', default=S)
    common.add_argument('--password', default=S)
    common.add_argument('--code-prefix', default=S, help='prefix khi --problems là id trần (mặc định cses_)')
    common.add_argument('--debug', action='store_true', default=S)

    ap = argparse.ArgumentParser(description='Tạo & quản lý contest trên CHT-oj qua HTTP admin.',
                                 formatter_class=argparse.RawDescriptionHelpFormatter, epilog=__doc__,
                                 parents=[common])
    sub = ap.add_subparsers(dest='cmd', required=True)

    sub.add_parser('inspect', parents=[common],
                   help='In toàn bộ field thật của form tạo contest (chạy trước lần đầu!).')

    c = sub.add_parser('create', parents=[common], help='Tạo contest mới.')
    c.add_argument('--key', required=True, help='mã contest: chỉ a-z, 0-9, _; không dùng dấu gạch ngang')
    c.add_argument('--name', required=True)
    c.add_argument('--start', required=True, help='"YYYY-MM-DD HH:MM"')
    c.add_argument('--end', required=True, help='"YYYY-MM-DD HH:MM"')
    c.add_argument('--problems', nargs='+', required=True, help='CSES id trần hoặc code đầy đủ')
    c.add_argument('--points-each', type=int, default=100)
    c.add_argument('--format', default='default',
                   help="format contest, khớp value/label trên form: default|icpc|ioi16|ioi|atcoder|ecoo|vnoj (mặc định: default)")
    c.add_argument('--format-config', default=None,
                   help='JSON cho format_config; mặc định null. Ví dụ VNOJ: "{\"penalty\":5,\"LSO\":false}"')
    c.add_argument('--partial', action='store_true',
                   help='bật partial cho từng bài trong contest (mặc định TẮT — CSES chấm nhị phân)')
    c.add_argument('--description', help='mô tả markdown (mặc định = name)')
    c.add_argument('--description-file', help='đọc mô tả từ file .md')
    c.add_argument('--visible', action='store_true', help='public ngay (mặc định: ẩn)')
    c.add_argument('--rated', action='store_true', help='bật tính rating cho contest ngay khi tạo')
    c.add_argument('--rate-all', action='store_true', help='rate tất cả user đã tham gia; tự động bật --rated')
    c.add_argument('--rating-floor', type=int, help='chỉ rate user có rating >= giá trị này')
    c.add_argument('--rating-ceiling', type=int, help='chỉ rate user có rating <= giá trị này')
    c.add_argument('--dry-run', action='store_true', help='chỉ in payload, không POST')

    a = sub.add_parser('add-problems', parents=[common], help='Thêm bài vào contest đã có.')
    a.add_argument('--key', required=True)
    a.add_argument('--problems', nargs='+', required=True)
    a.add_argument('--points-each', type=int, default=100)
    a.add_argument('--partial', action='store_true')
    a.add_argument('--dry-run', action='store_true')

    for nm in ('set-visible', 'set-hidden'):
        s = sub.add_parser(nm, parents=[common])
        s.add_argument('--key', required=True)

    sr = sub.add_parser('set-rated', parents=[common], help='Bật tính rating cho contest đã có.')
    sr.add_argument('--key', required=True)
    rg = sr.add_mutually_exclusive_group()
    rg.add_argument('--rate-all', action='store_true', help='bật rate_all')
    rg.add_argument('--no-rate-all', action='store_true', help='tắt rate_all nhưng vẫn rated')
    sr.add_argument('--rating-floor', type=int, help='chỉ rate user có rating >= giá trị này')
    sr.add_argument('--rating-ceiling', type=int, help='chỉ rate user có rating <= giá trị này')
    sr.add_argument('--clear-rating-bounds', action='store_true', help='xóa rating_floor/rating_ceiling')
    sr.add_argument('--dry-run', action='store_true')

    su = sub.add_parser('set-unrated', parents=[common], help='Tắt tính rating cho contest đã có.')
    su.add_argument('--key', required=True)
    su.add_argument('--clear-rating-bounds', action='store_true', help='xóa rating_floor/rating_ceiling')
    su.add_argument('--dry-run', action='store_true')

    opt = ap.parse_args()
    # SUPPRESS nghĩa là attribute có thể vắng mặt -> tự áp default ở đây.
    opt.site = getattr(opt, 'site', None) or DEFAULT_SITE
    opt.user = getattr(opt, 'user', None)
    opt.password = getattr(opt, 'password', None)
    opt.code_prefix = getattr(opt, 'code_prefix', None) or 'cses_'
    opt.debug = bool(getattr(opt, 'debug', False))
    if not opt.user:
        ap.error('thiếu --user (đặt trước hoặc sau tên lệnh đều được, '
                 'vd: `contest_tool.py inspect --user ntannn`)')
    if getattr(opt, 'key', None):
        validate_contest_key(opt.key)
    password = opt.password or getpass.getpass('Admin password for %s: ' % opt.user)
    cli = Client(opt.site, debug=opt.debug)
    cli.login(opt.user, password)

    if opt.cmd == 'inspect':
        cmd_inspect(cli, opt)
    elif opt.cmd == 'create':
        cmd_create(cli, opt)
    elif opt.cmd == 'add-problems':
        cmd_add_problems(cli, opt)
    elif opt.cmd == 'set-visible':
        cmd_set_visible(cli, opt, True)
    elif opt.cmd == 'set-hidden':
        cmd_set_visible(cli, opt, False)
    elif opt.cmd == 'set-rated':
        cmd_set_rated(cli, opt, True)
    elif opt.cmd == 'set-unrated':
        cmd_set_rated(cli, opt, False)


if __name__ == '__main__':
    main()