import requests
from bs4 import BeautifulSoup
import os

BASE_URL = "https://oj.thptchuyenhatinh.edu.vn"

# Khởi tạo session để lưu cookie
session = requests.Session()

# Bước 1: lấy CSRF token
login_page = session.get(f"{BASE_URL}/accounts/login/?next=")
soup = BeautifulSoup(login_page.text, "html.parser")
csrf_token = soup.find("input", {"name": "csrf_token"})["value"]

# Bước 2: gửi form đăng nhập
payload = {
    "nick": "ntannn",
    "pass": "Nhattan2007..",
    "csrf_token": csrf_token,
}
response = session.post(f"{BASE_URL}/accounts/login/?next=", data=payload)
assert response.status_code == 200, "Đăng nhập thất bại"

# Bước 3: tải trang danh sách bài
task = session.get(f"https://oj.thptchuyenhatinh.edu.vn/contest/wbz2025_pa06")
# Phân tích listing để lấy các ID bài (nằm trong đường dẫn task/<ID>)
with open("task.html", "w", encoding="utf-8") as f:
    f.write(task.text)