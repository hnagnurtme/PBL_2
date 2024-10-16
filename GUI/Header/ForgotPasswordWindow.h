#ifndef FORGOTPASSWORDWINDOW_H
#define FORGOTPASSWORDWINDOW_H
#include "Controller/LoginController.h"
#include "GUI/Header/RegisterWindow.h"
#include "GUI/Header/LoginWindow.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class ForgotPassWordWindow : public QWidget {
    Q_OBJECT

public:
    LoginController *control;
    ForgotPassWordWindow(QWidget *parent = nullptr);

signals:
    void closed(); 

private slots:
    void sendOTPRequest();
    void confirmOTP(); 
    void backtoLogin(); 

private:
    QLineEdit *emailLineEdit; 
    QPushButton *sendButton; 
    QPushButton *confirmButton; 
    QPushButton *backtologinButton; 
    QLineEdit *otpLineEdit; 
};

#endif 