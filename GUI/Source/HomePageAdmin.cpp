#include "GUI/Header/HomePageAdmin.h"
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

HomePageAdmin::HomePageAdmin(QWidget *parent) : QWidget(parent) {
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        this->setStyleSheet(style);
    }

    setFixedSize(1500, 800);
    setWindowTitle("Home Page Admin");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QVBoxLayout *menuLayout = new QVBoxLayout();
    QPushButton *btnTongQuan = new QPushButton("Tổng quan");
    QPushButton *btnNhanVien = new QPushButton("Quản lý nhân viên");
    QPushButton *btnHoaDon = new QPushButton("Quản lý hóa đơn");
    QPushButton *btnHangHoa = new QPushButton("Quản lý hàng hóa"); 
    
    btnTongQuan->setObjectName("btnTongQuan");
    btnNhanVien->setObjectName("btnNhanVien");
    btnHoaDon->setObjectName("btnHoaDon");
    btnHangHoa->setObjectName("btnHangHoa");

    connect(btnTongQuan, &QPushButton::clicked, this, &HomePageAdmin::showOverview);
    connect(btnNhanVien, &QPushButton::clicked, this, &HomePageAdmin::showEmployees);
    connect(btnHoaDon, &QPushButton::clicked, this, &HomePageAdmin::showInvoices); 

    menuLayout->addWidget(btnTongQuan);
    menuLayout->addWidget(btnNhanVien);
    menuLayout->addWidget(btnHoaDon); 
    menuLayout->addWidget(btnHangHoa);
    menuLayout->addStretch();

    groupBox = new QGroupBox("Quản lý nhân viên");
    groupBox->setFixedSize(1300,800);
    QVBoxLayout *groupLayout = new QVBoxLayout(groupBox);

    table = new QTableWidget(5, 9); // Cập nhật số cột cho bảng
    table->setHorizontalHeaderLabels({"STT", "Mã NV", "Họ tên", "Địa chỉ", "Email", "Tài Khoản", "Mật khẩu", "Chức vụ", "Hành động"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    searchLineEdit = new QLineEdit();
    searchLineEdit->setFixedHeight(50);
    searchLineEdit->setObjectName("inputArea");
    searchLineEdit->setPlaceholderText("Tìm kiếm theo tên nhân viên...");
    connect(searchLineEdit, &QLineEdit::textChanged, this, &HomePageAdmin::filterEmployees);

    groupLayout->addWidget(searchLineEdit); 
    groupLayout->addSpacing(20);
    groupLayout->addWidget(table);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addLayout(menuLayout);
    layout->addWidget(groupBox);

    mainLayout->addLayout(layout);
    setLayout(mainLayout);

    showEmployees();
}

void HomePageAdmin::addEmployeeData() {
    table->clearContents();
    table->setRowCount(100); // Thiết lập số hàng

    // Mở file để đọc dữ liệu
    QFile file("Data/UserInformation.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Không thể mở file UserInformation.txt");
        return;
    }

    QTextStream in(&file);
    QString line;
    int row = 0;

    // Đọc từng dòng từ file
    while (in.readLineInto(&line) && row < 100) {
        QStringList fields = line.split(',');

        if (fields.size() >= 8) {  // Đảm bảo có đủ trường dữ liệu
            table->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1)));  // STT
            table->setItem(row, 1, new QTableWidgetItem(fields[1].trimmed()));  // Mã NV
            table->setItem(row, 2, new QTableWidgetItem(fields[2].trimmed()));  // Họ tên
            table->setItem(row, 3, new QTableWidgetItem(fields[3].trimmed()));  // Địa chỉ
            table->setItem(row, 4, new QTableWidgetItem(fields[4].trimmed()));  // Email
            table->setItem(row, 5, new QTableWidgetItem(fields[5].trimmed()));  // Tài Khoản
            table->setItem(row, 6, new QTableWidgetItem(fields[6].trimmed()));  // Mật khẩu
            table->setItem(row, 7, new QTableWidgetItem(fields[7].trimmed()));  // Chức vụ

            // Thêm nút Sửa và Xóa
            QPushButton *btnEdit = new QPushButton("Sửa");
            btnEdit->setObjectName("confirmButton");
            connect(btnEdit, &QPushButton::clicked, [this, row]() { editRow(row); });

            QPushButton *btnDelete = new QPushButton("Xóa");
            btnDelete->setObjectName("cancelButton");
            connect(btnDelete, &QPushButton::clicked, [this, row]() { deleteRow(row); });

            QHBoxLayout *actionLayout = new QHBoxLayout();
            actionLayout->addWidget(btnEdit);
            actionLayout->addWidget(btnDelete);

            QWidget *actionWidget = new QWidget();
            actionWidget->setLayout(actionLayout);
            table->setCellWidget(row, 8, actionWidget);  // Đặt các nút vào cột hành động
            
            row++;  // Tăng số dòng đã thêm
        }
    }

    file.close();  // Đóng file
}

// Hiển thị hóa đơn
void HomePageAdmin::showInvoices() {
    table->clear();
    table->setRowCount(100);  // Giả sử có 100 hóa đơn
    table->setColumnCount(6);
    
    // Cập nhật số cột
    table->setHorizontalHeaderLabels({"Mã hóa đơn", "Mã nhân viên", "Tên nhân viên", "Mã khách hàng", "Ngày giao dịch", "Thành tiền"});
    addInvoiceData();  // Thêm dữ liệu hóa đơn

    groupBox->setVisible(true);
}

// Thêm dữ liệu hóa đơn
void HomePageAdmin::addInvoiceData() {
    table->clearContents();

    QFile file("Data/UserInformation.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Không thể mở file UserInformation.txt");
        return;
    }

    QTextStream in(&file);
    QString line;
    int row = 0;

    // Đọc từng dòng từ file
    while (in.readLineInto(&line) && row < 100) {
        QStringList fields = line.split(',');

        if (fields.size() >= 8) {  // Đảm bảo có đủ trường dữ liệu
            table->setItem(row, 0, new QTableWidgetItem("HD" + QString::number(row + 1)));  // Mã hóa đơn
            table->setItem(row, 1, new QTableWidgetItem(fields[1].trimmed())); // MNV
            table->setItem(row, 2, new QTableWidgetItem(fields[2].trimmed())); // Tên NV
            table->setItem(row, 3, new QTableWidgetItem("KH" + QString::number(row + 1)));  // Mã KH
            table->setItem(row, 4, new QTableWidgetItem("2024-10-" + QString::number(row % 30 + 1)));  // Ngày Giao dịch
            table->setItem(row, 5, new QTableWidgetItem(QString::number((row + 1) * 100000)));  // Thành tiền
            
            row++;  // Tăng số dòng đã thêm
        }
    }

    file.close();  // Đóng file
}

// Hiển thị nhân viên
void HomePageAdmin::showEmployees() {
    table->clear();
    table->setRowCount(100);
    table->setColumnCount(9); 
    int rowHeight = 70;  
    for (int row = 0; row < table->rowCount(); ++row) {
        table->setRowHeight(row, rowHeight);
    } // Cập nhật số cột
    table->setHorizontalHeaderLabels({"STT", "Mã NV", "Họ tên", "Địa chỉ", "Email", "Tài Khoản", "Mật khẩu", "Chức vụ", "Hành động"});
    addEmployeeData();  // Thêm dữ liệu nhân viên

    groupBox->setVisible(true);
}

void HomePageAdmin::showOverview() {
    table->clear();
    table->setRowCount(1);
    table->setColumnCount(1);
    table->setItem(0, 0, new QTableWidgetItem("Tổng quan dữ liệu..."));  // Nội dung tổng quan

    groupBox->setVisible(false);
}

void HomePageAdmin::filterEmployees() {
    QString searchTerm = searchLineEdit->text().trimmed();  // Loại bỏ khoảng trắng thừa
    if (searchTerm.isEmpty()) {
        // Hiển thị tất cả các hàng nếu không có từ khóa tìm kiếm
        for (int row = 0; row < table->rowCount(); ++row) {
            table->setRowHidden(row, false);
        }
        return;
    }

    // Lọc nhân viên dựa trên từ khóa tìm kiếm
    for (int row = 0; row < table->rowCount(); ++row) {
        QTableWidgetItem* item = table->item(row, 2);  // Lấy item của cột Họ tên (cột thứ 2)
        if (item) {  // Kiểm tra nếu item không phải nullptr
            bool matches = item->text().contains(searchTerm, Qt::CaseInsensitive);
            table->setRowHidden(row, !matches);  // Ẩn hoặc hiển thị hàng
        } else {
            table->setRowHidden(row, true);  // Nếu không có dữ liệu, ẩn hàng
        }
    }
}

void HomePageAdmin::editRow(int row) {
    QString newName = "Nguyễn Văn B"; // Thay đổi tên cho ví dụ
    table->item(row, 2)->setText(newName);
    QMessageBox::information(this, "Sửa", "Đã sửa thông tin của nhân viên: " + newName);
}

void HomePageAdmin::deleteRow(int row) {
    QString nameToRestore = table->item(row, 2)->text();
    table->removeRow(row);
    QMessageBox::information(this, "Xóa", "Đã xóa nhân viên: " + nameToRestore);
}
