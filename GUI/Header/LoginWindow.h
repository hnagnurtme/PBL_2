#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "Controller/LoginController.h"
#include "GUI/Header/RegisterWindow.h"
#include "GUI/Header/ForgotPasswordWindow.h"
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton> 

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginController *control;
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
