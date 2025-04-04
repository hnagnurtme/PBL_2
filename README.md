# Hệ Thống Quản Lý Cửa Hàng Điện Thoại

## Giới Thiệu
Dự án "Hệ Thống Quản Lý Cửa Hàng Điện Thoại" là bài tập lập trình cơ sở (PBL2) được thực hiện bởi hai sinh viên Nguyễn Văn Trung Anh và Đoàn Kiều Ngân, thuộc lớp 23T_DT1, khóa 2023, Khoa Công nghệ Thông tin, Trường Đại học Bách Khoa, Đại học Đà Nẵng. Dự án được hoàn thành dưới sự hướng dẫn của TS. Đặng Hoài Phương vào tháng 1 năm 2025.

Hệ thống này là một nền tảng trực tuyến giúp quản lý cửa hàng điện thoại, hỗ trợ cả khách hàng và người quản lý. Mục tiêu là tối ưu hóa quy trình mua sắm, quản lý sản phẩm, đơn hàng và doanh thu, đồng thời nâng cao trải nghiệm người dùng trong bối cảnh thương mại điện tử ngày càng phát triển.

## Mục Tiêu Của Dự Án

### Đối Với Khách Hàng:
- Cung cấp một nền tảng tiện lợi để tìm kiếm thông tin, xem chi tiết sản phẩm và mua điện thoại trực tuyến.
- Giúp tiết kiệm thời gian và chi phí so với mua sắm truyền thống.

### Đối Với Người Quản Lý:
- Hỗ trợ quản lý thông tin sản phẩm, khách hàng, đơn hàng và doanh thu một cách hiệu quả.
- Mở rộng thị trường kinh doanh thông qua nền tảng trực tuyến.

## Mục Tiêu Kỹ Thuật
- Xây dựng một cơ sở dữ liệu có cấu trúc rõ ràng, dễ truy cập.
- Phát triển hệ thống với các chức năng toàn diện, đáp ứng nhu cầu của cả hai nhóm người dùng.

## Chức Năng Chính

### 1. Chức Năng Dành Cho Khách Hàng:
- **Đăng ký và đăng nhập**: Tạo tài khoản mới hoặc đăng nhập bằng email và mật khẩu.
- **Tìm kiếm sản phẩm**: Tìm kiếm điện thoại theo tên hoặc từ khóa.
- **Xem chi tiết sản phẩm**: Hiển thị thông tin như giá, số lượng, thông số kỹ thuật.
- **Quản lý giỏ hàng**: Thêm, giảm hoặc xóa sản phẩm trong giỏ.
- **Đặt hàng**: Chọn ngày giao hàng, phương thức thanh toán và hoàn tất đơn hàng.
- **Xem lịch sử đơn hàng**: Kiểm tra danh sách đơn hàng đã mua và chi tiết hóa đơn.
- **Quản lý tài khoản**: Xem và chỉnh sửa thông tin cá nhân (tên, email, số điện thoại, địa chỉ).
- **Thống kê cá nhân**: Xem tổng số đơn hàng, tổng chi tiêu và biểu đồ số tiền trên mỗi hóa đơn.

### 2. Chức Năng Dành Cho Quản Lý:
- **Đăng nhập**: Truy cập hệ thống với vai trò quản lý.
- **Quản lý sản phẩm**: Xem danh sách, thêm, xóa hoặc chỉnh sửa thông tin sản phẩm.
- **Quản lý khách hàng**: Xem danh sách khách hàng và xóa thông tin nếu cần.
- **Quản lý hóa đơn**: Xem toàn bộ hóa đơn và chi tiết từng hóa đơn.
- **Thống kê doanh thu**: Xem tổng doanh thu, số lượng sản phẩm bán được, và biểu đồ phân tích theo ngày hoặc khách hàng.
- **Quản lý tài khoản**: Xem và chỉnh sửa thông tin cá nhân của quản lý.

## Công Nghệ Sử Dụng

### Ngôn Ngữ Và Thư Viện
- **Ngôn ngữ lập trình**: C++
- **Thư viện giao diện**: Qt (dùng để thiết kế giao diện trực quan và thân thiện).

### Cấu Trúc Dữ Liệu
- **Template Vector**: Sử dụng danh sách liên kết đôi để quản lý dữ liệu linh hoạt.
- **Template Pair**: Quản lý các cặp dữ liệu (ví dụ: sản phẩm và số lượng).

### Thuật Toán
- **Sắp xếp**: Insertion Sort (đơn giản, hiệu quả cho danh sách nhỏ).
- **Tìm kiếm**: Binary Search (tối ưu tốc độ tìm kiếm trên dữ liệu đã sắp xếp).

### Lưu Trữ Dữ Liệu
- Dữ liệu được lưu trong các file CSV (ví dụ: ProductInformation.csv cho sản phẩm).
- Quản lý thông qua các phương thức đọc/ghi file.

## Tài Nguyên Hệ Thống
- **resource.qrc**: Quản lý tài nguyên như hình ảnh, biểu tượng.
- **style.qss**: Tệp định kiểu giao diện người dùng.
- **Makefile**: Tệp cấu hình để biên dịch và liên kết chương trình.

## Cấu Trúc Hệ Thống

### Các Lớp Chính
- **User**  
  - Thuộc tính: `userId`, `name`, `email`, `phone`, `password`.
  - Vai trò: Lớp cơ sở cho `Customer` và `Manager`.

- **Customer** (Kế thừa từ `User`)  
  - Thuộc tính bổ sung: `Cart* cart`, `Orders* orderHistory`.
  - Chức năng: Quản lý hoạt động mua sắm của khách hàng.

- **Manager** (Kế thừa từ `User`)  
  - Chức năng: Quản lý sản phẩm, khách hàng và doanh thu.

- **Product**  
  - Thuộc tính: `productId`, `name`, `category`, `price`, `stock`, `description`, `detail`, `brand`.
  - Vai trò: Lưu trữ thông tin sản phẩm.

- **Invoice**  
  - Thuộc tính: `invoiceId`, `customerId`, `products`, `invoiceDate`, `totalAmount`, `deliveryDate`, `paymentMethod`.
  - Vai trò: Quản lý thông tin hóa đơn.

- **Orders**  
  - Cấu trúc: `Vector<Invoice*>` (tập hợp các hóa đơn).
  - Chức năng: Hỗ trợ quản lý và xử lý hóa đơn.

### Các Lớp Hỗ Trợ
- **DataController**: Đọc/ghi dữ liệu từ file CSV.
- **AppController**: Xác thực, phân quyền và sắp xếp dữ liệu.

### Lớp Giao Diện:
- **LoginSignupInterface**: Đăng nhập/đăng ký.
- **CustomerInterface**: Giao diện khách hàng.
- **ManagerInterface**: Giao diện quản lý.
- **AddNewProductInterface**: Thêm sản phẩm mới.

## Kết Quả Thực Thi

### Giao Diện Khách Hàng:
- **Đăng nhập/đăng ký**: Hiển thị thông báo "Login successful" hoặc "Invalid email or password".
- **Danh sách sản phẩm**: Xem, tìm kiếm và thêm sản phẩm vào giỏ hàng.
- **Giỏ hàng**: Thêm, giảm, xóa sản phẩm; hiển thị thông báo nếu hết hàng.
- **Đặt hàng**: Chọn ngày giao, phương thức thanh toán, nhận thông báo "Mua hàng thành công".
- **Thống kê**: Biểu đồ cột hiển thị số tiền chi tiêu trên mỗi hóa đơn.

---

## Liên Hệ
Để biết thêm chi tiết hoặc hỗ trợ kỹ thuật, vui lòng liên hệ qua email: `support@bka.edu.vn`.
