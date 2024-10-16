#ifndef CHANGEPASSWORDWINDOW_H
#define CHANGEPASSWORDWINDOW_H
#include "Controller/LoginController.h"
#include "GUI/Header/RegisterWindow.h"
#include "GUI/Header/LoginWindow.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <string>
using namespace std;
class ChangePasswordWindow : public QWidget {
    Q_OBJECT
public:
    LoginController *control;
    ChangePasswordWindow(QWidget *parent = nullptr, const string &otp ="" );
signals:
    void closed();
private slots:
    void sendButtonClicked();
    void exitButtonClicked();

private:
    QLineEdit *passwordRecover;          
    QLineEdit *passwordRecoverConfirm;    
    QPushButton *sendButton;  
    QPushButton *exitButton;             
    const string otpEnter;                  
};

#endif