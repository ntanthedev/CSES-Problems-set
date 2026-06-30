import requests
from bs4 import BeautifulSoup
import os
import time
from markdownify import markdownify as md
from urllib.parse import urljoin
import re
"""
- thêm tải theo category
- cải tiến xử lý ảnh + mathjax
- tải markdown solution
"""

class CSESAdvancedCrawler:
    def __init__(self, username, password):
        self.base_url = "https://cses.fi"
        self.session = requests.Session()
        self.username = username
        self.password = password
        
        # Thư mục gốc
        self.root_dir = "CSES_Data_Full"
        if not os.path.exists(self.root_dir):
            os.makedirs(self.root_dir)

    def login(self):
        print(f"[Login] Đang đăng nhập: {self.username}...")
        try:
            login_page = self.session.get(f"{self.base_url}/login")
            soup = BeautifulSoup(login_page.text, "html.parser")
            
            csrf_input = soup.find("input", {"name": "csrf_token"})
            if not csrf_input:
                print("[Login] Lỗi: Không tìm thấy form (Check IP/Cookie).")
                return False
                
            payload = {
                "nick": self.username,
                "pass": self.password,
                "csrf_token": csrf_input["value"],
            }
            response = self.session.post(f"{self.base_url}/login", data=payload)
            
            if "Logout" in response.text or "/logout" in response.text:
                print("[Login] Thành công!\n")
                return True
            else:
                print("[Login] Thất bại. Kiểm tra mật khẩu.")
                return False
        except Exception as e:
            print(f"[Login] Exception: {e}")
            return False

    def sanitize_filename(self, name):
        """Làm sạch tên file/folder"""
        return "".join(x for x in name if x.isalnum() or x in " ._-").strip()

    def process_math_elements(self, soup):
        """Chuyển đổi MathJax HTML sang LaTeX"""
        for math in soup.find_all("span", class_="math-inline"):
            latex = math.get_text().strip()
            math.replace_with(f"${latex}$")
        
        for math in soup.find_all("span", class_="math-display"):
            latex = math.get_text().strip()
            math.replace_with(f"\n$${latex}$$\n")
        return soup

    def process_images(self, soup, save_folder):
        """Tải ảnh và sửa link trong HTML"""
        images = soup.find_all("img")
        for img in images:
            img_url = img.get("src")
            if not img_url: continue
            
            # Tải ảnh
            full_url = urljoin(self.base_url, img_url)
            filename = self.sanitize_filename(img_url.split("/")[-1])
            save_path = os.path.join(save_folder, filename)
            
            try:
                # Kiểm tra nếu ảnh chưa tải thì mới tải
                if not os.path.exists(save_path):
                    r = self.session.get(full_url)
                    if r.status_code == 200:
                        with open(save_path, "wb") as f:
                            f.write(r.content)
                
                # Sửa src thành đường dẫn tương đối
                img['src'] = filename
                # Xóa style/class để markdown đẹp hơn
                if img.has_attr('class'): del img['class']
                if img.has_attr('style'): del img['style']
                
            except Exception:
                pass
        return soup

    def html_to_markdown_file(self, content_div, folder_path, filename):
        """Hàm chung để convert HTML div sang file Markdown"""
        if not content_div: return False
        
        # 1. Xử lý Toán
        content_div = self.process_math_elements(content_div)
        
        # 2. Xử lý Ảnh
        content_div = self.process_images(content_div, folder_path)
        
        # 3. Cleanup script/style
        for tag in content_div(["script", "style"]):
            tag.decompose()

        # 4. Convert Markdown
        # code_language="cpp" giúp markdownify nhận diện block code tốt hơn
        md_text = md(str(content_div), heading_style="ATX", code_language="cpp")
        
        # 5. Lưu file
        with open(os.path.join(folder_path, filename), "w", encoding="utf-8") as f:
            f.write(md_text)
        return True

    def download_task_content(self, task_id, folder_path):
        """Tải đề bài (Task)"""
        url = f"{self.base_url}/problemset/task/{task_id}/"
        resp = self.session.get(url)
        soup = BeautifulSoup(resp.text, "html.parser")
        content = soup.find("div", class_="content")
        
        if self.html_to_markdown_file(content, folder_path, "statement_en.md"):
            print("    + Đã tải đề bài (Statement).")
        else:
            print("    - Lỗi: Không thấy nội dung đề.")

    def download_model_solution(self, task_id, folder_path):
        """Tải lời giải chi tiết (Analysis)"""
        url = f"{self.base_url}/problemset/model/{task_id}/"
        resp = self.session.get(url)
        
        if resp.status_code != 200:
            print("    - Không thể truy cập Analysis (Chưa giải bài này?)")
            return

        soup = BeautifulSoup(resp.text, "html.parser")
        content = soup.find("div", class_="content")
        
        # Lưu toàn bộ phần giải thích + code vào file markdown
        if self.html_to_markdown_file(content, folder_path, "analysis_en.md"):
            print("    + Đã tải Analysis (Lời giải + Giải thích).")
            
            # (Option) Vẫn trích xuất riêng file .cpp sạch để tiện chấm
            pre_code = soup.find("pre", class_="prettyprint")
            if pre_code:
                with open(os.path.join(folder_path, "solution.cpp"), "w", encoding="utf-8") as f:
                    f.write(pre_code.get_text())
        else:
            print("    - Không tìm thấy nội dung Analysis.")

    def download_tests(self, task_id, folder_path):
        """Tải Test cases"""
        url = f"{self.base_url}/problemset/tests/{task_id}/"
        resp = self.session.get(url)
        soup = BeautifulSoup(resp.text, "html.parser")
        
        csrf = soup.find("input", {"name": "csrf_token"})
        if csrf:
            print("    + Đang tải Tests.zip ...")
            try:
                post_resp = self.session.post(url, data={
                    "csrf_token": csrf["value"],
                    "download": "true"
                }, stream=True)
                
                if post_resp.status_code == 200:
                    with open(os.path.join(folder_path, "tests.zip"), "wb") as f:
                        for chunk in post_resp.iter_content(chunk_size=8192):
                            f.write(chunk)
                    print("    + Tải Tests xong.")
                else:
                    print("    - Lỗi tải Tests.")
            except Exception as e:
                print(f"    - Exception tải tests: {e}")
        else:
            print("    - Không có nút download tests.")

    def run(self):
        if not self.login(): return

        print("[Crawler] Đang quét danh sách bài tập theo Category...")
        resp = self.session.get(f"{self.base_url}/problemset/")
        soup = BeautifulSoup(resp.text, "html.parser")
        
        # Logic quét theo Category:
        # CSES cấu trúc: <h2>Tên Category</h2> <ul class="task-list">...</ul>
        # Chúng ta sẽ tìm tất cả h2 và ul, rồi ghép cặp chúng.
        
        elements = soup.find_all(['h2', 'ul'])
        current_category = "General"
        
        for element in elements:
            if element.name == 'h2':
                # Cập nhật category hiện tại
                cat_name = element.get_text().strip()
                # Bỏ qua mấy mục không phải bài tập
                if cat_name in ["General", "Code submissions"]: continue 
                current_category = cat_name
                print(f"\n=== CATEGORY: {current_category} ===")
                
            elif element.name == 'ul' and 'task-list' in element.get('class', []):
                # Duyệt các bài trong category hiện tại
                tasks = element.find_all("li", class_="task")
                for task in tasks:
                    link_tag = task.find("a")
                    if not link_tag: continue
                    
                    href = link_tag['href']
                    task_id = href.split("/")[-1]
                    task_name = link_tag.get_text().strip()
                    
                    # Tạo đường dẫn: CSES_Data / Category / ID_Name
                    folder_name = f"{task_id}_{self.sanitize_filename(task_name)}"
                    full_path = os.path.join(self.root_dir, self.sanitize_filename(current_category), folder_name)
                    
                    if not os.path.exists(full_path):
                        os.makedirs(full_path)
                        
                    print(f"[*] Xử lý bài: {task_name} (ID: {task_id})")
                    
                    # Gọi các hàm tải
                    self.download_task_content(task_id, full_path)
                    self.download_model_solution(task_id, full_path)
                    self.download_tests(task_id, full_path)
                    
                    # Delay để tránh bị ban IP
                    time.sleep(1.5)

# --- CẤU HÌNH ---
USER = "ntantest"      # Username
PASS = "123456" # Password

bot = CSESAdvancedCrawler(USER, PASS)
bot.run()