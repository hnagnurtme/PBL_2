#pragma once

#include <QMap>
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QStackedWidget>
#include <QVector>
#include <QStringList>
#include <QTextEdit>
#include <QLabel>
#include <QString>

class GiaoDienKhachHang : public QWidget {
    Q_OBJECT

public:
    GiaoDienKhachHang(QWidget *parent = nullptr);
    void loadDonHangFromFile();
    void setupConnections();
    void showHoaDonDetails(const QString &maDonHang); 

private slots:
    void showOverview();
    void showProducts();
    void filterProducts();
    void showGioHang();
    void showDonHang();
    void showTaiKhoan();
    void DangXuat();
    void showHoaDon(); 
    void thanhtoan();
    void onCellClicked(int row, int column);

signals:
    void productAdded(const QString &productName);
    void productDeleted(const QString &productName);
    void filterClicked(const int row);
    void detailRequested(const QString &maDonHang);

private:
    QList<QMap<QString, QString>> donHang;
    QPushButton *datHang;
    QPushButton *thanhToan;
    QTextEdit *xuatHoaDon;
    QTextEdit *chiTietHoaDon;
    QTableWidget *gioHangTable;
    QStackedWidget *stackWidget;
    QTableWidget *table;
    QTableWidget *donhangTable;
    QLineEdit *searchLineEdit;
    QGroupBox *groupBox;
    void addProductsData();
    QVector<QStringList> gioHang;
    void addProducts(int row, bool fromCart);
    void deleteProducts(int row, bool fromCart);
    QString getHoaDonDetails(const QString &maDonHang);
    QLabel *TongTien;
};
