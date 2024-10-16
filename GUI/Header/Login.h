#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton> 

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();  
    void onForgotPasswordButtonClicked();  

private:
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QPushButton *confirmButton;
    QPushButton *registerButton;  
    QPushButton *forgotPasswordButton;  
};

#endif 
