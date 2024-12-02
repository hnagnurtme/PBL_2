#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QStackedWidget>
#include <QVector>
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
#include "Controller/DataController.h"
using namespace std;
class CustomerInterface : public QWidget {
    Q_OBJECT

public:
    CustomerInterface(QWidget *parent = nullptr,const string &customerid ="");
    void showMessage(QWidget *parent, bool status, const QString &message);
    void drawChart(const Vector<Pair<QString, double>>& data, const QString& title, const QString& xLabel, const QString& yLabel, QWidget* container);
    ~CustomerInterface();
private slots:
    void showOverview();
    void showProducts();
    void filterProducts();
    void showCart();
    void showOrders();
    void showAccount(bool change = false);
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
    QLineEdit *searchLineEdit;
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
    QGroupBox *customerInforBox;
    DataController *dataController;
    QGroupBox *diagramBox;
    QPushButton* applyButton;
    QPushButton* changeButton;
    void addProducts(int row, bool fromCart);
    void deleteProducts(int row, bool fromCart);
    void showDetailsProducts(int row);
    void addProductsData();
    void showInvoiceDetail(int row);
};