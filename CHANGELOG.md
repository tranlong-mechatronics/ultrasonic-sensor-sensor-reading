# Project Changelog & Bug Journal

This log tracks all technical challenges, hardware defects, and software bugs resolved during the development of the ESP32 Sonar Radar project.

---

## [Week 3] PlatformIO migration and baseline setup

**Context / Bối cảnh:**
* **EN:** These issues were encountered after a 5-day project hiatus, specifically during the migration phase from Arduino IDE to VS Code (PlatformIO) upon plugging in the ESP32 chip for baseline hardware verification.
* **VN:** Các lỗi này phát sinh sau 5 ngày dự án tạm dừng, cụ thể là trong giai đoạn chuyển đổi môi trường từ Arduino IDE sang VS Code (PlatformIO) ngay khi cắm cáp kết nối chip ESP32 để kiểm thử hệ thống.

### 1. Technical bug journal (English version)

| Bug / Issue | Symptom | Root Cause | Resolution |
| :--- | :--- | :--- | :--- |
| **Terminal character corruption** | Strange or corrupted characters (like ``) appearing in the Serial Monitor. | Baud rate configured in code (`115200`) mismatches VS Code's default terminal speed (`9600`). | Add `monitor_speed = 115200` to the `platformio.ini` configuration file. |
| **COM port locked (Error 2)** | `Access is denied` error occurs, blocking the code upload to the ESP32 chip. | The active Serial Monitor task is holding the COM6 port, blocking the uploader from accessing it. | Kill the active monitor terminal or replug the USB cable to reset Windows port handles. |
| **Frozen distance readings** | Distance measurements get stuck at `159cm - 160cm` even when blocking the sensor. | The software filter returns the previous valid value continuously because blocking the sensor causes a signal timeout (returning 0). | Check the 5V power supply (VIN pin) and adjust the boundary conditions in the filtering logic. |
| **Intermittent system noise** | Unstable measurements and random data jumps without any specific pattern. | **Hardware defect:** ESP32 chip pins have a poor electrical connection with the breadboard. | Press down the chip firmly and secure the jumper wires on the test board. |
| **Name collision with `std::distance`** | Compilation failed with a warning/error pointing to `std::distance`. | A local variable named `distance` conflicted with the C++ standard library's built-in iterator function `std::distance`. | Renamed the local variable from `distance` to `sonarDistance` to avoid namespace ambiguity. |
| **VS Code ghost compilation error** | Syntax was corrected but the `Problems` tab still flagged an undeclared variable error. | The source file had unsaved changes (indicated by a white dot on the tab), causing the background linter to evaluate an outdated code version. | Saved the file using `Ctrl + S` to refresh the compiler context. |
| **File renaming failure (EBUSY)** | `Error: EBUSY: resource busy or locked` popped up when renaming `.log` to `.csv`. | The PlatformIO Serial Monitor task was actively writing live stream data into the log file, causing Windows to lock the file handle. | Terminated the active monitor terminal (via the trash bin icon) to release the file handle before renaming. |

### 2. Nhật ký sửa lỗi dự án (Bản tiếng Việt đối chiếu)

| Lỗi gặp phải | Triệu chứng nhận biết | Nguyên nhân gốc rễ | Giải pháp dứt điểm |
| :--- | :--- | :--- | :--- |
| **Lỗi vỡ ký tự terminal** | Xuất hiện các ký tự lạ dạng `` ở Serial Monitor. | Tốc độ Baud cấu hình trong code (`115200`) lệch với tốc độ đọc mặc định của VS Code (`9600`). | Thêm dòng `monitor_speed = 115200` vào file cấu hình `platformio.ini`. |
| **Kẹt cổng COM (Error 2)** | Hệ thống báo lỗi `Access is denied` khi bấm nạp code sang chip. | Tiến trình đọc Serial Monitor cũ vẫn đang ghim chặt cổng COM6, không cho trình nạp truy cập. | Bấm nút thùng rác để giải phóng Terminal hoặc rút cáp USB cắm lại để Windows reset cổng handle. |
| **Đứng hình thông số khoảng cách** | Dí vật cản lại gần hoặc bịt kín cảm biến nhưng thông số kẹt cứng ở `159cm - 160cm`. | Bộ lọc phần mềm trả về giá trị cũ liên tục khi cảm biến bị bịt kín (gây mất sóng, hàm `pulseIn` trả về 0). | Kiểm tra lại dây nguồn 5V (chân VIN) và điều chỉnh lại điều kiện biên của thuật toán lọc. |
| **Nhiễu chập chờn hệ thống** | Lúc đo được lúc không, thông số nhảy cóc không theo quy luật. | **Phần cứng:** Chân chip ESP32 tiếp xúc không chặt với board kiểm thử. | Ấn chặt chip và cố định lại chân cắm trên test board. |
| **Xung đột tên hàm `std::distance`** | Biên dịch thất bại kèm cảnh báo hệ thống liên quan đến cụm từ `std::distance`. | Đặt tên biến là `distance` trùng với hàm tính khoảng cách con trỏ có sẵn trong thư viện chuẩn C++ (`std::`). | Đổi tên biến cục bộ từ `distance` thành `sonarDistance` để trình biên dịch không bị nhận nhầm. |
| **Lỗi biên dịch "ảo" trong VS Code** | Khai báo lại biến đúng cú pháp nhưng tab `Problems` vẫn cứng đầu báo lỗi chưa khai báo. | File chỉnh sửa chưa được lưu (xuất hiện dấu chấm tròn trắng trên tab), khiến trình biên dịch ngầm liên tục đọc bản code cũ. | Nhấn tổ hợp phím `Ctrl + S` để lưu file nhằm cập nhật lại trạng thái code cho hệ thống. |
| **Không đổi được đuôi file (EBUSY)** | Xuất hiện thông báo lỗi hệ thống `Error: EBUSY: resource busy or locked` khi đổi đuôi `.log` sang `.csv`. | Tiến trình Serial Monitor của PlatformIO vẫn đang liên tục ghi dữ liệu thô vào file log, kích hoạt cơ chế khóa handle của Windows. | Bấm nút thùng rác (Kill Terminal) để đóng hoàn toàn cổng monitor, giải phóng file trước khi tiến hành đổi tên. |

### 3. Conclusion & System Status / Kết luận và trạng thái hệ thống

* **EN:** All identified issues have been successfully resolved. The baseline firmware is now fully operational, successfully streaming clean telemetry data formatted as CSV. The data pipeline has been verified via Microsoft Excel for seamless plotting. The `logs/` directory has been added to `.gitignore` to keep the repository clean. The system is ready for Week 4's web server interface development.
* **VN:** Toàn bộ các vấn đề phát sinh đã được xử lý triệt để. Hệ thống firmware nền tảng hiện đã hoạt động hoàn hảo, tự động xuất dữ liệu đo đạc sạch theo định dạng CSV và đã được kiểm chứng trơn tru trên Microsoft Excel để sẵn sàng vẽ đồ thị. Thư mục `logs/` cũng đã được đưa vào `.gitignore` để giữ kho code sạch sẽ. Hệ thống đã sẵn sàng cho giai đoạn phát triển giao diện Web Server ở Tuần 4.