#include "GUI/Header/GiaoDienKhachHang.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFile>
#include <QTextStream>
#include <QStackedWidget>
#include <QDate>
#include <QPushButton>
#include <QDir>

GiaoDienKhachHang::GiaoDienKhachHang(QWidget *parent) : QWidget(parent) {
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        this->setStyleSheet(style);
    }

    setFixedSize(1500, 800);
    setWindowTitle("Home Page Admin");

    QWidget *menuWidget = new QWidget();
    QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);
    menuWidget->setFixedSize(180, 800);
    menuWidget->move(0, 0);
    
    QPushButton *btnTongQuan = new QPushButton("Tổng quan");
    QPushButton *btnSanPham = new QPushButton("Sản phẩm");
    QPushButton *btnGioHang = new QPushButton("Giỏ hàng");
    QPushButton *btnDonHang = new QPushButton("Đơn hàng của bạn");
    QPushButton *btnTaiKhoan = new QPushButton("Thông tin tài khoản");
    QPushButton *btnDangXuat = new QPushButton("Đăng xuất");

    btnTongQuan->setObjectName("btnTongQuan");
    btnSanPham->setObjectName("btnNhanVien");
    btnGioHang->setObjectName("btnNhanVien");
    btnDonHang->setObjectName("btnNhanVien");
    btnTaiKhoan->setObjectName("confirmButton");
    btnDangXuat->setObjectName("cancelButton");

    connect(btnTongQuan, &QPushButton::clicked, this, &GiaoDienKhachHang::showOverview);
    connect(btnSanPham, &QPushButton::clicked, this, &GiaoDienKhachHang::showProducts);
    connect(btnGioHang, &QPushButton::clicked, this, &GiaoDienKhachHang::showGioHang);
    connect(btnDonHang, &QPushButton::clicked, this, &GiaoDienKhachHang::showDonHang);
    connect(btnTaiKhoan, &QPushButton::clicked, this, &GiaoDienKhachHang::showTaiKhoan);
    connect(btnDangXuat, &QPushButton::clicked, this, &GiaoDienKhachHang::DangXuat);

    menuLayout->addSpacing(50);
    menuLayout->addWidget(btnTongQuan);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(btnSanPham);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(btnGioHang);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(btnDonHang);
    menuLayout->addSpacing(100);
    menuLayout->addWidget(btnTaiKhoan);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(btnDangXuat);
    menuLayout->addSpacing(50);

    stackWidget = new QStackedWidget();
    
    QGroupBox *sanPhamGroupBox = new QGroupBox();
    QVBoxLayout *sanPhamLayout = new QVBoxLayout(sanPhamGroupBox);
    table = new QTableWidget(5, 6);
    table->setHorizontalHeaderLabels({"STT", "Hình ảnh", "Mã sản phẩm", "Tên sản phẩm", "Giá thành", "Hành động"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setColumnWidth(0, 30); 
    searchLineEdit = new QLineEdit();
    searchLineEdit->setFixedHeight(50);
    searchLineEdit->setPlaceholderText("Tìm kiếm theo tên sản phẩm...");
    connect(searchLineEdit, &QLineEdit::textChanged, this, &GiaoDienKhachHang::filterProducts);

    sanPhamLayout->addWidget(searchLineEdit);
    sanPhamLayout->addSpacing(20);
    sanPhamLayout->addWidget(table);

    QGroupBox *gioHangGroupBox = new QGroupBox();
    QVBoxLayout *gioHangLayout = new QVBoxLayout(gioHangGroupBox);
    QHBoxLayout *giaodienHoadon = new QHBoxLayout();
    QGroupBox *giaodienHoadonBox = new QGroupBox();
    giaodienHoadonBox->setLayout(giaodienHoadon);

    gioHangLayout->addWidget(giaodienHoadonBox);
    gioHangTable = new QTableWidget(0, 4);
    gioHangTable->setHorizontalHeaderLabels({"STT", "Tên sản phẩm", "Giá", "Số lượng"});
    giaodienHoadon->addWidget(gioHangTable);
    gioHangTable->setFixedSize(700, 500);
    xuatHoaDon = new QTextEdit("Hóa đơn");
    xuatHoaDon->setVisible(false);
    TongTien = new QLabel();
    datHang = new QPushButton("Đặt hàng");
    datHang->setObjectName("confirmButton");
    connect(datHang, &QPushButton::clicked, this, &GiaoDienKhachHang::showHoaDon);
    
    thanhToan = new QPushButton("Thanh toán");
    thanhToan->setObjectName("confirmButton");
    thanhToan->setVisible(false);
    connect(thanhToan, &QPushButton::clicked, this, &GiaoDienKhachHang::thanhtoan);
    QGroupBox *hoadonBox = new QGroupBox();
    QVBoxLayout *hoadonLayout = new QVBoxLayout();
    hoadonBox->setLayout(hoadonLayout);
    hoadonLayout->addWidget(xuatHoaDon);
    hoadonLayout->addWidget(thanhToan);
    giaodienHoadon->addWidget(hoadonBox);
    QHBoxLayout *thanhtoanLayout = new QHBoxLayout();
    thanhtoanLayout->addWidget(TongTien);
    thanhtoanLayout->addWidget(datHang);
    gioHangLayout->addWidget(giaodienHoadonBox);
    gioHangLayout->addLayout(thanhtoanLayout);


    QGroupBox *donHangGroupBox = new QGroupBox();
    QVBoxLayout *donHangLayout = new QVBoxLayout(donHangGroupBox);


    donhangTable = new QTableWidget(0, 5);
    donhangTable->setHorizontalHeaderLabels({"STT", "Ngày giao dịch", "Mã đơn", "Thành tiền", "Chi tiết"});
    donhangTable->setFixedSize(700, 800);
    chiTietHoaDon = new QTextEdit();
    chiTietHoaDon->setVisible(false); 

    donHangLayout->addWidget(donhangTable);
    donHangLayout->addWidget(chiTietHoaDon);

    stackWidget->addWidget(sanPhamGroupBox);
    stackWidget->addWidget(gioHangGroupBox);
    stackWidget->addWidget(donHangGroupBox);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(menuWidget);
    layout->addWidget(stackWidget);
    mainLayout->addLayout(layout);
    setLayout(mainLayout);
    showProducts();
}


void GiaoDienKhachHang::addProductsData() {
    table->clearContents();
    table->setRowCount(100);

    QFile file("Data/ProductInformation.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Không thể mở file ProductInformation.txt");
        return;
    }

    QTextStream in(&file);
    QString line;
    int row = 0;

    while (in.readLineInto(&line) && row < 100) {
        QStringList fields = line.split(',');

        if (fields.size() >= 5) {
            table->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1)));

            QLabel* imageLabel = new QLabel();
            QPixmap pixmap(fields[1].trimmed());
            if (!pixmap.isNull()) {
                imageLabel->setPixmap(pixmap.scaled(table->columnWidth(1), table->rowHeight(row), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
                imageLabel->setScaledContents(true);
                table->setCellWidget(row, 1, imageLabel);
            } else {
                table->setItem(row, 1, new QTableWidgetItem("Không có ảnh"));
            }
            table->setItem(row, 2, new QTableWidgetItem(fields[2].trimmed()));
            table->setItem(row, 3, new QTableWidgetItem(fields[3].trimmed()));
            table->setItem(row, 4, new QTableWidgetItem(fields[4].trimmed()));

            QPushButton *btnEdit = new QPushButton("Thêm");
            btnEdit->setObjectName("confirmButton");
            connect(btnEdit, &QPushButton::clicked, [this, row]() { addProducts(row,false); });

            QPushButton *btnDelete = new QPushButton("Xóa");
            btnDelete->setObjectName("cancelButton");
            connect(btnDelete, &QPushButton::clicked, [this, row]() { deleteProducts(row,false); });

            QHBoxLayout *actionLayout = new QHBoxLayout();
            actionLayout->addWidget(btnEdit);
            QWidget *actionWidget = new QWidget();
            actionWidget->setLayout(actionLayout);
            table->setCellWidget(row, 5, actionWidget);

            row++;
        }
    }

    file.close();
}

void GiaoDienKhachHang::showProducts() {
    table->clear();
    table->setRowCount(100);
    table->setColumnCount(6);

    int rowHeight = 100;
    for (int row = 0; row < table->rowCount(); ++row) {
        table->setRowHeight(row, rowHeight);
    }

    table->setHorizontalHeaderLabels({"STT", "Hình ảnh", "Mã sản phẩm", "Tên sản phẩm", "Giá thành", "Thêm vào giỏ hàng"});
    addProductsData();

    stackWidget->setCurrentIndex(0);
}

void GiaoDienKhachHang::showGioHang() {
    gioHangTable->clear();
    gioHangTable->setColumnCount(6);
    gioHangTable->setHorizontalHeaderLabels({"STT", "Tên sản phẩm", "Mã sản phẩm", "Giá", "Số lượng", "Hành động"});

    gioHangTable->setRowCount(gioHang.size());
    for (int i = 0; i < gioHang.size(); ++i) {
        gioHangTable->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        gioHangTable->setItem(i, 1, new QTableWidgetItem(gioHang[i][0]));
        gioHangTable->setItem(i, 2, new QTableWidgetItem(gioHang[i][1]));
        gioHangTable->setItem(i, 3, new QTableWidgetItem(gioHang[i][2]));
        gioHangTable->setItem(i, 4, new QTableWidgetItem(gioHang[i][3]));

        QPushButton *btnAdd = new QPushButton("+");
        btnAdd->setObjectName("confirmButton");
        connect(btnAdd, &QPushButton::clicked, [this, i]() { addProducts(i, true); });

        QPushButton *btnDelete = new QPushButton("-");
        btnDelete->setObjectName("cancelButton");
        connect(btnDelete, &QPushButton::clicked, [this, i]() { deleteProducts(i, true); });

        QWidget *actionWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionWidget);
        layout->addWidget(btnAdd);
        layout->addWidget(btnDelete);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        actionWidget->setLayout(layout);

        gioHangTable->setCellWidget(i, 5, actionWidget);
    }
    int tongTien = 0;
    for (const auto &sanPham : gioHang) {
        int gia = sanPham[2].toInt();
        int soLuong = sanPham[3].toInt();
        tongTien += gia * soLuong;
    }

    TongTien->setText("Tổng tiền: " + QString::number(tongTien) + " VND");
    for (int row = 0; row < gioHangTable->rowCount(); ++row) {
        gioHangTable->setRowHeight(row, 50);
    }

    stackWidget->setCurrentIndex(1);
}

void GiaoDienKhachHang::showOverview() {
    table->clear();
    table->setRowCount(1);
    table->setColumnCount(1);
    table->setItem(0, 0, new QTableWidgetItem("Tổng quan dữ liệu..."));

    groupBox->setVisible(true);
}

void GiaoDienKhachHang::filterProducts() {
    QString searchTerm = searchLineEdit->text().trimmed();
    if (searchTerm.isEmpty()) {
        for (int row = 0; row < table->rowCount(); ++row) {
            table->setRowHidden(row, false);
        }
        return;
    }

    for (int row = 0; row < table->rowCount(); ++row) {
        QTableWidgetItem* item = table->item(row, 3);
        if (item) {
            bool matches = item->text().contains(searchTerm, Qt::CaseInsensitive);
            table->setRowHidden(row, !matches);
        } else {
            table->setRowHidden(row, true);
        }
    }
}

void GiaoDienKhachHang::addProducts(int row, bool fromCart) {
    QString tenSanPham = fromCart ? gioHang[row][0] : table->item(row, 3)->text();
    QString giaSanPham = fromCart ? gioHang[row][1] : table->item(row, 4)->text();

    bool daCoTrongGioHang = false;
    for (auto &sanPham : gioHang) {
        if (sanPham[0] == tenSanPham) {
            int soLuong = sanPham[3].toInt();
            soLuong++;
            sanPham[3] = QString::number(soLuong);
            daCoTrongGioHang = true;
            break;
        }
    }

    if (!daCoTrongGioHang) {
        gioHang.append({tenSanPham, table->item(row, 2)->text(), giaSanPham, "1"});
    }
    if (stackWidget->currentIndex() == 1) {
        showGioHang();
    }
}

void GiaoDienKhachHang::deleteProducts(int row, bool fromCart) {
    if (gioHang.isEmpty()) {
        QMessageBox::warning(this, "Cảnh báo", "Giỏ hàng trống, không có sản phẩm nào để xóa.");
        return;
    }

    QString tenSanPham = fromCart ? gioHang[row][0] : table->item(row, 3)->text();
    bool found = false;

    for (int i = 0; i < gioHang.size(); ++i) {
        if (gioHang[i][0] == tenSanPham) {
            int soLuong = gioHang[i][3].toInt();
            if (soLuong > 1) {
                soLuong--;
                gioHang[i][3] = QString::number(soLuong);
            } else {
                gioHang.removeAt(i);
            }
            found = true;
            break;
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Cảnh báo", "Sản phẩm không có trong giỏ hàng.");
    }
    
    if (stackWidget->currentIndex() == 1) {
        showGioHang();
    }
}




void GiaoDienKhachHang::showTaiKhoan() {
}

void GiaoDienKhachHang::DangXuat() {
}

void GiaoDienKhachHang::showHoaDon() {
    QString tenCongTy = "Công Ty Nguyễn Trung Ánh";
    QString tenKhachHang = "Trịnh Giao Linh";
    QString maKhachHang = "KH001";

    // Tạo mã hóa đơn duy nhất bằng cách kết hợp với thời gian
    QString maHoaDon = QString("HD%1").arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));

    QString ngayThang = QDate::currentDate().toString("dd/MM/yyyy");

    QString hoaDonText;
    hoaDonText += "===================== " + tenCongTy + " ======================\n";
    hoaDonText += "Tên khách hàng: " + tenKhachHang + "\n";
    hoaDonText += "Mã khách hàng: " + maKhachHang + "\n";
    hoaDonText += "Mã hóa đơn: " + maHoaDon + "\n";
    hoaDonText += "Ngày: " + ngayThang + "\n";
    hoaDonText += "--------------------------------------------------------------\n";
    hoaDonText += QString("%1\t%2\t%3\t%4\n")
                    .arg("STT", -5)
                    .arg("Tên sản phẩm", -20)
                    .arg("Giá", -10)
                    .arg("Số lượng", -10);
    hoaDonText += "--------------------------------------------------------------\n";

    int tongTien = 0;

    for (int i = 0; i < gioHang.size(); ++i) {
        QString tenSanPham = gioHang[i][0];
        int gia = gioHang[i][2].toInt();
        int soLuong = gioHang[i][3].toInt();
        int thanhTien = gia * soLuong;
        tongTien += thanhTien;

        hoaDonText += QString("%1\t%2\t%3\t%4\n")
                        .arg(i + 1, -5)
                        .arg(tenSanPham, -20)
                        .arg(gia, -10)
                        .arg(soLuong, -10);
    }

    hoaDonText += "--------------------------------------------------------------\n";
    hoaDonText += "                                                    Tổng tiền: " + QString::number(tongTien) + " VND\n";
    hoaDonText += "==============================================================\n";
    
    xuatHoaDon->setVisible(true);
    xuatHoaDon->setPlainText(hoaDonText);
    thanhToan->setVisible(true);
    datHang->setVisible(false);

    // Đường dẫn đến thư mục lưu hóa đơn
    QString dirPath = "Data/HoaDon";
    QDir dir;

    // Kiểm tra và tạo thư mục nếu chưa tồn tại
    if (!dir.exists(dirPath)) {
        dir.mkpath(dirPath);
    }

    // Tên file chứa hóa đơn của khách hàng
    QString tenFile = dirPath + "/HoaDon_" + maKhachHang + ".txt";
    
    // Mở file để ghi (append)
    QFile file(tenFile);
    if (file.open(QIODevice::Append | QIODevice::Text)) { // Mở file ở chế độ append
        QTextStream out(&file);
        out << hoaDonText; // Ghi thêm hóa đơn vào file
        file.close();
    } else {
        qDebug() << "Không thể mở file để ghi: " << file.errorString();
    }

    // Lưu thông tin đơn hàng vào danh sách donHang
    donHang.append({{"ngayGiaoDich", ngayThang}, {"maDon", maHoaDon}, {"thanhTien", QString::number(tongTien)}});
}


void GiaoDienKhachHang::thanhtoan() {
    QMessageBox::information(this, "Đặt hàng", "Thanh toán thành công ");
    xuatHoaDon->clear();
    gioHang.clear();
    gioHangTable->clear();
    GiaoDienKhachHang::showProducts();
    xuatHoaDon->setVisible(false);
    thanhToan->setVisible(false);
    datHang->setVisible(true);
}

void GiaoDienKhachHang::loadDonHangFromFile() {
    QString dirPath = "Data/HoaDon"; // Đường dẫn tới thư mục chứa file hóa đơn
    QDir dir(dirPath);
    QStringList fileList = dir.entryList(QStringList() << "*.txt", QDir::Files); // Tìm tất cả file có định dạng .txt

    donhangTable->setRowCount(0); // Đặt lại số hàng trong bảng trước khi thêm dữ liệu
    QSet<QString> uniqueInvoiceIDs; // Bộ lưu trữ mã hóa đơn duy nhất

    for (const QString &fileName : fileList) {
        QString filePath = dirPath + "/" + fileName; // Đường dẫn đầy đủ tới file
        QFile file(filePath);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString line;

            // Đọc thông tin hóa đơn
            QString customerName, customerID, invoiceID, date;
            double total = 0.0; // Tổng tiền

            // Đọc 4 dòng đầu tiên chứa thông tin khách hàng
            for (int i = 0; i < 4; ++i) {
                in.readLineInto(&line);
                if (i == 0) {
                    customerName = line.mid(line.indexOf(':') + 1).trimmed(); // Tên khách hàng
                } else if (i == 1) {
                    customerID = line.mid(line.indexOf(':') + 1).trimmed(); // Mã khách hàng
                } else if (i == 2) {
                    invoiceID = line.mid(line.indexOf(':') + 1).trimmed(); // Mã hóa đơn
                } else if (i == 3) {
                    date = line.mid(line.indexOf(':') + 1).trimmed(); // Ngày
                }
            }

            // Kiểm tra xem mã hóa đơn đã được thêm vào bảng chưa
            if (uniqueInvoiceIDs.contains(invoiceID)) {
                file.close();
                continue; // Bỏ qua nếu hóa đơn đã tồn tại
            }

            uniqueInvoiceIDs.insert(invoiceID); // Thêm mã hóa đơn vào bộ lưu trữ

            // Thêm thông tin hóa đơn vào bảng
            int currentRow = donhangTable->rowCount();
            donhangTable->insertRow(currentRow);
            donhangTable->setItem(currentRow, 0, new QTableWidgetItem(QString::number(currentRow + 1))); // STT
            donhangTable->setItem(currentRow, 1, new QTableWidgetItem(date)); // Ngày giao dịch
            donhangTable->setItem(currentRow, 2, new QTableWidgetItem(invoiceID)); // Mã đơn
            donhangTable->setItem(currentRow, 3, new QTableWidgetItem(QString::number(total, 'f', 2))); // Thành tiền

            // Tạo nút bấm để hiện chi tiết hóa đơn
            QPushButton *detailButton = new QPushButton("Chi tiết");
            connect(detailButton, &QPushButton::clicked, [=]() {
                showHoaDonDetails(invoiceID); // Hiển thị chi tiết hóa đơn với mã đơn
            });
            donhangTable->setCellWidget(currentRow, 4, detailButton); // Chi tiết

            // Đọc dòng tiêu đề sản phẩm
            in.readLineInto(&line); // Bỏ qua dòng tiêu đề
            in.readLineInto(&line); // Bỏ qua dòng gạch ngang

            // Đọc dữ liệu sản phẩm
            while (in.readLineInto(&line)) {
                QStringList data = line.split('\t'); // Tách dữ liệu theo tab

                if (data.size() < 4) {
                    continue; // Bỏ qua nếu không đủ dữ liệu
                }

                QString productName = data.at(1); // Tên sản phẩm
                double price = data.at(2).toDouble(); // Giá
                int quantity = data.at(3).toInt(); // Số lượng
                total += price * quantity; // Cộng dồn tổng tiền

                // Thêm dữ liệu sản phẩm vào bảng
                donhangTable->insertRow(donhangTable->rowCount());
                int productRow = donhangTable->rowCount() - 1;
                donhangTable->setItem(productRow, 0, new QTableWidgetItem(QString::number(productRow))); // STT
                donhangTable->setItem(productRow, 1, new QTableWidgetItem(productName)); // Tên sản phẩm
                donhangTable->setItem(productRow, 2, new QTableWidgetItem(QString::number(price, 'f', 2))); // Giá
                donhangTable->setItem(productRow, 3, new QTableWidgetItem(QString::number(quantity))); // Số lượng
            }

            // Thêm tổng tiền vào bảng
            donhangTable->insertRow(donhangTable->rowCount());
            int totalRow = donhangTable->rowCount() - 1;
            donhangTable->setItem(totalRow, 1, new QTableWidgetItem("Tổng tiền:")); // Tổng tiền
            donhangTable->setItem(totalRow, 2, new QTableWidgetItem(QString::number(total, 'f', 2))); // Hiển thị tổng tiền

            file.close(); // Đóng file sau khi đọc xong
        } else {
            qDebug() << "Không thể mở file: " << file.errorString(); // In thông báo lỗi nếu không mở được file
        }
    }
}



void GiaoDienKhachHang::setupConnections() {
    connect(donhangTable, &QTableWidget::cellClicked, this, &GiaoDienKhachHang::onCellClicked);
}

void GiaoDienKhachHang::showDonHang() {
    donhangTable->clear();
    donhangTable->setColumnCount(5);
    donhangTable->setHorizontalHeaderLabels({"STT", "Ngày giao dịch", "Mã đơn", "Thành tiền", "Chi tiết"});

    loadDonHangFromFile();

    for (int row = 0; row < donhangTable->rowCount(); ++row) {
        QPushButton *btnDetail = new QPushButton("Chi tiết");
        btnDetail->setObjectName("confirmButton");
        donhangTable->setCellWidget(row, 4, btnDetail);

        connect(btnDetail, &QPushButton::clicked, [this, row]() {
            QString maDonHang = donhangTable->item(row, 2)->text();
            showHoaDonDetails(maDonHang);  
        });
    }

    for (int row = 0; row < donhangTable->rowCount(); ++row) {
        donhangTable->setRowHeight(row, 50);
    }

    stackWidget->setCurrentIndex(2);
}



void GiaoDienKhachHang::onCellClicked(int row, int column) {
    if (column == 4) {
        QString maDonHang = donhangTable->item(row, 2)->text();
        showHoaDonDetails(maDonHang);  // Hiển thị chi tiết hóa đơn
    }
}

QString GiaoDienKhachHang::getHoaDonDetails(const QString &maDonHang) {
    QString dirPath = "Data/HoaDon";
    QString filePath = dirPath + "/HoaDon_" + maDonHang + ".txt";
    QFile file(filePath);
    QString hoaDonText;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            hoaDonText += in.readLine() + "\n";
        }
        file.close();
    } else {
        qDebug() << "Không thể mở file hóa đơn: " << file.errorString();
        hoaDonText = "Không tìm thấy hóa đơn.";
    }

    return hoaDonText;
}

void GiaoDienKhachHang::showHoaDonDetails(const QString &maDonHang) {
    QString chiTiet = getHoaDonDetails(maDonHang);
    xuatHoaDon->setPlainText(chiTiet);
    xuatHoaDon->setVisible(true);
}
