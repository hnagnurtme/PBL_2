#include "View/ManagerInterface.h"
#include "Model/Product.h"
#include "Model/Invoice.h"
#include "Model/Orders.h"
#include "Datastructures/Vector.h"
#include "Controller/DataController.h"
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
#include <QDir>
#include <QComboBox>
#include <memory>
#include <QDateEdit>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCore/QVector>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtGui/QPainter>

void ManagerInterface::showMessage(QWidget *parent, bool status, const QString &message) {
    QMessageBox messageBox(parent);
    QString icon_path = (status) ? "Resource/ICON/ICON7.png" : "Resource/ICON/ICON6.png";
    QPixmap originalPixmap(icon_path);
    QPixmap scaledPixmap = originalPixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    messageBox.setIconPixmap(scaledPixmap);
    messageBox.setText(message);
    messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    messageBox.setFixedSize(600, 400);
    messageBox.exec();
}

ManagerInterface::ManagerInterface(QWidget *parent,const string &managerid) : QWidget(parent) {
    
    DataController *managerData = new DataController();
    Manager newManager =  managerData->findManagerById(managerid);
    manager = new Manager(newManager);
    delete managerData;
    
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        setStyleSheet(style);
    }

    setFixedSize(1500, 800);
    setWindowTitle("Manager Homepage");

    showOverviewButton = new QPushButton("Overview", this);
    showProductsButton = new QPushButton("Products", this);
    showCustomersButton = new QPushButton("Customers", this);
    showInvoicesButton = new QPushButton("Invoices", this);
    showAccountButton = new QPushButton("Account", this);
    checkoutButton = new QPushButton("Logout", this);
    checkoutButton->setObjectName("cancelButton");

    connect(showOverviewButton, &QPushButton::clicked, this, &ManagerInterface::showOverview);
    connect(showProductsButton, &QPushButton::clicked, this, &ManagerInterface::showProducts);
    connect(showCustomersButton, &QPushButton::clicked, this, &ManagerInterface::showCustomers);
    connect(showInvoicesButton, &QPushButton::clicked, this, &ManagerInterface::showInvoices);
    connect(showAccountButton, &QPushButton::clicked, this, &ManagerInterface::showAccount);
    connect(checkoutButton, &QPushButton::clicked, this, &ManagerInterface::checkout);

    QWidget *menuWidget = new QWidget(this);
    QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);
    menuWidget->setFixedSize(200, 800);

    menuLayout->addSpacing(50);
    menuLayout->addWidget(showOverviewButton);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(showProductsButton);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(showCustomersButton);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(showInvoicesButton);
    menuLayout->addSpacing(100);
    menuLayout->addWidget(showAccountButton);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(checkoutButton);
    menuLayout->addSpacing(50);

    stackWidget = new QStackedWidget(this);
    QLineEdit *searchLineEdit = new QLineEdit(this);
    searchLineEdit->setFixedHeight(50);
    QIcon searchIcon("Resource/ICON/ICON5.png"); 
    searchLineEdit->addAction(searchIcon, QLineEdit::LeadingPosition);
    searchLineEdit->setPlaceholderText("Search by product name...");
    connect(searchLineEdit, &QLineEdit::textChanged, this, &ManagerInterface::filterProducts);

    productTable = new QTableWidget(5, 6, this);
    productTable->setHorizontalHeaderLabels({"No.", "Description", "Product ID", "Product Name", "Price", "Quantity", "Change"});

    QGroupBox *productGroupBox = new QGroupBox(this);
    QVBoxLayout *productLayout = new QVBoxLayout(productGroupBox);
    productLayout->addWidget(searchLineEdit);
    productLayout->addSpacing(20);
    productLayout->addWidget(productTable);
    productTable->setFixedSize(1250, 700);

    customersTable = new QTableWidget(0, 6, this);
    customersTable->setHorizontalHeaderLabels({"No.", "Product Name", "Product ID", "Price", "Quantity", "Action"});
    customersTable->setFixedSize(750, 650);

    
    invoicesTable = new QTableWidget(0,7,this);
    invoicesTable->setHorizontalHeaderLabels({"No.", "InvoiceID", "PlaceOrderDate", "DeliveryDate", "TotalAmount", "PaymentMehod","View"});
    invoicesTable->setFixedSize(950, 650);

    QGroupBox *ordersBox = new QGroupBox(this);
    QVBoxLayout *ordersLayout = new QVBoxLayout(ordersBox);
    ordersLayout->addWidget(invoicesTable);

    overviewBox = new QGroupBox(this);

    stackWidget->addWidget(productGroupBox);
    stackWidget->addWidget(overviewBox);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(menuWidget);
    layout->addWidget(stackWidget);
    mainLayout->addLayout(layout);
    setLayout(mainLayout);

    showProducts();
}


void ManagerInterface:: showOverview(){

}
void ManagerInterface::showProducts(){

}
void ManagerInterface::filterProducts(){

}
void ManagerInterface::checkout(){

}
void ManagerInterface::showAccount(){

}
void ManagerInterface::showCustomers(){

}
void ManagerInterface::showInvoices(){
    
}