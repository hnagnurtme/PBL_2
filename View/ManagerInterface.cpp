#include "View/ManagerInterface.h"
#include "View/AddNewProduct.h"
#include "Model/Product.h"
#include "Model/Invoice.h"
#include "Model/Orders.h"
#include "Datastructures/Vector.h"
#include "Controller/DataController.h"
#include "Controller/AppController.h"
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
#include <QLineSeries>
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

ManagerInterface:: ~ManagerInterface(){
    delete manager;
    delete appController;
    delete dataController;
}

ManagerInterface::ManagerInterface(QWidget *parent,const string &managerid) : QWidget(parent) {
    dataController = new DataController();
    Manager newManager =  dataController->findManagerById(managerid);
    manager = new Manager(newManager);
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        setStyleSheet(style);
    }
    setFixedSize(1500, 800);
    setWindowTitle("Manager Homepage");

    showOverviewButton = new QPushButton(" Overview", this);
    showProductsButton = new QPushButton(" Products", this);
    showCustomersButton = new QPushButton(" Customers", this);
    showInvoicesButton = new QPushButton(" Invoices", this);
    showAccountButton = new QPushButton(" Account", this);
    checkoutButton = new QPushButton(" Logout", this);
    QIcon icon1 = QIcon(":/icon22");
    QIcon icon2 = QIcon(":/icon23");
    QIcon icon3 = QIcon(":/icon27");
    QIcon icon4 = QIcon(":/icon28");
    QIcon icon5 = QIcon(":/icon24");
    QIcon icon6 = QIcon(":/icon25");
    showOverviewButton->setIcon(icon1);
    showOverviewButton->setIconSize(QSize(45, 45));
    showProductsButton->setIcon(icon2);
    showProductsButton->setIconSize(QSize(45, 45));
    showCustomersButton->setIcon(icon3);
    showCustomersButton->setIconSize(QSize(45, 45));
    showInvoicesButton->setIcon(icon4);
    showInvoicesButton->setIconSize(QSize(45, 45));
    showAccountButton->setIcon(icon5);
    showAccountButton->setIconSize(QSize(45, 45));
    checkoutButton->setIcon(icon6);
    checkoutButton->setIconSize(QSize(45, 45));
    showOverviewButton->setFixedSize(180, 70);
    showProductsButton->setFixedSize(180, 70);
    showCustomersButton->setFixedSize(180, 70);
    showInvoicesButton->setFixedSize(180, 70);
    showAccountButton->setFixedSize(180, 70);
    checkoutButton->setFixedSize(180, 70);

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
    searchProductLine = new QLineEdit(this);
    searchProductLine->setFixedHeight(50);
    QIcon searchIcon("Resource/ICON/ICON5.png"); 
    searchProductLine->addAction(searchIcon, QLineEdit::LeadingPosition);
    searchProductLine->setPlaceholderText("Search by product name...");
    connect(searchProductLine, &QLineEdit::textChanged, this, &ManagerInterface::filterProducts);
    searchCustomerLine = new QLineEdit(this);
    searchCustomerLine->setFixedHeight(50);
    searchCustomerLine->addAction(searchIcon, QLineEdit::LeadingPosition);
    searchCustomerLine->setPlaceholderText("Search by customer name...");
    connect(searchCustomerLine, &QLineEdit::textChanged, this, &ManagerInterface::filterCustomer);
    searchInvoiceLine = new QLineEdit(this);
    searchInvoiceLine->setFixedHeight(50);
    searchInvoiceLine->addAction(searchIcon, QLineEdit::LeadingPosition);
    searchInvoiceLine->setPlaceholderText("Search by placeorder date...");
    connect(searchInvoiceLine, &QLineEdit::textChanged, this, &ManagerInterface::filterInvoice);

    addNewProductButton = new QPushButton(this);
    addNewProductButton->setText(" Add New Product");
    QIcon addIcon("Resource/ICON/ICON4.png"); 
    addNewProductButton->setIcon(addIcon);
    addNewProductButton->setIconSize(QSize(35, 35));
    connect(addNewProductButton, &QPushButton::clicked, this,&ManagerInterface::addNewProduct);

    productTable = new QTableWidget(5, 6, this);
    productTable->setHorizontalHeaderLabels({"No.", "Description", "Product ID", "Product Name", "Price", "Quantity", "Change"});

    QGroupBox *productGroupBox = new QGroupBox(this);
    QVBoxLayout *productLayout = new QVBoxLayout(productGroupBox);
    productLayout->addWidget(searchProductLine);
    productLayout->addWidget(addNewProductButton);
    productLayout->addWidget(productTable);
    productTable->setFixedSize(1250, 700);

    customersTable = new QTableWidget(0, 7, this);
    customersTable->setHorizontalHeaderLabels({"No.", "CustomerID", "Name", "Email", "Phone", "Address","Total Price"});

    QGroupBox *customersGroupBox = new QGroupBox(this);
    QVBoxLayout *customersLayout = new QVBoxLayout(customersGroupBox);
    customersLayout->addWidget(searchCustomerLine);
    customersLayout->addSpacing(20);
    customersLayout->addWidget(customersTable);
    customersTable->setFixedSize(1250,700);
    
    invoicesTable = new QTableWidget(0,7,this);
    invoicesTable->setHorizontalHeaderLabels({"No.", "InvoiceID", "PlaceOrderDate", "DeliveryDate", "TotalAmount", "PaymentMehod","View"});

    QGroupBox *invoicesGroupBox = new QGroupBox(this);
    QVBoxLayout *invoicesLayout = new QVBoxLayout(invoicesGroupBox);
    invoicesLayout->addWidget(searchInvoiceLine);
    invoicesLayout->addSpacing(20);
    invoicesLayout->addWidget(invoicesTable);
    invoicesTable->setFixedSize(1250, 700);
    
    overviewBox = new QGroupBox(this);
    managerInforBox = new QGroupBox(this);

    stackWidget->addWidget(overviewBox);
    stackWidget->addWidget(productGroupBox);
    stackWidget->addWidget(customersGroupBox);
    stackWidget->addWidget(invoicesGroupBox);
    stackWidget->addWidget(managerInforBox);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(menuWidget);
    layout->addWidget(stackWidget);
    mainLayout->addLayout(layout);
    setLayout(mainLayout);
    showOverview();
}

void ManagerInterface::showProducts(){
    productTable->clearContents();
    productTable->setRowCount(100);
    productTable->setColumnCount(7);

    int rowHeight = 100;
    for (int row = 0; row < productTable->rowCount(); ++row) {
        productTable->setRowHeight(row, rowHeight);
    }
    int columnWigth = 150;
    for (int column = 0; column < productTable->columnCount(); ++column) {
        productTable->setColumnWidth(column, columnWigth);
    }
    productTable->setColumnWidth(6,200);
    productTable->setColumnWidth(3,300);
    productTable->setColumnWidth(0,100);
    productTable->setHorizontalHeaderLabels({"No.", "Description", "Product ID", "Product Name", "Price", "Quantity", "Action"});
    addProductsData();
    stackWidget->setCurrentIndex(1);
}

void ManagerInterface::checkout(){
    this->close();
}

void ManagerInterface::showAccount(bool change ) {
    QLayout* oldLayout = managerInforBox->layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->deleteLater();
            }
            delete item;
        }
        delete oldLayout;
    }

    string name = manager->getName();
    string email = manager->getEmail();
    string address = manager->getAddress();
    string phone = manager->getPhone();
    string password = manager->getPassword();

    QLabel* nameLabelText = new QLabel("Name: ");
    QLabel* nameLabel = new QLabel(QString::fromStdString(name));
    QLineEdit* nameEdit = new QLineEdit(QString::fromStdString(name));
    
    QLabel* emailLabelText = new QLabel("Email: ");
    QLabel* emailLabel = new QLabel(QString::fromStdString(email));
    QLineEdit* emailEdit = new QLineEdit(QString::fromStdString(email));
    
    QLabel* addressLabelText = new QLabel("Address: ");
    QLabel* addressLabel = new QLabel(QString::fromStdString(address));
    QLineEdit* addressEdit = new QLineEdit(QString::fromStdString(address));
    
    QLabel* phoneLabelText = new QLabel("Phone: ");
    QLabel* phoneLabel = new QLabel(QString::fromStdString(phone));
    QLineEdit* phoneEdit = new QLineEdit(QString::fromStdString(phone));
    
    QLabel* passwordLabelText = new QLabel("Password: ");
    QLabel* passwordLabel = new QLabel(QString::fromStdString(password));
    QLineEdit* passwordEdit = new QLineEdit(QString::fromStdString(password));

    nameLabelText->setObjectName("titleLabel");
    nameLabel->setObjectName("inputArea");
    nameEdit->setObjectName("inputArea");

    emailLabelText->setObjectName("titleLabel");
    emailLabel->setObjectName("inputArea");
    emailEdit->setObjectName("inputArea");

    addressLabelText->setObjectName("titleLabel");
    addressLabel->setObjectName("inputArea");
    addressEdit->setObjectName("inputArea");

    phoneLabelText->setObjectName("titleLabel");
    phoneLabel->setObjectName("inputArea");
    phoneEdit->setObjectName("inputArea");

    passwordLabelText->setObjectName("titleLabel");
    passwordLabel->setObjectName("inputArea");
    passwordEdit->setObjectName("inputArea");

    QGridLayout* layout = new QGridLayout(managerInforBox);
    managerInforBox->setFixedSize(900, 300);

    layout->addWidget(nameLabelText, 0, 0);
    layout->addWidget(nameLabel, 0, 1);
    layout->addWidget(nameEdit, 0, 2);
    
    layout->addWidget(emailLabelText, 1, 0);
    layout->addWidget(emailLabel, 1, 1);
    layout->addWidget(emailEdit, 1, 2);
    
    layout->addWidget(addressLabelText, 2, 0);
    layout->addWidget(addressLabel, 2, 1);
    layout->addWidget(addressEdit, 2, 2);
    
    layout->addWidget(phoneLabelText, 3, 0);
    layout->addWidget(phoneLabel, 3, 1);
    layout->addWidget(phoneEdit, 3, 2);
    
    layout->addWidget(passwordLabelText, 4, 0);
    layout->addWidget(passwordLabel, 4, 1);
    layout->addWidget(passwordEdit, 4, 2);

    changeButton = new QPushButton("Change");
    applyButton = new QPushButton("Apply Change");
    applyButton->setVisible(false);

    connect(changeButton, &QPushButton::clicked, [this, nameEdit, emailEdit, addressEdit, phoneEdit, passwordEdit]() {
        nameEdit->setVisible(true);
        emailEdit->setVisible(true);
        addressEdit->setVisible(true);
        phoneEdit->setVisible(true);
        passwordEdit->setVisible(true);
        applyButton->setVisible(true);
        changeButton->setVisible(false);
    });
    
    connect(applyButton, &QPushButton::clicked, [this, nameEdit, emailEdit, addressEdit, phoneEdit, passwordEdit]() {
        manager->setName(nameEdit->text().toStdString());
        manager->setEmail(emailEdit->text().toStdString());
        manager->setAddress(addressEdit->text().toStdString());
        manager->setPhone(phoneEdit->text().toStdString());
        manager->setPassword(passwordEdit->text().toStdString());
        dataController->updateManager(*manager);
        showAccount(false);
    });

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(changeButton);
    buttonLayout->addWidget(applyButton);
    layout->addLayout(buttonLayout, 5, 0, 1, 3);
    managerInforBox->setLayout(layout);
    managerInforBox->show();
    stackWidget->setCurrentIndex(4);

    if (!change) {
        nameEdit->setVisible(false);
        emailEdit->setVisible(false);
        addressEdit->setVisible(false);
        phoneEdit->setVisible(false);
        passwordEdit->setVisible(false);
    }

    stackWidget->setCurrentIndex(4);
}

void ManagerInterface::showCustomers(){
    customersTable->clear();
    customersTable->setRowCount(100);
    customersTable->setColumnCount(8);

    int rowHeight = 100;
    for (int row = 0; row < customersTable->rowCount(); ++row) {
        customersTable->setRowHeight(row, rowHeight);
    }
    int columnWigth = 150;
    for (int column = 0; column < customersTable->columnCount(); ++column) {
        customersTable->setColumnWidth(column, columnWigth);
    }
    customersTable->setColumnWidth(6,100);
    customersTable->setColumnWidth(5,300);
    customersTable->setColumnWidth(3,200);
    customersTable->setColumnWidth(0,50);
    customersTable->setHorizontalHeaderLabels({"No.", "CustomerID", "Name", "Email", "Phone", "Address","Total Price","Action"});
    addCustomersData();

    stackWidget->setCurrentIndex(2);
}

void ManagerInterface::showInvoices(){
    invoicesTable->clear();
    invoicesTable->setRowCount(100);
    invoicesTable->setColumnCount(7);

    int rowHeight = 100;
    for (int row = 0; row < invoicesTable->rowCount(); ++row) {
        invoicesTable->setRowHeight(row, rowHeight);
    }
    int columnWigth = 150;
    for (int column = 0; column < invoicesTable->columnCount(); ++column) {
        invoicesTable->setColumnWidth(column, columnWigth);
    }
    invoicesTable->setColumnWidth(6,200);
    invoicesTable->setColumnWidth(3,300);
    invoicesTable->setColumnWidth(0,100);

    invoicesTable->setHorizontalHeaderLabels({"No.", "InvoiceID", "PlaceOrderDate", "DeliveryDate", "TotalAmount", "PaymentMehod","View"});
    addInvoicesData();

    stackWidget->setCurrentIndex(3);
}

void ManagerInterface::addProductsData() {
    productTable->clearContents();
    productTable->setRowCount(0);
    Vector<Product> products = dataController->loadProductData(); 
    size_t productCount = products.getSize(); 
    int row = 0;
    for (size_t i = 0; i < productCount && row < 100; ++i) {
        productTable->insertRow(row);
        productTable->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1))); 
        productTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(products[i].getProductId()))); 
        productTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(products[i].getName()))); 
        productTable->setItem(row, 4, new QTableWidgetItem(QString::number(products[i].getPrice()))); 
        productTable->setItem(row, 5, new QTableWidgetItem(QString::number(products[i].getStock()))); 
        QString imagePath = QString::fromStdString(products[i].getDescription()); 
        QLabel* imageLabel = new QLabel();
        QPixmap pixmap(imagePath);

        if (!pixmap.isNull()) {
            QPixmap scaledPixmap = pixmap.scaled(130, 130, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
            imageLabel->setFixedSize(130, 130); 
            imageLabel->setScaledContents(true); 
            productTable->setCellWidget(row, 1, imageLabel);
        } else {
            productTable->setItem(row, 1, new QTableWidgetItem("Không có ảnh"));
        }

        QPushButton *deleteProductButton = new QPushButton();
        QIcon delIcon("Resource/ICON/ICON3.png"); 
        deleteProductButton->setIcon(delIcon);
        deleteProductButton->setIconSize(QSize(35, 35));
        connect(deleteProductButton, &QPushButton::clicked, [this, productId = QString::fromStdString(products[i].getProductId())]() {
            deleteProductById(productId);
        });
        QPushButton *updateProductButton = new QPushButton();
        QIcon updateIcon("Resource/ICON/ICON15.png");
        updateProductButton->setIcon(updateIcon);
        updateProductButton->setIconSize(QSize(35,35));
        connect (updateProductButton, &QPushButton::clicked, [this, productId = QString::fromStdString(products[i].getProductId())](){
            updateProductById(productId);
        });

        QPushButton *showDetailsButton = new QPushButton();
        QIcon heartIcon("Resource/ICON/ICON10.png"); 
        showDetailsButton->setIcon(heartIcon);
        showDetailsButton->setIconSize(QSize(35, 35));
        connect(showDetailsButton, &QPushButton::clicked, [this, row]() { showDetailsProducts(row); });

        QHBoxLayout *actionLayout = new QHBoxLayout();
        actionLayout->addWidget(updateProductButton);
        actionLayout->addWidget(deleteProductButton);
        actionLayout->addSpacing(10);
        actionLayout->addWidget(showDetailsButton);
        

        QWidget *actionWidget = new QWidget();
        actionWidget->setLayout(actionLayout);
        productTable->setCellWidget(row, 6, actionWidget); 
        row++; 
    }
    for (int i = 0; i < row; ++i) {
        productTable->setRowHeight(i, 150);
    }
    if (productTable->rowCount() == 0) {
        qDebug() << "Product table is empty.";
    } 
}

void ManagerInterface::addNewProduct() {
    AddProductWidget *addProductWidget = new AddProductWidget();
    connect(addProductWidget, &AddProductWidget::productAdded, this, &ManagerInterface::showProducts);
    addProductWidget->show();
}

void  ManagerInterface::updateProductById(const QString& productId) {
    if (productId.isEmpty()) {
        showMessage(this, false, "Invalid product selected");
        return;
    }
    Product *product = new Product(dataController->findProductById(productId.toStdString()));
    AddProductWidget *addProductWidget = new AddProductWidget(nullptr,product);
    connect(addProductWidget, &AddProductWidget::productAdded, this, &ManagerInterface::showProducts);
    addProductWidget->show();
}

void ManagerInterface::deleteProductById(const QString& productId) {
    if (productId.isEmpty()) {
        showMessage(this, false, "Invalid product selected");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Product",
                                  "Are you sure you want to delete this product?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    dataController->deleteProduct(productId.toStdString());
    showMessage(this, true, "Delete Product Complete");
    showProducts(); 
}

void ManagerInterface:: deleteCustomer(int row){
    QString customerId;
    if (customersTable->item(row, 1) == nullptr) return;
    customerId = customersTable->item(row, 1)->text();
    dataController->deleteCustomer(customerId.toStdString());
    showMessage(this,true,"Delete Customer Complete");
    showCustomers(); 
}

void ManagerInterface ::showDetailsProducts(int row){
    Vector<Product> products = dataController->loadProductData();
    if (row < 0 || row >= products.getSize()) {
        QMessageBox::warning(this, "Error", "Invalid product selection.");
        return;
    }

    Vector<string> details = products[row].getDetail();
    
    if (details.getSize() < 3) {
        QMessageBox::warning(this, "Error", "Product details are incomplete.");
        return;
    }

    QString productDetails = QString("Detail Information:\n   Screen: %1\n    Resolution: %2\n   Processor: %3")
                                .arg(QString::fromStdString(details[0]))
                                .arg(QString::fromStdString(details[1]))
                                .arg(QString::fromStdString(details[2]));

    showMessage(this, true,productDetails);
}

void ManagerInterface::addCustomersData() {
    customersTable->clearContents();
    customersTable->setRowCount(0);

    Vector<Pair<Customer, double>> customerTotalData = appController->sortCustomerByAmount();
    size_t customerCount = customerTotalData.getSize();
    int row = 0;

    if (customerCount == 0) {
        qDebug() << "No customers to display.";
        return;
    }

    for (size_t i = 0; i < customerCount && row < 100; ++i) {
        const Customer& customer = customerTotalData[i].getFirst();
        double totalPrice = customerTotalData[i].getSecond();

        customersTable->insertRow(row);
        customersTable->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1)));
        customersTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(customer.getUserId())));
        customersTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(customer.getName())));
        customersTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(customer.getEmail())));
        customersTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(customer.getPhone())));
        customersTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(customer.getAddress())));
        customersTable->setItem(row, 6, new QTableWidgetItem(QString::number(totalPrice)));

        QPushButton *deleteCustomerButton = new QPushButton();
        QIcon addIcon("Resource/ICON/ICON13.png"); 
        deleteCustomerButton->setIcon(addIcon);
        deleteCustomerButton->setIconSize(QSize(25, 25));
        connect(deleteCustomerButton, &QPushButton::clicked, [this, row]() {deleteCustomer( row); });

        QHBoxLayout *actionLayout = new QHBoxLayout();
        actionLayout->addWidget(deleteCustomerButton);

        QWidget *actionWidget = new QWidget();
        actionWidget->setLayout(actionLayout);
        customersTable->setCellWidget(row, 7, actionWidget); 

        row++; 
    }

    for (int i = 0; i < row; ++i) {
        customersTable->setRowHeight(i, 70);
    }

    if (customersTable->rowCount() == 0) {
        qDebug() << "Customers table is empty.";
    }
}


void ManagerInterface::addInvoicesData() {
    invoicesTable->clearContents();
    invoicesTable->setRowCount(0);
    Vector<Invoice*> invoices = appController->sortInvoiceByDate();
    invoicesTable->setHorizontalHeaderLabels({"No.", "InvoiceID", "PlaceOrderDate", "DeliveryDate", "TotalAmount", "PaymentMehod","View"});
    invoicesTable->setRowCount(invoices.getSize());
    for (int i = 0; i < invoices.getSize(); ++i) {
        invoicesTable->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        invoicesTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(invoices[i]->getInvoiceId())));
        invoicesTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(invoices[i]->getInvoiceDate())));
        invoicesTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(invoices[i]->getDeliveryDate())));
        invoicesTable->setItem(i, 4, new QTableWidgetItem(QString::number(invoices[i]->getTotalAmount())));
        invoicesTable->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(invoices[i]->getPaymentMethod())));

        QPushButton *viewButton = new QPushButton(this);
        QIcon addIcon("Resource/ICON/ICON9.png"); 
        viewButton->setIcon(addIcon);
        viewButton->setIconSize(QSize(25, 25));
        connect(viewButton, &QPushButton::clicked, [this, i]() { showInvoiceDetail(i) ;});

        QWidget *actionWidget = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(actionWidget);
        layout->addWidget(viewButton);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        actionWidget->setLayout(layout);
        invoicesTable->setCellWidget(i, 6, actionWidget);
        
    }

    for (int row = 0; row < invoicesTable->rowCount(); ++row) {
        invoicesTable->setRowHeight(row, 70);
    }
    
}

void ManagerInterface:: showInvoiceDetail(int row) {
    QString invoice_ID;
    invoice_ID = invoicesTable->item(row,1)->text();
    string invoiceId = invoice_ID.toStdString();
    string invoice;
    dataController->findInvoiceByInvoiceID(invoiceId,invoice);
    showMessage(this,true,QString::fromStdString(invoice));
    
}

void ManagerInterface::drawChart(const Vector<Pair<QString, double>>& data, const QString& title, const QString& xLabel, const QString& yLabel, QWidget* container) {
    QLayout *existingLayout = container->layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget();  
            delete item;  
        }
        delete existingLayout;  
    }

    QVector<QString> categories; 
    QVector<double> values;     
    int dataSize = data.getSize();
    int maxItems = std::min(dataSize, 20);

    for (int i = 0; i < maxItems; ++i) {
        categories.append(data[i].getFirst());  
        values.append(data[i].getSecond());    
    }

    QBarSet *set = new QBarSet(yLabel);
    for (double value : values) {
        *set << value;  
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    series->setLabelsVisible(true);  

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->setTitleText(xLabel);
    axisX->append(categories);
    chart->setAxisX(axisX, series);
    
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText(yLabel);
    axisY->setRange(0, *std::max_element(values.begin(), values.end()));
    chart->setAxisY(axisY, series);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->addWidget(chartView);
    container->setLayout(layout);
}

void ManagerInterface::showOverview() {
    QLayout *existingLayout = overviewBox->layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget();  
            delete item;  
        }
        delete existingLayout;  
    }
    Vector<Pair<string, int>> soldProducts = dataController->loadSoldProductData();
    Vector<Pair<QString, double>> data;  
    double totalAmountSpent = 0.0;  
    int numberOfProduct = 0;  

    for (int i = 0; i < soldProducts.getSize(); ++i) {
        QString productId = QString::fromStdString(soldProducts[i].getFirst());
        int quantity = soldProducts[i].getSecond();

        Product product = dataController->findProductById(soldProducts[i].getFirst());
        double totalAmount = product.getPrice() * quantity;
        numberOfProduct += quantity;  
        totalAmountSpent += totalAmount; 
        data.pushback(Pair<QString, double>(productId, quantity));
    }
    QGroupBox *box1 = new QGroupBox(this);
    QVBoxLayout *Layout1 = new QVBoxLayout(box1);

    QPushButton *soldProductCountButton = new  QPushButton(" Sold Product" );
    QIcon Icon1(":/icon17"); 
    soldProductCountButton->setIcon(Icon1);
    soldProductCountButton->setIconSize(QSize(35, 35));
    QLabel *soldProductCountLabel = new QLabel(QString::number(numberOfProduct));
    soldProductCountLabel->setObjectName("overral");
    
    Layout1->addWidget(soldProductCountButton);
    Layout1->addWidget(soldProductCountLabel);

    QGroupBox *box2 = new QGroupBox(this);
    QVBoxLayout *Layout2 = new QVBoxLayout(box2);

    QPushButton *totalAmountSpentButton = new QPushButton("Total Amount Spent");
    QIcon Icon2(":/icon18");
    totalAmountSpentButton->setIcon(Icon2);
    totalAmountSpentButton->setIconSize(QSize(35, 35));
    QLabel *totalAmountLabel = new QLabel( QString::number(totalAmountSpent, 'f', 2));
    totalAmountLabel->setObjectName("overral");
    Layout2->addWidget(totalAmountSpentButton);
    Layout2->addWidget(totalAmountLabel);

    QGroupBox *box3 = new QGroupBox(this);
    QVBoxLayout *Layout3 = new QVBoxLayout(box3);
    QPushButton *totalCustomerButton = new QPushButton("Total Customers");
    QIcon Icon3(":/icon16");
    totalCustomerButton->setIcon(Icon3);
    totalCustomerButton->setIconSize(QSize(35, 35));
    int numCustomers = dataController->loadAllCustomersData().getSize();
    QLabel *totalCustomerLabel = new QLabel( QString::number(numCustomers));
    totalCustomerLabel->setObjectName("overral");
    Layout3->addWidget(totalCustomerButton);
    Layout3->addWidget(totalCustomerLabel);

    QGroupBox *box4 = new QGroupBox(this);
    QVBoxLayout *Layout4 = new QVBoxLayout(box4);
    QPushButton *totalInvoice = new QPushButton("Total Invoices");
    QIcon Icon4(":/icon19");
    totalInvoice->setIcon(Icon4);
    totalInvoice->setIconSize(QSize(35, 35));
    int numInvoice = appController->loadAllInvoice().getSize();
    QLabel *totalInvoicesLabel = new QLabel( QString::number(numInvoice));
    totalInvoicesLabel->setObjectName("overral");
    Layout4->addWidget(totalInvoice);
    Layout4->addWidget(totalInvoicesLabel);

    connect(totalCustomerButton, &QPushButton::clicked, this, &ManagerInterface::showCustomers);
    connect(soldProductCountButton, &QPushButton::clicked, this, &ManagerInterface::showSoldProduct);
    connect(totalAmountSpentButton, &QPushButton::clicked, this, &ManagerInterface::showSoldProduct);
    connect(totalInvoice, &QPushButton::clicked, this, &ManagerInterface::showInvoices);

    QGroupBox *soldProductCountBox = new QGroupBox(this);
    QHBoxLayout *soldProductCountLayout = new QHBoxLayout(soldProductCountBox);
    soldProductCountLayout->addSpacing(10);
    soldProductCountLayout->addWidget(box1);
    soldProductCountLayout->addSpacing(10);
    soldProductCountLayout->addWidget(box2);
    soldProductCountLayout->addSpacing(10);
    soldProductCountLayout->addWidget(box3);
    soldProductCountLayout->addSpacing(10);
    soldProductCountLayout->addWidget(box4);

    QPushButton *showSoldProductCountButton = new QPushButton(" Show Sold Product Count");
    QPushButton *showInvoiceByDateButton = new QPushButton(" Show Amount By Date");
    QPushButton *showCustomerByAmountButton = new QPushButton(" Show Customer By Amount");
    QIcon iconChart(":/icon21");
    showSoldProductCountButton->setIcon(iconChart);
    showInvoiceByDateButton->setIcon(iconChart);
    showCustomerByAmountButton->setIcon(iconChart);
    showSoldProductCountButton->setIconSize(QSize(35, 35));
    showInvoiceByDateButton->setIconSize(QSize(35, 35));
    showCustomerByAmountButton->setIconSize(QSize(35, 35));
    
    connect(showInvoiceByDateButton, &QPushButton::clicked, this, &ManagerInterface::showAmountByDate);
    connect(showSoldProductCountButton, &QPushButton::clicked, this, &ManagerInterface::showProductById);
    connect(showCustomerByAmountButton,&QPushButton::clicked,this, &ManagerInterface::showCustomerByAmount);
    QGroupBox *dataBox = new QGroupBox(this);
    QHBoxLayout *dataLayout = new QHBoxLayout(dataBox);
    dataLayout->addWidget(showSoldProductCountButton);
    dataLayout->addWidget(showInvoiceByDateButton);
    dataLayout->addWidget(showCustomerByAmountButton);
    diagramBox = new QGroupBox(this);

    QVBoxLayout *layout = new QVBoxLayout(overviewBox);
    layout->addWidget(soldProductCountBox);
    layout->addSpacing(20);
    layout->addWidget(dataBox);
    layout->addWidget(diagramBox);
    overviewBox->setLayout(layout);
    overviewBox->show();
    showProductById();
    stackWidget->setCurrentIndex(0);
}
void ManagerInterface:: showProductById(){
    Vector<Pair<string, int>> soldProducts = dataController->loadSoldProductData();
    Vector<Pair<QString, double>> data;  
    for (int i = 0; i < soldProducts.getSize(); ++i) {
        QString productId = QString::fromStdString(soldProducts[i].getFirst());
        int quantity = soldProducts[i].getSecond();
        data.pushback(Pair<QString, double>(productId, quantity));
    }
    if(data.getSize()!=0)
    drawChart(data, "Total Revenue by Product ID", "Product ID", "Revenue", diagramBox);
}
void ManagerInterface::showAmountByDate() {
    Vector<Invoice*> invoicesData = appController->loadAllInvoice();
    Vector<Pair<QString, double>> data;

    QDate endDate = QDate::currentDate();
    QDate startDate = endDate.addDays(-14); 

    QVector<QString> allDates;
    QVector<double> allAmounts;

    for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
        allDates.append(date.toString("yyyy-MM-dd"));
        allAmounts.append(0.0); 
    }

    for (int i = 0; i < invoicesData.getSize(); ++i) {
        QString invoiceDate = QString::fromStdString(invoicesData[i]->getInvoiceDate());
        double amount = invoicesData[i]->getTotalAmount();

        int index = allDates.indexOf(invoiceDate);
        if (index != -1) {
            allAmounts[index] += amount; 
        }
    }

    for (int i = 0; i < allDates.size(); ++i) {
        data.pushback(Pair<QString, double>(allDates[i], allAmounts[i]));
    }

    if(data.getSize()!=0)
    drawChart(data, "Total Amount By Date", "Date", "Amount", diagramBox);
}
void ManagerInterface:: showCustomerByAmount(){
    Vector<Pair<QString, double>> data;
    Vector<Customer> customers = dataController->loadAllCustomersData();
    for(int i = 0; i <customers.getSize();i++){
        Vector<Invoice*> invoices = dataController->loadOrdersData(customers[i].getUserId()).getInvoice();
        double totalPrice = 0.0;
        for (int j = 0; j < invoices.getSize(); ++j) {
            totalPrice += invoices[j]->getTotalAmount();
        }
        if( totalPrice > 0.0 ){
        QString customerName = QString::fromStdString(customers[i].getName());
        data.pushback(Pair<QString, double>(customerName, totalPrice));
        }
    }
    if(data.getSize()!=0)
    drawChart(data, "Total Amount By Customer", "Customer", "Amount", diagramBox);
}
void  ManagerInterface:: filterProducts(){
    QString searchTerm = searchProductLine->text().trimmed();
    if (searchTerm.isEmpty()) {
        for (int row = 0; row < productTable->rowCount(); ++row) {
            productTable->setRowHidden(row, false);
        }
        return;
    }

    for (int row = 0; row <productTable->rowCount(); ++row) {
        QTableWidgetItem* item = productTable->item(row, 3);
        if (item) {
            bool matches = item->text().contains(searchTerm, Qt::CaseInsensitive);
            productTable->setRowHidden(row, !matches);
        } else {
            productTable->setRowHidden(row, true);
        }
    }
}
void  ManagerInterface::filterCustomer(){
    QString searchTerm = searchCustomerLine->text().trimmed();
    if (searchTerm.isEmpty()) {
        for (int row = 0; row < customersTable->rowCount(); ++row) {
            customersTable->setRowHidden(row, false);
        }
        return;
    }

    for (int row = 0; row <customersTable->rowCount(); ++row) {
        QTableWidgetItem* item = customersTable->item(row, 3);
        if (item) {
            bool matches = item->text().contains(searchTerm, Qt::CaseInsensitive);
            customersTable->setRowHidden(row, !matches);
        } else {
            customersTable->setRowHidden(row, true);
        }
    }
}
void  ManagerInterface::filterInvoice(){
    QString searchTerm = searchInvoiceLine->text().trimmed();
    if (searchTerm.isEmpty()) {
        for (int row = 0; row < invoicesTable->rowCount(); ++row) {
            invoicesTable->setRowHidden(row, false);
        }
        return;
    }

    for (int row = 0; row <invoicesTable->rowCount(); ++row) {
        QTableWidgetItem* item =invoicesTable->item(row, 2);
        if (item) {
            bool matches = item->text().contains(searchTerm, Qt::CaseInsensitive);
            invoicesTable->setRowHidden(row, !matches);
        } else {
            invoicesTable->setRowHidden(row, true);
        }
    }
}

void ManagerInterface::showSoldProduct() {
    Vector<Pair<string, int>> soldProducts = appController->sortSoldProducts();
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Sold Products");
    dialog->resize(800, 500);
    QTableWidget *table = new QTableWidget(dialog);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Product ID","Product Name" , "Quantity Sold","Price"});
    table->setRowCount(soldProducts.getSize());
    for (int i = 0; i < soldProducts.getSize(); ++i) {
        const Pair<string, int> &product = soldProducts[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(product.getFirst())));
        string productname ;
        int price = dataController->findProductById(product.getFirst()).getPrice();
        productname = dataController->findProductById(product.getFirst()).getName();
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(productname)));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(product.getSecond())));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(price)));
        
    }
    table->setColumnWidth(1,300);
    table->setColumnWidth(2,150);
    table->setColumnWidth(3,150);
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(table);
    dialog->setLayout(layout);
    dialog->exec();
}