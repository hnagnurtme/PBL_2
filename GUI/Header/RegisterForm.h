#pragma once
#include "Controller/RegisterFormController.h"
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QDateEdit>
#include <QComboBox>
class RegisterForm : public QWidget{
    Q_OBJECT;
private:
    QLineEdit *firstnameEdit;
    QLineEdit *lastnameEdit;
    QLineEdit *phonenumberEdit;
    QDateEdit *birthdayEdit;
    QLineEdit *addressEdit;
    QLineEdit *genderEdit;
    QPushButton *confirmButton;
    QPushButton *exitButton;
    QPushButton *gotoHomePageButton;
public :
    RegisterFormController *control;
    RegisterForm(QWidget *parent = nullptr);
signals:
    void closed();

private slots:
    void onConfirmRegisterClicked();
    void onExitClicked();
    void ongotoHomepageClicked();
};
