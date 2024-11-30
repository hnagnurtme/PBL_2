#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QString>
#include <QStringList>
#include "Model/Product.h"
#include "Controller/DataController.h"
#include "Controller/AppController.h"

class AddProductWidget : public QWidget {
    Q_OBJECT

public:
    explicit AddProductWidget(QWidget *parent = nullptr,Product *product = nullptr);
    void showMessage(QWidget *parent, bool status, const QString &message);
private slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();
signals:
    void productAdded();

private:
    Product *product;
    QLineEdit *nameEdit;
    QLineEdit *categoryEdit;
    QDoubleSpinBox *priceSpin;
    QSpinBox *stockSpin;
    QLineEdit *descriptionEdit;
    QLineEdit *detailEdit;
    QLineEdit *brandEdit;
};
