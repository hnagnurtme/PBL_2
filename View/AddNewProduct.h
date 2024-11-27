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
    explicit AddProductWidget(QWidget *parent = nullptr);
    void showMessage(QWidget *parent, bool status, const QString &message);
    bool getStatus();
private slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    bool check ;
    QLineEdit *nameEdit;
    QLineEdit *categoryEdit;
    QDoubleSpinBox *priceSpin;
    QSpinBox *stockSpin;
    QLineEdit *descriptionEdit;
    QLineEdit *detailEdit;
    QLineEdit *brandEdit;
};
