import os

# Đường dẫn đến thư mục chứa dữ liệu
ROOT_DIR = "CSES_Data_Full"

def prepend_header_to_markdown(file_path, header_text):
    """
    Thêm header vào đầu file markdown nếu chưa có.
    """
    if not os.path.exists(file_path):
        return

    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            original_content = f.read()

        # Kiểm tra xem file đã có header này chưa để tránh chèn trùng lặp khi chạy nhiều lần
        # So sánh dòng đầu tiên (đã strip) với header mới
        first_line = original_content.split('\n', 1)[0].strip()
        expected_header = header_text.strip()

        if first_line == expected_header:
            print(f"  [Skip] File {os.path.basename(file_path)} đã có tiêu đề.")
            return

        # Ghi đè file với header mới + nội dung cũ
        new_content = header_text + "\n\n" + original_content
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(new_content)
        
        print(f"  [OK] Đã thêm tiêu đề vào {os.path.basename(file_path)}")

    except Exception as e:
        print(f"  [Error] Lỗi xử lý file {file_path}: {e}")

def rename_tests_zip(folder_path, task_id):
    """
    Đổi tên tests.zip -> tests_{id}.zip
    """
    old_path = os.path.join(folder_path, "tests.zip")
    new_name = f"tests_{task_id}.zip"
    new_path = os.path.join(folder_path, new_name)

    if os.path.exists(old_path):
        try:
            os.rename(old_path, new_path)
            print(f"  [OK] Đã đổi tên: tests.zip -> {new_name}")
        except Exception as e:
            print(f"  [Error] Không thể đổi tên zip: {e}")
    elif os.path.exists(new_path):
        print(f"  [Skip] File {new_name} đã tồn tại.")

def process_folders():
    if not os.path.exists(ROOT_DIR):
        print(f"Không tìm thấy thư mục '{ROOT_DIR}'. Hãy đặt file code này ngang hàng với thư mục data.")
        return

    print("Đang quét và xử lý dữ liệu...")
    
    # Duyệt qua tất cả các thư mục con
    for dirpath, dirnames, filenames in os.walk(ROOT_DIR):
        folder_name = os.path.basename(dirpath)
        
        # Kiểm tra xem folder có phải là folder bài tập không
        # Quy tắc crawler cũ: ID_Name (Ví dụ: 1084_Apartments)
        # Điều kiện: Có dấu gạch dưới và phần đầu là số
        if "_" in folder_name:
            parts = folder_name.split("_", 1)
            task_id = parts[0]
            
            if task_id.isdigit():
                task_name_raw = parts[1]
                # Làm đẹp tên bài (bỏ dấu gạch nối thừa nếu có, thay bằng dấu cách cho đẹp mắt)
                # Ví dụ: Apartments -> Apartments; Weird-Algorithm -> Weird Algorithm
                task_name_display = task_name_raw.replace("-", " ").replace("_", " ")
                
                print(f"\n--- Xử lý bài: {task_name_display} (ID: {task_id}) ---")
                
                # Tạo header mẫu: "# 1084 - Apartments"
                header_h1 = f"# {task_id} - {task_name_display}"

                # 1. Xử lý statement_en.md
                stmt_path = os.path.join(dirpath, "statement_en.md")
                prepend_header_to_markdown(stmt_path, header_h1)

                # 2. Xử lý analysis_en.md
                analy_path = os.path.join(dirpath, "analysis_en.md")
                prepend_header_to_markdown(analy_path, header_h1)

                # 3. Đổi tên file tests.zip
                rename_tests_zip(dirpath, task_id)

    print("\nHoàn tất xử lý!")

if __name__ == "__main__":
    process_folders()