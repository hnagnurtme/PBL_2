#include "View/ManagerInterface.h"
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
    searchInvoiceLine->setPlaceholderText("Search by customer name...");
    connect(searchInvoiceLine, &QLineEdit::textChanged, this, &ManagerInterface::filterInvoice);
    

    productTable = new QTableWidget(5, 6, this);
    productTable->setHorizontalHeaderLabels({"No.", "Description", "Product ID", "Product Name", "Price", "Quantity", "Change"});

    QGroupBox *productGroupBox = new QGroupBox(this);
    QVBoxLayout *productLayout = new QVBoxLayout(productGroupBox);
    productLayout->addWidget(searchProductLine);
    productLayout->addSpacing(20);
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
    invoicesTable->setFixedSize(1000,700);
    
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
    showProducts();
}

void ManagerInterface::showProducts(){
    productTable->clear();
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

void ManagerInterface::showAccount(){

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

        QPushButton *addProductsButton = new QPushButton();
        QIcon addIcon("Resource/ICON/ICON2.png"); 
        addProductsButton->setIcon(addIcon);
        addProductsButton->setIconSize(QSize(35, 35));
        connect(addProductsButton, &QPushButton::clicked, [this, row]() { addProducts(row, false); });

        QPushButton *showDetailsButton = new QPushButton();
        QIcon heartIcon("Resource/ICON/ICON10.png"); 
        showDetailsButton->setIcon(heartIcon);
        showDetailsButton->setIconSize(QSize(35, 35));
        connect(showDetailsButton, &QPushButton::clicked, [this, row]() { showDetailsProducts(row); });

        QHBoxLayout *actionLayout = new QHBoxLayout();
        actionLayout->addWidget(addProductsButton);
        actionLayout->addSpacing(5);
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

void ManagerInterface :: addProducts(int row, bool fromCart){

}

void ManagerInterface :: deleteProducts(int row, bool fromCart){

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
    Vector<Customer> customers = dataController->loadAllCustomersData();
    size_t customerCount = customers.getSize(); 
    int row = 0;
    for (size_t i = 0; i < customerCount && row < 100; ++i) {
        customersTable->insertRow(row);
        customersTable->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1))); 
        customersTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(customers[i].getUserId()))); 
        customersTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(customers[i].getName()))); 
        customersTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(customers[i].getEmail()))); 
        customersTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(customers[i].getPhone()))); 
        customersTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(customers[i].getAddress()))); 
        Vector<Invoice*> invoices = dataController->loadOrdersData(customers[i].getUserId()).getInvoice();
        double totalPrice = 0.0;
        for (size_t j = 0; j < invoices.getSize(); ++j) {
            totalPrice += invoices[j]->getTotalAmount();
        }
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

void ManagerInterface:: deleteCustomer(int row){
    QString customerId;
    if (customersTable->item(row, 2) == nullptr) return;
    customerId = customersTable->item(row, 1)->text();
    dataController->deleteCustomer(customerId.toStdString());
    showMessage(this,true,"Delete Customer Complete");
    showCustomers(); 

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
        invoicesTable->setRowHeight(row, 50);
    }
    invoicesTable->setColumnWidth(0, 50); 
    invoicesTable->setColumnWidth(1, 150);
    invoicesTable->setColumnWidth(2, 150);
    invoicesTable->setColumnWidth(3, 150);
    invoicesTable->setColumnWidth(4, 180);
    invoicesTable->setColumnWidth(5, 150);
    invoicesTable->setColumnWidth(6, 80);
    
}

void ManagerInterface:: showInvoiceDetail(int row) {
    QString invoice_ID;
    invoice_ID = invoicesTable->item(row,1)->text();
    string invoiceId = invoice_ID.toStdString();
    

    string invoice;
    dataController->findInvoiceByInvoiceID(invoiceId,invoice);
    showMessage(this,true,QString::fromStdString(invoice));
    
}

inline void drawChart(const Vector<Pair<QString, double>>& data, const QString& title, const QString& xLabel, const QString& yLabel, QWidget* container) {
    QVector<QString> categories; 
    QVector<double> values;     
    for (int i = 0; i <data.getSize();++i) {
        categories.append(data[i].getFirst());  
        values.append(data[i].getSecond());    
    }

    QBarSet *set = new QBarSet(yLabel);
    for (double value : values) {
        *set << value;  
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
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

inline void drawLineChart(const Vector<Pair<QString, double>>& data, const QString& title, const QString& xLabel, const QString& yLabel, QWidget* container) {
    QLayout* oldLayout = container->layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    QVector<QString> categories;
    QVector<double> values;
    for (int i = 0; i < data.getSize(); ++i) {
        categories.append(data[i].getFirst());
        values.append(data[i].getSecond());
    }

    // Tạo QLineSeries để chứa các điểm và nối chúng bằng đường
    QLineSeries* series = new QLineSeries();
    for (int i = 0; i < values.size(); ++i) {
        series->append(i, values[i]); // Thêm các điểm vào series
    }
    series->setName(yLabel);

    // Tạo QChart
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Trục X: Thêm các danh mục từ dữ liệu
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Trục Y: Xác định phạm vi dựa trên giá trị
    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText(yLabel);
    axisY->setRange(0, *std::max_element(values.begin(), values.end()) + 10); // Tăng một chút để có khoảng trống
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Tạo QChartView
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Đặt layout mới cho container
    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->addWidget(chartView);
    container->setLayout(layout);
}

void ManagerInterface::showOverview() {
    Vector<Pair<string, int>> soldProducts = dataController->loadSoldProductData();

    Vector<Pair<QString, double>> data;  
    double totalAmountSpent = 0.0;  
    int totalOrders = soldProducts.getSize();  
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
    QLabel *soldProductCountLabel = new QLabel("Total Products Sold: " + QString::number(numberOfProduct));
    soldProductCountLabel->setObjectName("titleLabel");
    QLabel *totalAmountLabel = new QLabel("Total Amount Earned: " + QString::number(totalAmountSpent, 'f', 2));
    totalAmountLabel->setObjectName("titleLabel");
    drawChart(data, "Total Revenue by Product ID", "Product ID", "Revenue", overviewBox);
    QVBoxLayout *layout = new QVBoxLayout(overviewBox);
    layout->addWidget(soldProductCountLabel);
    layout->addSpacing(20);
    layout->addWidget(totalAmountLabel);
    layout->addSpacing(20);
    overviewBox->setLayout(layout);
    overviewBox->show();
    stackWidget->setCurrentIndex(0);
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
        QTableWidgetItem* item =invoicesTable->item(row, 3);
        if (item) {
            bool matches = item->text().contains(searchTerm, Qt::CaseInsensitive);
            invoicesTable->setRowHidden(row, !matches);
        } else {
            invoicesTable->setRowHidden(row, true);
        }
    }
}