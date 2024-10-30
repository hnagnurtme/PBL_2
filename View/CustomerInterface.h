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
#include "Model/Cart.h"
#include "Model/Customer.h"
#include <string>
using namespace std;
class CustomerInterface : public QWidget {
    Q_OBJECT

public:
    CustomerInterface(QWidget *parent = nullptr);
private slots:
    void showOverview();
    void showProducts();
    void filterProducts();
    void showCart();
    void showOrders();
    void showAccount();
    void showInvoice();
    void payment();
    void checkout();
    void cartOrigin();
signals:
private:
    string customerID ;
    Cart cart;
    QVector<QStringList> gioHang;
    QPushButton *showOverviewButton;
    QPushButton *showProductsButton;
    QPushButton *checkoutButton;
    QPushButton *showCartButton;
    QPushButton *showOrdersButton;
    QPushButton *showInvoicesButton;
    QPushButton *showAccountButton;
    QStackedWidget *stackWidget;
    QTextEdit *invoiceDisplay ;
    QPushButton *paymentButton;
    QPushButton *placeOrdersButton;
    QTableWidget *productTable;
    QTableWidget *cartTable;
    QTableWidget *ordersTable;
    QLabel *totalPrice;
    void addProducts(int row, bool fromCart);
    void deleteProducts(int row, bool fromCart);
    void addProductsData();
};
