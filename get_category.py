import re
from bs4 import BeautifulSoup
from urllib.parse import urljoin

BASE = "https://cses.fi"

TASK_ID_RE = re.compile(r"/problemset/task/(\d+)")

def parse_problemset_list(html: str, base_url: str = BASE):
    """
    Trả về list các dict:
    {
      'category': 'Introductory Problems',
      'id': 1068,
      'title': 'Weird Algorithm',
      'url': 'https://cses.fi/problemset/task/1068',
      'detail': '154261 / 161465',
      'score_class': 'task-score icon full'  # hoặc None
    }
    """
    soup = BeautifulSoup(html, "lxml")
    out = []

    for h2 in soup.select("div.content h2"):
        category = h2.get_text(strip=True)

        ul = h2.find_next_sibling("ul", class_="task-list")
        if not ul:
            continue

        for li in ul.find_all("li", recursive=False):
            # Chỉ lấy bài thật: li.task
            if "task" not in (li.get("class") or []):
                continue

            a = li.find("a", href=True)
            if not a:
                continue

            href = a["href"].strip()
            m = TASK_ID_RE.search(href)
            if not m:
                continue

            task_id = int(m.group(1))
            title = a.get_text(strip=True)
            url = urljoin(base_url, href)

            detail_span = li.find("span", class_="detail")
            detail = detail_span.get_text(strip=True) if detail_span else None

            score_span = li.find("span", class_=lambda c: c and "task-score" in c)
            score_class = " ".join(score_span.get("class", [])) if score_span else None

            out.append({
                "category": category,
                "id": task_id,
                "title": title,
                "url": url,
                "detail": detail,
                "score_class": score_class,
            })

    return out
if __name__ == "__main__":
    tasks = parse_problemset_list(html_problemset)
    intro = filter_tasks(tasks, category="Introductory Problems")