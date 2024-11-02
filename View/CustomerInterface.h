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
#include <QDateEdit>
#include <QLabel>
#include <QString>
#include "Model/Cart.h"
#include "Model/Customer.h"
#include "Model/Invoice.h"
#include <string>
#include <QComboBox>
#include <QMessageBox>
using namespace std;
class CustomerInterface : public QWidget {
    Q_OBJECT

public:
    CustomerInterface(QWidget *parent = nullptr);
    void showMessage(QWidget *parent, QMessageBox::Icon iconType, const QString &message);
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
    void clearCart();
    void onDeliveryDateChanged();
    void onPaymentMethodChanged();
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
    QPushButton *clearCartButton;
    QPushButton *placeOrdersButton;
    QTableWidget *productTable;
    QTableWidget *cartTable;
    QTableWidget *ordersTable;
    QLabel *totalPrice;
    QLabel *dateLabel;
    QDateEdit *deliveryDateEdit;
    QComboBox *paymentMethodComboBox; 
    QLabel *paymentMethodLabel;
    void addProducts(int row, bool fromCart);
    void deleteProducts(int row, bool fromCart);
    void addProductsData();
};
