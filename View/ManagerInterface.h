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
#include "Model/Manager.h"
#include "Model/Invoice.h"
#include "Controller/DataController.h"
#include "Controller/AppController.h"
#include <string>
#include <QComboBox>
#include <QMessageBox>
#include "Model/Customer.h"
using namespace std;
class ManagerInterface : public QWidget {
    Q_OBJECT

public:
    ManagerInterface(QWidget *parent = nullptr,const string &managerid ="");
    void showMessage(QWidget *parent, bool status, const QString &message);
    ~ManagerInterface();
    private slots:
    void showOverview();
    void showProducts();
    void filterProducts();
    void checkout();
    void showAccount();
    void showCustomers();
    void showInvoices();
    void filterCustomer();
    void filterInvoice();
signals:
private:
    Manager* manager;
    QPushButton *showOverviewButton;
    QPushButton *showProductsButton;
    QPushButton *checkoutButton;
    QPushButton *showCustomersButton;
    QPushButton *showInvoicesButton;
    QLineEdit *searchProductLine;
    QLineEdit *searchCustomerLine;
    QLineEdit *searchInvoiceLine;
    QPushButton *showAccountButton;
    QStackedWidget *stackWidget;
    QTextEdit *invoiceDisplay ;
    QTableWidget *productTable;
    QTableWidget *customersTable;
    QTableWidget *invoicesTable;
    QGroupBox *overviewBox;
    QGroupBox *managerInforBox;
    void addProductsData();
    void addCustomersData();
    void addInvoicesData();
    void addProducts(int row, bool fromCart);
    void deleteProducts(int row, bool fromCart);
    void deleteCustomer(int row);
    void showDetailsProducts(int row);
    void showInvoiceDetail(int row);
    DataController * dataController;
    AppController * appController;
};