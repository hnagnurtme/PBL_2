#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QTextEdit>

class HomePageAdmin : public QWidget {
    Q_OBJECT

public:
    HomePageAdmin(QWidget *parent = nullptr);

private slots:
    void showOverview();
    void showEmployees();
    void showInvoices(); // Cập nhật tên phương thức
    void filterEmployees();
    void editRow(int row);
    void deleteRow(int row);

private:
    QTextEdit *hoaDon;
    QTableWidget *table;
    QLineEdit *searchLineEdit;
    QGroupBox *groupBox;
    void addEmployeeData();
    void addInvoiceData(); // Thêm hàm để thêm dữ liệu hóa đơn
};