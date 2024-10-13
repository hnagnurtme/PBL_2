#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
class RegisterForm : public QWidget{
    Q_OBJECT;
private:
    QLineEdit *firstnameEdit;
    QLineEdit *lastnameEdit;
    QLineEdit *phonenumberEdit;
    QLineEdit *adressEdit;
    QLineEdit *birthdayEdit;
    QCheckBox *gender;
    QPushButton *confirmButton;
    QPushButton *exitButton;

public :
    RegisterForm(QWidget *parent = nullptr);
signals:
    void closed();

private slots:
    void onConfirmRegisterClicked();
    void onExitClicked();
};
