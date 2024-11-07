#include "View/CustomerInterface.h"
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



void CustomerInterface::showMessage(QWidget *parent, bool status, const QString &message) {
    QMessageBox messageBox(parent);
    QString icon_path = (status) ? "Resource/ICON/ICON7.png" : "Resource/ICON/ICON6.png";
    QPixmap originalPixmap(icon_path);
    QPixmap scaledPixmap = originalPixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    messageBox.setIconPixmap(scaledPixmap);
    messageBox.setText(message);
    messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    messageBox.setFixedSize(400, 200);
    messageBox.exec();
}
CustomerInterface::CustomerInterface(QWidget *parent) : QWidget(parent) {
    customer = new Customer("USER002");

    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        setStyleSheet(style);
    }

    setFixedSize(1500, 800);
    setWindowTitle("Customer Homepage");

    showOverviewButton = new QPushButton("Overview", this);
    showProductsButton = new QPushButton("Products", this);
    showCartButton = new QPushButton("Cart", this);
    showOrdersButton = new QPushButton("Orders", this);
    showAccountButton = new QPushButton("Account", this);
    checkoutButton = new QPushButton("Logout", this);
    checkoutButton->setObjectName("cancelButton");

    connect(showOverviewButton, &QPushButton::clicked, this, &CustomerInterface::showOverview);
    connect(showProductsButton, &QPushButton::clicked, this, &CustomerInterface::showProducts);
    connect(showCartButton, &QPushButton::clicked, this, &CustomerInterface::showCart);
    connect(showOrdersButton, &QPushButton::clicked, this, &CustomerInterface::showOrders);
    connect(showAccountButton, &QPushButton::clicked, this, &CustomerInterface::showAccount);
    connect(checkoutButton, &QPushButton::clicked, this, &CustomerInterface::checkout);

    QWidget *menuWidget = new QWidget(this);
    QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);
    menuWidget->setFixedSize(200, 800);

    menuLayout->addSpacing(50);
    menuLayout->addWidget(showOverviewButton);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(showProductsButton);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(showCartButton);
    menuLayout->addSpacing(10);
    menuLayout->addWidget(showOrdersButton);
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
    connect(searchLineEdit, &QLineEdit::textChanged, this, &CustomerInterface::filterProducts);

    productTable = new QTableWidget(5, 6, this);
    productTable->setHorizontalHeaderLabels({"No.", "Description", "Product ID", "Product Name", "Price", "Quantity", "Add to Cart"});

    QGroupBox *productGroupBox = new QGroupBox(this);
    QVBoxLayout *productLayout = new QVBoxLayout(productGroupBox);
    productLayout->addWidget(searchLineEdit);
    productLayout->addSpacing(20);
    productLayout->addWidget(productTable);
    productTable->setFixedSize(1250, 700);

    cartTable = new QTableWidget(0, 6, this);
    cartTable->setHorizontalHeaderLabels({"No.", "Product Name", "Product ID", "Price", "Quantity", "Action"});
    cartTable->setFixedSize(750, 650);

    invoiceDisplay = new QTextEdit("Invoice", this);
    invoiceDisplay->setVisible(false);
    paymentButton = new QPushButton("Payment", this);
    paymentButton->setVisible(false);
    connect(paymentButton, &QPushButton::clicked, this, &CustomerInterface::payment);

    dateLabel = new QLabel("Choose delivery date:", this);
    dateLabel->setObjectName("inputArea");
    dateLabel->setVisible(false);
    deliveryDateEdit = new QDateEdit(this);
    deliveryDateEdit->setVisible(false);
    deliveryDateEdit->setCalendarPopup(true);
    deliveryDateEdit->setMinimumDate(QDate::currentDate());
    connect(deliveryDateEdit, &QDateEdit::dateChanged, this, &CustomerInterface::onDeliveryDateChanged);

    paymentMethodLabel = new QLabel("Payment Method:", this);
    paymentMethodLabel->setObjectName("inputArea");
    paymentMethodLabel->setVisible(false);
    paymentMethodComboBox = new QComboBox(this);
    paymentMethodComboBox->addItem("Credit Card");
    paymentMethodComboBox->addItem("Bank Transfer");
    paymentMethodComboBox->addItem("Cash on Delivery");
    paymentMethodComboBox->setVisible(false);
    connect(paymentMethodComboBox, &QComboBox::currentIndexChanged, this, &CustomerInterface::onPaymentMethodChanged);

    totalPrice = new QLabel(this);
    totalPrice->setObjectName("inputArea");
    placeOrdersButton = new QPushButton("Place Orders", this);
    connect(placeOrdersButton, &QPushButton::clicked, this, &CustomerInterface::showInvoice);
    clearCartButton = new QPushButton("Clear Cart", this);
    clearCartButton->setObjectName("cancelButton");
    connect(clearCartButton, &QPushButton::clicked, this, &CustomerInterface::clearCart);

    QGroupBox *placeOrderBox = new QGroupBox(this);
    QHBoxLayout *placeOrdersLayout = new QHBoxLayout(placeOrderBox);
    placeOrdersLayout->addWidget(totalPrice);
    placeOrdersLayout->addWidget(clearCartButton);
    placeOrdersLayout->addWidget(placeOrdersButton);

    QGroupBox *cartAndPlaceOrdersBox = new QGroupBox(this);
    QVBoxLayout *cartAndPlaceOrderLayout = new QVBoxLayout(cartAndPlaceOrdersBox);
    cartAndPlaceOrderLayout->addWidget(cartTable);
    cartAndPlaceOrderLayout->addWidget(placeOrderBox);

    QGroupBox *invoiceGroupBox = new QGroupBox(this);
    QVBoxLayout *invoiceLayout = new QVBoxLayout(invoiceGroupBox);
    invoiceLayout->addWidget(invoiceDisplay);
    invoiceLayout->addWidget(dateLabel);
    invoiceLayout->addWidget(deliveryDateEdit);
    invoiceLayout->addWidget(paymentMethodLabel);
    invoiceLayout->addWidget(paymentMethodComboBox);
    invoiceLayout->addWidget(paymentButton);

    QHBoxLayout *cartAndInvoiceLayout = new QHBoxLayout();
    QGroupBox *cartAndInvoiceBox = new QGroupBox(this);
    cartAndInvoiceBox->setLayout(cartAndInvoiceLayout);
    cartAndInvoiceLayout->addWidget(cartAndPlaceOrdersBox);
    cartAndInvoiceLayout->addWidget(invoiceGroupBox);

    ordersTable = new QTableWidget(0,7,this);
    ordersTable->setHorizontalHeaderLabels({"No.", "InvoiceID", "PlaceOrderDate", "DeliveryDate", "TotalAmount", "PaymentMehod","View"});
    ordersTable->setFixedSize(950, 650);

    QGroupBox *ordersBox = new QGroupBox(this);
    QVBoxLayout *ordersLayout = new QVBoxLayout(ordersBox);
    ordersLayout->addWidget(ordersTable);

    overviewBox = new QGroupBox(this);

    stackWidget->addWidget(productGroupBox);
    stackWidget->addWidget(cartAndInvoiceBox);
    stackWidget->addWidget(ordersBox);
    stackWidget->addWidget(overviewBox);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(menuWidget);
    layout->addWidget(stackWidget);
    mainLayout->addLayout(layout);
    setLayout(mainLayout);

    cartOrigin();
    ordersOrigin();
    showProducts();
}


void CustomerInterface::addProductsData() {
    productTable->clearContents();
    productTable->setRowCount(0);

    DataController *productData = new DataController();;
    Vector<Product> products = productData->loadProductData(); 
    delete productData;
    size_t productCount = products.getSize(); 
    int row = 0;

    qDebug() << "Number of products loaded:" << productCount;

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

        QPushButton *addFavouriteButton = new QPushButton();
        QIcon heartIcon("Resource/ICON/ICON1.png"); 
        addFavouriteButton->setIcon(heartIcon);
        addFavouriteButton->setIconSize(QSize(35, 35));
        connect(addFavouriteButton, &QPushButton::clicked, [this, row]() { addFavouriteProducts(row); });

        QHBoxLayout *actionLayout = new QHBoxLayout();
        actionLayout->addWidget(addProductsButton);
        actionLayout->addSpacing(5);
        actionLayout->addWidget(addFavouriteButton);

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


void CustomerInterface::showProducts() {
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



    productTable->setHorizontalHeaderLabels({"No.", "Description", "Product ID", "Product Name", "Price", "Quantity", "Add to Cart"});
    addProductsData();
    stackWidget->setCurrentIndex(0);
}
void CustomerInterface::addProducts(int row, bool fromCart) {
    QString tenSanPham, giaSanPham, productId;

    if (fromCart) {
        if (cartTable->item(row, 0) == nullptr) return;
        tenSanPham = cartTable->item(row, 1)->text();
        giaSanPham = cartTable->item(row, 2)->text();
        productId = QString::fromStdString(customer->getCart()->getItems()[row].getFirst()->getProductId());
    } else {
        if (productTable->item(row, 3) == nullptr) return;
        tenSanPham = productTable->item(row, 3)->text();
        giaSanPham = productTable->item(row, 4)->text();
        productId = productTable->item(row, 2)->text();
    }

    Product *product = new Product(productId.toStdString(), tenSanPham.toStdString(), "", giaSanPham.toDouble(), 0, "", Vector<string>(), "");
    customer->addToCart(product,1);

    if (fromCart) {
        showCart();
    }
}

void CustomerInterface::deleteProducts(int row, bool fromCart) {
    QString productId;

    if (fromCart) {
        if (cartTable->item(row, 0) == nullptr) return;
        productId = QString::fromStdString(customer->getCart()->getItems()[row].getFirst()->getProductId());
    } else {
        if (productTable->item(row, 2) == nullptr) return;
        productId = productTable->item(row, 2)->text();
    }

    if (!productId.isEmpty() && customer->getCart()->contains(productId.toStdString())) {
        customer->reduceItem(productId.toStdString(), 1);
        if (customer->getCart()->getItemQuantity(productId.toStdString()) == 0) {
            customer->removeItem(productId.toStdString());
        }
    }

    if (fromCart) {
        showCart();
    }
}


void CustomerInterface::cartOrigin() {
    unique_ptr<DataController> cartData = make_unique<DataController>();
    unique_ptr<Cart> cartOrigin = make_unique<Cart>(cartData->loadCartData(customer->getUserId()));

    for (long i = 0; i < cartOrigin->getItems().getSize(); ++i) {
        Product* product = cartOrigin->getItems()[i].getFirst(); 
        int quantity = cartOrigin->getItems()[i].getSecond();
        customer->addToCart(product, quantity);
    }
}
void CustomerInterface::ordersOrigin() {
    unique_ptr<DataController> ordersData = make_unique<DataController>();
    Orders orders = ordersData->loadOrdersData(customer->getUserId());
    
    customer->updateOrderHistory(orders);
}


void CustomerInterface::showCart() {
    cartTable->clear();
    cartTable->setColumnCount(6);
    cartTable->setHorizontalHeaderLabels({"No.", "Product Name", "Product ID", "Price", "Quantity", "Action"});
    Vector<Pair<Product*, int>> items = customer->getCart()->getItems(); 
    cartTable->setRowCount(items.getSize());
    for (int i = 0; i < items.getSize(); ++i) {
        cartTable->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        cartTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(items[i].getFirst()->getName())));
        cartTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(items[i].getFirst()->getProductId())));
        cartTable->setItem(i, 3, new QTableWidgetItem(QString::number(items[i].getFirst()->getPrice())));
        cartTable->setItem(i, 4, new QTableWidgetItem(QString::number(items[i].getSecond())));

        QPushButton *addButton = new QPushButton(this);
        QIcon addIcon("Resource/ICON/ICON4.png"); 
        addButton->setIcon(addIcon);
        addButton->setIconSize(QSize(25, 25));
        connect(addButton, &QPushButton::clicked, [this, i]() { addProducts(i, true); });

        QPushButton *deleteButton = new QPushButton(this);
        QIcon delIcon("Resource/ICON/ICON3.png"); 
        deleteButton->setIcon(delIcon);
        deleteButton->setIconSize(QSize(25, 25));
        deleteButton->setObjectName("cancelButton");
        connect(deleteButton, &QPushButton::clicked, [this, i]() { deleteProducts(i, true); });

        QWidget *actionWidget = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(actionWidget);
        layout->addWidget(addButton);
        layout->addWidget(deleteButton);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        actionWidget->setLayout(layout);
        cartTable->setCellWidget(i, 5, actionWidget);
    }

    for (int row = 0; row < cartTable->rowCount(); ++row) {
        cartTable->setRowHeight(row, 50);
    }
    cartTable->setColumnWidth(0, 50); 
    cartTable->setColumnWidth(1, 250);
    cartTable->setColumnWidth(5, 125);
    double totalprice = 0.0;
    const Vector<Pair<Product*, int>>& cartItems = customer->getCart()->getItems(); 

    for (long i = 0; i < cartItems.getSize(); ++i) {
        const Product* product = cartItems[i].getFirst();
        int soLuong = cartItems[i].getSecond(); 
        double gia = product->getPrice();
        totalprice += gia * soLuong; 
    }

    totalPrice->setText("Total Price : " + QString::number(totalprice) + " $");
    totalPrice->setStyleSheet("font-weight: bold; font-size: 16pt;");
    totalPrice->setFixedHeight(40);
    stackWidget->setCurrentIndex(1);
    unique_ptr<DataController> cartData = make_unique<DataController>();
    cartData->saveCartData(*customer->getCart()); 

}

void CustomerInterface::clearCart() {
    customer->getCart()->clearCart();
    unique_ptr<DataController> cartData = make_unique<DataController>();
    cartData->saveCartData(*customer->getCart()); 
    showCart();
}

void CustomerInterface::showOverview() {
    DataController *productData = new DataController();
    Vector<Product> products = productData->loadProductData();
    delete productData;

    QVector<QString> productIds;
    QVector<double> productQuantities;

    for (int i = 0; i < products.getSize(); ++i) {
        QString productId = QString::fromStdString(products[i].getProductId());
        double quantity = products[i].getStock();
        productIds.append(productId);
        productQuantities.append(quantity);
    }

    QBarSet *set = new QBarSet("Product Quantity");

    for (double quantity : productQuantities) {
        *set << quantity;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Product Quantities by Product ID");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(productIds);
    chart->setAxisX(axisX, series);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, *std::max_element(productQuantities.begin(), productQuantities.end()));
    chart->setAxisY(axisY, series);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(overviewBox);
    layout->addWidget(chartView);
    overviewBox->setLayout(layout);

    overviewBox->show();
    stackWidget->setCurrentIndex(3);
}




void CustomerInterface::filterProducts() {
    {}
}


void CustomerInterface::showAccount() {
}

void CustomerInterface::checkout() {
}

void CustomerInterface::addFavouriteProducts(int row){

}

void CustomerInterface::showInvoice() { 
    if (customer->getCart()->isEmptyCart()){
        showMessage(this, false, "Cart is already empty");
        return;
    }
    invoiceDisplay->setVisible(true);
    invoiceDisplay->setText("");
    paymentButton->setVisible(true);
    placeOrdersButton->setVisible(false);
    dateLabel->setVisible(true);
    deliveryDateEdit->setVisible(true);
    paymentMethodComboBox->setVisible(true);
    paymentMethodLabel->setVisible(true);
}


void CustomerInterface::payment() {
    showMessage(this,true,"Successfully completed your purchase");
    
    QDate deliveryDate = deliveryDateEdit->date();
    QString deliveryDateString = deliveryDate.toString("yyyy-MM-dd");
    QString paymentMethod = paymentMethodComboBox->currentText();

    customer->payment(deliveryDateString.toStdString(),paymentMethod.toStdString());
    invoiceDisplay->setText("");
    paymentMethodLabel->setVisible(false);
    paymentMethodComboBox->setVisible(false);
    deliveryDateEdit->setVisible(false);
    dateLabel->setVisible(false);
    paymentButton->setVisible(false);
    placeOrdersButton->setVisible(true);
    showProducts();
}


void CustomerInterface::onDeliveryDateChanged() {
    QDate deliveryDate = deliveryDateEdit->date();
    QString deliveryDateString = deliveryDate.toString("yyyy-MM-dd");
    QString paymentMethod = paymentMethodComboBox->currentText();
    Invoice invoice(*customer->getCart());
    invoice.setDeliveryDate(deliveryDateString.toStdString());
    invoice.setPaymentMethod(paymentMethod.toStdString());
    string invoiceInfo = invoice.displayInvoice(); 
    invoiceDisplay->setVisible(true);
    invoiceDisplay->setText(QString::fromStdString(invoiceInfo));
}
void CustomerInterface::onPaymentMethodChanged(){
    QDate deliveryDate = deliveryDateEdit->date();
    QString deliveryDateString = deliveryDate.toString("yyyy-MM-dd");
    QString paymentMethod = paymentMethodComboBox->currentText();
    Invoice invoice(*customer->getCart());
    invoice.setDeliveryDate(deliveryDateString.toStdString());
    invoice.setPaymentMethod(paymentMethod.toStdString());
    string invoiceInfo = invoice.displayInvoice(); 
    invoiceDisplay->setVisible(true);
    invoiceDisplay->setText(QString::fromStdString(invoiceInfo));
}
void CustomerInterface::showOrders(){
    ordersTable->clear();
    ordersTable->setColumnCount(7);
    ordersTable->setHorizontalHeaderLabels({"No.", "InvoiceID", "PlaceOrderDate", "DeliveryDate", "TotalAmount", "PaymentMehod","View"});
    Vector<Invoice*> invoices = customer->getOrderHistory().getInvoice();
    ordersTable->setRowCount(invoices.getSize());
    for (int i = 0; i < invoices.getSize(); ++i) {
        ordersTable->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ordersTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(invoices[i]->getInvoiceId())));
        ordersTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(invoices[i]->getInvoiceDate())));
        ordersTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(invoices[i]->getDeliveryDate())));
        ordersTable->setItem(i, 4, new QTableWidgetItem(QString::number(invoices[i]->getTotalAmount())));
        ordersTable->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(invoices[i]->getPaymentMethod())));

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
        ordersTable->setCellWidget(i, 6, actionWidget);
        
    }

    for (int row = 0; row < ordersTable->rowCount(); ++row) {
        ordersTable->setRowHeight(row, 50);
    }
    ordersTable->setColumnWidth(0, 50); 
    ordersTable->setColumnWidth(1, 150);
    ordersTable->setColumnWidth(2, 150);
    ordersTable->setColumnWidth(3, 150);
    ordersTable->setColumnWidth(4, 180);
    ordersTable->setColumnWidth(5, 150);
    ordersTable->setColumnWidth(6, 80);

    stackWidget->setCurrentIndex(2);
}


CustomerInterface::~CustomerInterface() {
    delete customer;
}


void CustomerInterface::showInvoiceDetail( int i){

}