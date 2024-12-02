#include "View/AddNewProduct.h"
#include "Model/Manager.h"
#include <QMessageBox>
#include <QFile>

void AddProductWidget::showMessage(QWidget *parent, bool status, const QString &message) {
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
AddProductWidget::AddProductWidget(QWidget *parent,Product *newproduct) : QWidget(parent) {
    if (newproduct != nullptr) 
    product = new Product(*newproduct);
    else product = new Product();
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        setStyleSheet(style);
    }
    setWindowTitle("Add New Product");
    setFixedWidth(800);

    QFormLayout *formLayout = new QFormLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    nameEdit = new QLineEdit;
    categoryEdit = new QLineEdit;
    priceSpin = new QDoubleSpinBox;
    stockSpin = new QSpinBox;
    descriptionEdit = new QLineEdit;
    detailEdit = new QLineEdit;
    brandEdit = new QLineEdit;

    priceSpin->setRange(0.0, 1000000.0);
    priceSpin->setDecimals(2);
    stockSpin->setRange(0, 1000000);

    if (newproduct) {
    nameEdit->setText(QString::fromStdString(newproduct->getName()));
    categoryEdit->setText(QString::fromStdString(newproduct->getCategory()));
    priceSpin->setValue(newproduct->getPrice());
    stockSpin->setValue(newproduct->getStock());
    descriptionEdit->setText(QString::fromStdString(newproduct->getDescription()));
    QStringList detailsList;
    Vector<string> details = newproduct->getDetail();
    for (int i = 0; i < details.getSize(); i++) {
        detailsList.append(QString::fromStdString(details[i]));
    }
    detailEdit->setText(detailsList.join(','));

    brandEdit->setText(QString::fromStdString(newproduct->getBrand()));
}

    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("Category:", categoryEdit);
    formLayout->addRow("Price:", priceSpin);
    formLayout->addRow("Stock:", stockSpin);
    formLayout->addRow("Description:", descriptionEdit);
    formLayout->addRow("Detail (comma-separated):", detailEdit);
    formLayout->addRow("Brand:", brandEdit);

    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &AddProductWidget::onOkButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddProductWidget::onCancelButtonClicked);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void AddProductWidget::onOkButtonClicked() {
    Product newProduct;
    AppController appController;
    Manager manager;
    if (product != nullptr && !product->getProductId().empty()) {
    newProduct.setProductId(product->getProductId());
    } else {
    newProduct.setProductId(appController.createProductId());
    }
    newProduct.setName(nameEdit->text().toStdString());
    newProduct.setCategory(categoryEdit->text().toStdString());
    newProduct.setPrice(priceSpin->value());
    newProduct.setStock(stockSpin->value());
    newProduct.setDescription(descriptionEdit->text().toStdString());

    QStringList detailsList = detailEdit->text().split(',');
    Vector<string> detailVector;
    for (const QString &detailStr : detailsList) {
        detailVector.pushback(detailStr.trimmed().toStdString());
    }
    newProduct.setDetail(detailVector);
    newProduct.setBrand(brandEdit->text().toStdString());

    manager.addNewProduct(newProduct);
    emit productAdded(); 
    showMessage(this,true,"Add New Product Sucessfull");
    this->close();
}

void AddProductWidget::onCancelButtonClicked() {
    showMessage(this,false,"Add New Product Failed ");
    this->close();
}