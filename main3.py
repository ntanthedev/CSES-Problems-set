import requests
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry
from bs4 import BeautifulSoup
import os
import time
from markdownify import markdownify as md
from urllib.parse import urljoin
import re

class CSESAdvancedCrawler:
    def __init__(self, username, password):
        self.base_url = "https://cses.fi"
        self.session = requests.Session()
        self.username = username
        self.password = password
        
        # --- CẤU HÌNH AUTO RETRY (QUAN TRỌNG) ---
        # Tự động thử lại 5 lần nếu kết nối bị ngắt hoặc gặp lỗi server
        # backoff_factor=2 nghĩa là đợi lần lượt 2s, 4s, 8s, 16s... nếu lỗi
        retry_strategy = Retry(
            total=5,
            backoff_factor=2, 
            status_forcelist=[429, 500, 502, 503, 504],
            allowed_methods=["HEAD", "GET", "POST", "OPTIONS"]
        )
        adapter = HTTPAdapter(max_retries=retry_strategy)
        self.session.mount("https://", adapter)
        self.session.mount("http://", adapter)
        # ----------------------------------------
        
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
        return "".join(x for x in name if x.isalnum() or x in " ._-").strip()

    def process_math_elements(self, soup):
        for math in soup.find_all("span", class_="math-inline"):
            latex = math.get_text().strip()
            math.replace_with(f"${latex}$")
        for math in soup.find_all("span", class_="math-display"):
            latex = math.get_text().strip()
            math.replace_with(f"\n$${latex}$$\n")
        return soup

    def process_images(self, soup, save_folder):
        images = soup.find_all("img")
        for img in images:
            img_url = img.get("src")
            if not img_url: continue
            
            full_url = urljoin(self.base_url, img_url)
            filename = self.sanitize_filename(img_url.split("/")[-1])
            save_path = os.path.join(save_folder, filename)
            
            try:
                # Nếu ảnh đã tải rồi thì không tải lại
                if not os.path.exists(save_path):
                    r = self.session.get(full_url, timeout=10) # Thêm timeout
                    if r.status_code == 200:
                        with open(save_path, "wb") as f:
                            f.write(r.content)
                
                img['src'] = filename
                if img.has_attr('class'): del img['class']
                if img.has_attr('style'): del img['style']
                
            except Exception:
                pass
        return soup

    def html_to_markdown_file(self, content_div, folder_path, filename):
        if not content_div: return False
        content_div = self.process_math_elements(content_div)
        content_div = self.process_images(content_div, folder_path)
        for tag in content_div(["script", "style"]):
            tag.decompose()

        md_text = md(str(content_div), heading_style="ATX", code_language="cpp")
        
        with open(os.path.join(folder_path, filename), "w", encoding="utf-8") as f:
            f.write(md_text)
        return True

    def download_task_content(self, task_id, folder_path):
        # Kiểm tra file đã tồn tại chưa
        if os.path.exists(os.path.join(folder_path, "statement_en.md")):
             # Giả sử đã có đề bài thì không tải lại
             return True

        url = f"{self.base_url}/problemset/task/{task_id}/"
        try:
            resp = self.session.get(url, timeout=15)
            soup = BeautifulSoup(resp.text, "html.parser")
            content = soup.find("div", class_="content")
            
            if self.html_to_markdown_file(content, folder_path, "statement_en.md"):
                print("    + Đã tải đề bài.")
                return True
            else:
                print("    - Lỗi: Không thấy nội dung đề.")
                return False
        except Exception as e:
            print(f"    ! Lỗi tải đề: {e}")
            return False

    def download_model_solution(self, task_id, folder_path):
        if os.path.exists(os.path.join(folder_path, "analysis_en.md")):
            return 

        url = f"{self.base_url}/problemset/model/{task_id}/"
        try:
            resp = self.session.get(url, timeout=15)
            if resp.status_code != 200: return

            soup = BeautifulSoup(resp.text, "html.parser")
            content = soup.find("div", class_="content")
            
            if self.html_to_markdown_file(content, folder_path, "analysis_en.md"):
                print("    + Đã tải Analysis.")
                pre_code = soup.find("pre", class_="prettyprint")
                if pre_code:
                    with open(os.path.join(folder_path, "solution.cpp"), "w", encoding="utf-8") as f:
                        f.write(pre_code.get_text())
        except Exception:
            pass

    def download_tests(self, task_id, folder_path):
        if os.path.exists(os.path.join(folder_path, "tests.zip")):
            return

        url = f"{self.base_url}/problemset/tests/{task_id}/"
        try:
            resp = self.session.get(url, timeout=15)
            soup = BeautifulSoup(resp.text, "html.parser")
            
            csrf = soup.find("input", {"name": "csrf_token"})
            if csrf:
                print("    + Đang tải Tests.zip ...")
                post_resp = self.session.post(url, data={
                    "csrf_token": csrf["value"],
                    "download": "true"
                }, stream=True, timeout=30) # Test nặng nên timeout lâu hơn
                
                if post_resp.status_code == 200:
                    with open(os.path.join(folder_path, "tests.zip"), "wb") as f:
                        for chunk in post_resp.iter_content(chunk_size=8192):
                            f.write(chunk)
                    print("    + Tải Tests xong.")
        except Exception as e:
            print(f"    ! Lỗi tải tests: {e}")

    def run(self):
        if not self.login(): return

        print("[Crawler] Đang quét danh sách bài tập...")
        try:
            resp = self.session.get(f"{self.base_url}/problemset/", timeout=15)
        except Exception as e:
            print(f"Lỗi kết nối trang chủ: {e}")
            return

        soup = BeautifulSoup(resp.text, "html.parser")
        
        elements = soup.find_all(['h2', 'ul'])
        current_category = "General"
        
        for element in elements:
            if element.name == 'h2':
                cat_name = element.get_text().strip()
                if cat_name in ["General", "Code submissions"]: continue 
                current_category = cat_name
                print(f"\n=== CATEGORY: {current_category} ===")
                
            elif element.name == 'ul' and 'task-list' in element.get('class', []):
                tasks = element.find_all("li", class_="task")
                for task in tasks:
                    link_tag = task.find("a")
                    if not link_tag: continue
                    
                    href = link_tag['href']
                    task_id = href.split("/")[-1]
                    task_name = link_tag.get_text().strip()
                    
                    # Đường dẫn thư mục bài
                    folder_name = f"{task_id}_{self.sanitize_filename(task_name)}"
                    full_path = os.path.join(self.root_dir, self.sanitize_filename(current_category), folder_name)
                    
                    if not os.path.exists(full_path):
                        os.makedirs(full_path)
                    
                    # --- KIỂM TRA ĐÃ TẢI CHƯA (Logic mới) ---
                    # Nếu đã có file statement_en.md và tests.zip (hoặc chỉ statement nếu bài đó k có test)
                    # Ở đây mình chỉ check statement cho nhanh, bạn có thể thêm check tests.zip nếu muốn kỹ
                    if os.path.exists(os.path.join(full_path, "statement_en.md")):
                        print(f"[*] {task_name} (ID: {task_id}) -> ĐÃ CÓ. SKIP.")
                        continue 
                    # ----------------------------------------

                    print(f"[*] Xử lý: {task_name} (ID: {task_id})")
                    
                    # Gọi các hàm tải
                    self.download_task_content(task_id, full_path)
                    self.download_model_solution(task_id, full_path)
                    self.download_tests(task_id, full_path)
                    
                    # Delay tăng lên một chút để an toàn
                    time.sleep(2)

# --- CẤU HÌNH ---
USER = "ntantest"      
PASS = "123456" 

bot = CSESAdvancedCrawler(USER, PASS)
bot.run()