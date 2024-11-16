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
#include "Model/Customer.h"
using namespace std;
class CustomerInterface : public QWidget {
    Q_OBJECT

public:
    CustomerInterface(QWidget *parent = nullptr,const string &customerid ="");
    void showMessage(QWidget *parent, bool status, const QString &message);
    ~CustomerInterface();
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
    void ordersOrigin();
    void clearCart();
    void onDeliveryDateChanged();
    void onPaymentMethodChanged();
    
signals:
private:
    Customer* customer;
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
    QGroupBox *overviewBox;
    void addProducts(int row, bool fromCart);
    void deleteProducts(int row, bool fromCart);
    void showDetailsProducts(int row);
    void addProductsData();
    void showInvoiceDetail(int row);
};
