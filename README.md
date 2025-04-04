# Hệ Thống Quản Lý Cửa Hàng Điện Thoại

## Giới Thiệu
Dự án "Hệ Thống Quản Lý Cửa Hàng Điện Thoại" là một nền tảng trực tuyến giúp quản lý cửa hàng điện thoại, hỗ trợ cả khách hàng và người quản lý. Mục tiêu là tối ưu hóa quy trình mua sắm, quản lý sản phẩm, đơn hàng và doanh thu, đồng thời nâng cao trải nghiệm người dùng trong bối cảnh thương mại điện tử ngày càng phát triển.
**Grade: 9.7/10**
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
- ![image](https://github.com/user-attachments/assets/379f71e9-e366-455f-937e-597bb9072267)

- **Danh sách sản phẩm**: Xem, tìm kiếm và thêm sản phẩm vào giỏ hàng.
- ![image](https://github.com/user-attachments/assets/bd2cc368-7233-4cce-b274-604e7592da95)

- ![image](https://github.com/user-attachments/assets/49b02eb9-9e6b-43a3-91b5-174fa7b60144)



- **Giỏ hàng**: Thêm, giảm, xóa sản phẩm; hiển thị thông báo nếu hết hàng.

- ![image](https://github.com/user-attachments/assets/ba4f5753-da99-4467-b29a-4567e7737ac5)
- 
- ![image](https://github.com/user-attachments/assets/c194875b-207d-4f01-b947-1a29b8e39b4a)

- **Đặt hàng**: Chọn ngày giao, phương thức thanh toán, nhận thông báo "Mua hàng thành công".
- ![image](https://github.com/user-attachments/assets/fa438e7b-03e0-4dd2-a683-620cff6c8afd)

- ![image](https://github.com/user-attachments/assets/6717927f-e434-4050-8e9d-99ce8b397bda)

- ![image](https://github.com/user-attachments/assets/46812a0b-4bcf-411a-bfe6-fdb480e3ca86)

- **Chỉnh sửa**: Thêm , sửa xoá sản phẩm.
- ![image](https://github.com/user-attachments/assets/641c3439-6af7-4c46-a081-737b55d16100)

- ![image](https://github.com/user-attachments/assets/25d25010-c1a6-46ed-ad1e-f4cdbbeebf4b)

- ![image](https://github.com/user-attachments/assets/0dae823b-2e3c-4da7-8916-accf158754ec)

- ![image](https://github.com/user-attachments/assets/701fd47c-ed20-44c6-8e16-37e0c5f2fa30)

- **Thống kê**: Biểu đồ cột hiển thị số tiền chi tiêu trên mỗi hóa đơn.

- ![image](https://github.com/user-attachments/assets/dd386c4b-7f60-454f-bd61-593c31bca6c7)

- ![image](https://github.com/user-attachments/assets/a34a2aad-3cd8-49ee-ad83-2f87a2dc3f2b)

- ![image](https://github.com/user-attachments/assets/07102841-d454-4fec-922e-134484f0abca)

- ![image](https://github.com/user-attachments/assets/102be7ac-741d-4618-bb47-54b2e78ddc9f)

- ![image](https://github.com/user-attachments/assets/85181b55-8f26-409b-934e-659477e1a6a3)

- ![image](https://github.com/user-attachments/assets/2bc4dbed-c0c2-4753-9595-1096bbfab1fd)

- ![image](https://github.com/user-attachments/assets/97abb9a5-7bba-4a0f-abd7-1e18c0075a13)

---

## Liên Hệ
Để biết thêm chi tiết hoặc hỗ trợ kỹ thuật, vui lòng liên hệ qua email: `102230174@sv1.dut.udn.vn`.

## Tài Liệu Tham Khảo
- **Video Demo PBL2**: [DEMO.mp4](https://drive.google.com/file/d/1REmA7QyUNxuU0Mn5X1wPcLwzD2soVSVG/view?usp=drive_link)
- **Báo cáo PBL2**: [BAOCAO-FINAL.pdf](https://github.com/user-attachments/files/18299404/BAOCAO-FINAL.pdf)

