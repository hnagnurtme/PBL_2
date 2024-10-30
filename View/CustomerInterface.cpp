#include "View/CustomerInterface.h"
#include "Model/Product.h"
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
CustomerInterface::CustomerInterface(QWidget *parent) : QWidget(parent) {
    customerID ="USER001";
    cart.setCartID(customerID);
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        this->setStyleSheet(style);
    }

    setFixedSize(1500, 800);
    setWindowTitle("Customer Homepage");

    showOverviewButton = new QPushButton("Overview");
    showProductsButton = new QPushButton("Products");
    showCartButton = new QPushButton("Cart");
    showOrdersButton = new QPushButton("Your Orders");
    showAccountButton = new QPushButton("Account Information");
    checkoutButton = new QPushButton("Logout");

    showOverviewButton->setObjectName("showOverviewButton");
    showProductsButton->setObjectName("showProductsButton");
    showCartButton->setObjectName("showCartButton");
    showOrdersButton->setObjectName("showOrdersButton");
    showAccountButton->setObjectName("showAccountButton");
    checkoutButton->setObjectName("checkoutButton");

    connect(showOverviewButton, &QPushButton::clicked, this, &CustomerInterface::showOverview);
    connect(showProductsButton, &QPushButton::clicked, this, &CustomerInterface::showProducts);
    connect(showCartButton, &QPushButton::clicked, this, &CustomerInterface::showCart);
    connect(showOrdersButton, &QPushButton::clicked, this, &CustomerInterface::showOrders);
    connect(showAccountButton, &QPushButton::clicked, this, &CustomerInterface::showAccount);
    connect(checkoutButton, &QPushButton::clicked, this, &CustomerInterface::checkout);

    QWidget *menuWidget = new QWidget();
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

    stackWidget = new QStackedWidget();
    QLineEdit *searchLineEdit = new QLineEdit();
    searchLineEdit->setFixedHeight(50);
    searchLineEdit->setPlaceholderText("Search by product name...");
    connect(searchLineEdit, &QLineEdit::textChanged, this, &CustomerInterface::filterProducts);

    productTable = new QTableWidget(5, 6);
    productTable->setHorizontalHeaderLabels({"No.", "Description", "Product ID", "Product Name", "Price", "Quantity", "Add to Cart"});
    productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    productTable->setColumnWidth(0, 50);

    QGroupBox *productGroupBox = new QGroupBox();
    QVBoxLayout *productLayout = new QVBoxLayout(productGroupBox);
    productLayout->addWidget(searchLineEdit);
    productLayout->addSpacing(20);
    productLayout->addWidget(productTable);

    cartTable = new QTableWidget(0, 6);
    cartTable->setHorizontalHeaderLabels({"No.", "Product Name", "Product ID", "Price", "Quantity", "Action"});
    cartTable->setFixedSize(700, 650);

    invoiceDisplay = new QTextEdit("Invoice");
    invoiceDisplay->setVisible(false);
    paymentButton = new QPushButton("Payment");
    paymentButton->setVisible(false);
    paymentButton->setObjectName("confirmButton");
    connect(paymentButton, &QPushButton::clicked, this, &CustomerInterface::payment);
    totalPrice = new QLabel();
    totalPrice->setObjectName("inputArea");
    placeOrdersButton = new QPushButton("Place Oders");
    placeOrdersButton->setObjectName("confirmButton");
    connect(placeOrdersButton, &QPushButton::clicked, this, &CustomerInterface::showInvoice);
    QGroupBox *placeOrderBox = new QGroupBox();
    QHBoxLayout *placeOrdersLayout = new QHBoxLayout(placeOrderBox);
    placeOrdersLayout->addWidget(totalPrice);
    placeOrdersLayout->addWidget(placeOrdersButton);

    QGroupBox *cartAndPlaceOrdersBox = new QGroupBox();
    QVBoxLayout *cartAndPlaceOrderLayout = new QVBoxLayout(cartAndPlaceOrdersBox);
    cartAndPlaceOrderLayout->addWidget(cartTable);
    cartAndPlaceOrderLayout->addWidget(placeOrderBox);

    QGroupBox *invoiceGroupBox = new QGroupBox();
    QVBoxLayout *invoiceLayout = new QVBoxLayout(invoiceGroupBox);
    invoiceLayout->addWidget(invoiceDisplay);
    invoiceLayout->addWidget(paymentButton);

    QHBoxLayout *cartAndInvoiceLayout = new QHBoxLayout();
    QGroupBox *cartAndInvoiceBox = new QGroupBox();
    cartAndInvoiceBox->setLayout(cartAndInvoiceLayout);
    cartAndInvoiceLayout->addWidget(cartAndPlaceOrdersBox);
    cartAndInvoiceLayout->addWidget(invoiceGroupBox);

    stackWidget->addWidget(productGroupBox);
    stackWidget->addWidget(cartAndInvoiceBox);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(menuWidget);
    layout->addWidget(stackWidget);
    mainLayout->addLayout(layout);
    setLayout(mainLayout);
    cartOrigin();
    showProducts();

}

void CustomerInterface::addProductsData() {
    productTable->clearContents();
    productTable->setRowCount(0);

    DataController productData;
    productData.setProductFileName("D:/PBL/Data/ProductInformation.csv");
    Vector<Product> products = productData.loadProductData(); 

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

        QPushButton *addProductsButton = new QPushButton("Add");
        addProductsButton->setObjectName("confirmButton");
        connect(addProductsButton, &QPushButton::clicked, [this, row]() { addProducts(row, false); });

        QHBoxLayout *actionLayout = new QHBoxLayout();
        actionLayout->addWidget(addProductsButton);

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
        productId = QString::fromStdString(cart.getItems()[row].getFirst().getProductId());
    } else {
        if (productTable->item(row, 3) == nullptr) return;
        tenSanPham = productTable->item(row, 3)->text();
        giaSanPham = productTable->item(row, 4)->text();
        productId = productTable->item(row, 2)->text();
    }

    Product product(productId.toStdString(), tenSanPham.toStdString(), "", giaSanPham.toDouble(), 0, "", Vector<string>(), "");
    cart.addItem(product, 1); 

    if (fromCart) {
        showCart();
    }
}



void CustomerInterface::deleteProducts(int row, bool fromCart) {
    QString productId;

    if (fromCart) {
        if (cartTable->item(row, 0) == nullptr) return;
        productId = QString::fromStdString(cart.getItems()[row].getFirst().getProductId());
    } else {
        if (productTable->item(row, 2) == nullptr) return;
        productId = productTable->item(row, 2)->text();
    }

    if (!productId.isEmpty() && cart.contains(productId.toStdString())) {
        cart.reduceItem(productId.toStdString(), 1);
        if (cart.getItemQuantity(productId.toStdString()) == 0) {
            cart.removeItem(productId.toStdString());
        }
    }

    if (fromCart) {
        showCart();
    }
}

void CustomerInterface::cartOrigin(){
    DataController cartData;
    Cart cartOrigin = cartData.loadCartData(customerID); 

    for (long i = 0; i < cartOrigin.getItems().getSize(); ++i) {
        const Product& product = cartOrigin.getItems()[i].getFirst();
        int quantity = cartOrigin.getItems()[i].getSecond();
        cart.addItem(product, quantity);
    }
}

void CustomerInterface::showCart() {
    
    cartTable->clear();
    cartTable->setColumnCount(6);
    cartTable->setHorizontalHeaderLabels({"No.", "Product Name", "Product ID", "Price", "Quantity", "Action"});
    Vector<Pair<Product, int>> items = cart.getItems(); 
    cartTable->setRowCount(items.getSize());
    for (int i = 0; i < items.getSize(); ++i) {
        cartTable->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        cartTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(items[i].getFirst().getName())));
        cartTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(items[i].getFirst().getProductId())));
        cartTable->setItem(i, 3, new QTableWidgetItem(QString::number(items[i].getFirst().getPrice())));
        cartTable->setItem(i, 4, new QTableWidgetItem(QString::number(items[i].getSecond())));

        QPushButton *addButton = new QPushButton("+");
        addButton->setObjectName("confirmButton");
        connect(addButton, &QPushButton::clicked, [this, i]() { addProducts(i, true); });

        QPushButton *deleteButton = new QPushButton("-");
        deleteButton->setObjectName("cancelButton");
        connect(deleteButton, &QPushButton::clicked, [this, i]() { deleteProducts(i, true); });

        QWidget *actionWidget = new QWidget();
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
    cartTable->setColumnWidth(1, 220);
    double totalprice = 0.0;
    const Vector<Pair<Product, int>>& cartItems = cart.getItems(); 

    for (long i = 0; i < cartItems.getSize(); ++i) {
        const Product& product = cartItems[i].getFirst();
        int soLuong = cartItems[i].getSecond(); 
        double gia = product.getPrice();
        totalprice += gia * soLuong; 
    }

    totalPrice->setText("Total Price : " + QString::number(totalprice) + " $");
    totalPrice->setStyleSheet("font-weight: bold; font-size: 16pt;");
    totalPrice->setFixedHeight(40);
    stackWidget->setCurrentIndex(1);
    DataController cartData;
    cartData.saveCartData(cart); 
}






void CustomerInterface::showOverview() {
    {}
}

void CustomerInterface::filterProducts() {
    {}
}


void CustomerInterface::showAccount() {
}

void CustomerInterface::checkout() {
}

void CustomerInterface::showInvoice(){
    invoiceDisplay->setVisible(true);
    paymentButton->setVisible(true);
    placeOrdersButton->setVisible(false);
}

void CustomerInterface::showOrders(){
}

void CustomerInterface::payment(){

}

