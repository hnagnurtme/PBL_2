#pragma once
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
    QComboBox *gender;
    QPushButton *confirmButton;
    QPushButton *exitButton;

public :
    RegisterForm(QWidget *parent = nullptr);
// signals:
//     void closed();

// private slots:
//     void onConfirmRegisterClicked();
//     void onExitClicked();
};
