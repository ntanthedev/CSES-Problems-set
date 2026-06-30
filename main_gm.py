import requests
from bs4 import BeautifulSoup
import os
import time
from markdownify import markdownify as md
from urllib.parse import urljoin

class CSESCrawler:
    def __init__(self, username, password):
        self.base_url = "https://cses.fi"
        self.session = requests.Session()
        self.username = username
        self.password = password
        
        # Tạo folder tổng
        if not os.path.exists("CSES_Problems"):
            os.makedirs("CSES_Problems")

    def login(self):
        print(f"[Login] Đang đăng nhập tài khoản {self.username}...")
        try:
            login_page = self.session.get(f"{self.base_url}/login")
            soup = BeautifulSoup(login_page.text, "html.parser")
            
            # Kiểm tra xem có lấy được form login không
            csrf_input = soup.find("input", {"name": "csrf_token"})
            if not csrf_input:
                print("[Login] Không tìm thấy form đăng nhập (Có thể IP bị chặn hoặc đã login).")
                return False
                
            csrf_token = csrf_input["value"]
            payload = {
                "nick": self.username,
                "pass": self.password,
                "csrf_token": csrf_token,
            }
            response = self.session.post(f"{self.base_url}/login", data=payload)
            
            if "Logout" in response.text or "/logout" in response.text:
                print("[Login] Thành công!")
                return True
            else:
                print("[Login] Thất bại. Kiểm tra lại user/pass.")
                return False
        except Exception as e:
            print(f"[Login] Lỗi kết nối: {e}")
            return False

    def process_math_elements(self, soup):
        """Chuyển đổi MathJax HTML sang LaTeX ($...$)"""
        for math in soup.find_all("span", class_="math-inline"):
            latex = math.get_text().strip()
            math.replace_with(f"${latex}$")
        
        for math in soup.find_all("span", class_="math-display"):
            latex = math.get_text().strip()
            math.replace_with(f"\n$${latex}$$\n")
        return soup

    def process_and_download_images(self, soup, folder_path):
        """
        Tìm tất cả thẻ img, tải ảnh về, và sửa src thành đường dẫn cục bộ
        """
        images = soup.find_all("img")
        if not images:
            return soup

        print(f"   -> Phát hiện {len(images)} hình ảnh. Đang tải...")
        
        for i, img in enumerate(images):
            img_url = img.get("src")
            if not img_url:
                continue
            
            # Tạo đường dẫn tuyệt đối để tải
            full_img_url = urljoin(self.base_url, img_url)
            
            # Lấy tên file gốc hoặc đặt tên mới
            # CSES url thường là: /file/hash/Name.png -> Lấy Name.png
            file_name = img_url.split("/")[-1]
            # Xử lý trường hợp tên file có ký tự lạ
            file_name = "".join(x for x in file_name if x.isalnum() or x in "._-")
            
            local_img_path = os.path.join(folder_path, file_name)

            try:
                # Tải ảnh
                img_resp = self.session.get(full_img_url)
                if img_resp.status_code == 200:
                    with open(local_img_path, "wb") as f:
                        f.write(img_resp.content)
                    
                    # SỬA HTML: Trỏ src về file vừa tải (đường dẫn tương đối)
                    img['src'] = file_name
                    # Xóa class để markdownify không render lộn xộn
                    del img['class'] 
                    del img['style']
                else:
                    print(f"      [!] Lỗi tải ảnh: {full_img_url}")
            except Exception as e:
                print(f"      [!] Exception tải ảnh: {e}")
        
        return soup

    def get_task_content(self, task_id, folder_path):
        url = f"{self.base_url}/problemset/task/{task_id}/"
        resp = self.session.get(url)
        soup = BeautifulSoup(resp.text, "html.parser")
        
        content_div = soup.find("div", class_="content")
        
        if content_div:
            # 1. Xử lý Toán học
            content_div = self.process_math_elements(content_div)
            
            # 2. Xử lý Hình ảnh (Tải về + Sửa link)
            content_div = self.process_and_download_images(content_div, folder_path)
            
            # 3. Dọn dẹp script
            for tag in content_div(["script", "style"]):
                tag.decompose()

            # 4. Convert sang Markdown
            html_content = str(content_div)
            # heading_style="ATX" để dùng # thay vì gạch chân
            markdown_text = md(html_content, heading_style="ATX", newline_style="BACKSLASH")
            
            # Lưu file markdown
            with open(f"{folder_path}/problem_en.md", "w", encoding="utf-8") as f:
                f.write(f"# Problem ID: {task_id}\n\n")
                f.write(markdown_text)
            
            print("   -> Đã tạo file markdown (kèm ảnh).")
        else:
            print("   -> Lỗi: Không lấy được nội dung bài.")

    def get_model_solution(self, task_id, folder_path):
        url = f"{self.base_url}/problemset/model/{task_id}/"
        resp = self.session.get(url)
        soup = BeautifulSoup(resp.text, "html.parser")
        pre_code = soup.find("pre", class_="prettyprint")
        
        if pre_code:
            code_content = pre_code.get_text()
            with open(f"{folder_path}/solution.cpp", "w", encoding="utf-8") as f:
                f.write(code_content)
            print("   -> Đã tải Code mẫu.")
        else:
            # Có thể chưa giải bài này nên không xem được code
            pass

    def download_tests(self, task_id, folder_path):
        url = f"{self.base_url}/problemset/tests/{task_id}/"
        resp = self.session.get(url)
        soup = BeautifulSoup(resp.text, "html.parser")
        
        csrf_input = soup.find("input", {"name": "csrf_token"})
        if csrf_input:
            token = csrf_input["value"]
            payload = {"csrf_token": token, "download": "true"}
            
            print("   -> Đang tải Tests...")
            post_resp = self.session.post(url, data=payload, stream=True)
            
            if post_resp.status_code == 200:
                with open(f"{folder_path}/tests.zip", "wb") as f:
                    for chunk in post_resp.iter_content(chunk_size=8192):
                        f.write(chunk)
                print("   -> Tải Tests thành công.")
            else:
                print("   -> Lỗi tải file ZIP.")

    def run_crawler(self, start_id=1068, count=5):
        """
        start_id: ID bài bắt đầu (ví dụ 1068 là Weird Algorithm)
        count: Số lượng bài muốn tải
        """
        if not self.login():
            return

        # Để đơn giản, CSES ID thường là số liên tiếp hoặc trong list.
        # Cách tốt nhất là vào trang list lấy href như code cũ.
        # Ở đây tôi dùng lại logic lấy list cho chuẩn.
        
        print("[Crawler] Đang lấy danh sách bài...")
        list_page = self.session.get(f"{self.base_url}/problemset/")
        soup = BeautifulSoup(list_page.text, "html.parser")
        task_links = soup.select("li.task > a")
        
        print(f"[Crawler] Tìm thấy {len(task_links)} bài tập.")
        
        processed = 0
        for task in task_links:
            if processed >= count: break
            
            href = task["href"] 
            task_id = href.split("/")[-1] # id bài
            task_name = task.get_text().strip()
            
            # Tạo tên thư mục an toàn
            safe_name = "".join(x for x in task_name if x.isalnum() or x in " _-").strip()
            folder_path = f"CSES_Problems/{task_id}_{safe_name}"
            
            if not os.path.exists(folder_path):
                os.makedirs(folder_path)
            
            print(f"\n[{processed+1}/{count}] Xử lý: {task_name} (ID: {task_id})")
            
            self.get_task_content(task_id, folder_path)
            self.get_model_solution(task_id, folder_path)
            self.download_tests(task_id, folder_path)
            
            processed += 1
            time.sleep(1) # Delay nhẹ

# --- CONFIG ---
USER = "ntannn"      # Thay user của bạn
PASS = "Nhattan2007" # Thay pass của bạn

bot = CSESCrawler(USER, PASS)
# Chạy thử tải 5 bài đầu tiên
bot.run_crawler(count=5)