#include "GUI/Header/LoginWindow.h"
#include "Controller/RegisterFormController.h"
#include "GUI/Header/ForgotPasswordWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

ForgotPassWordWindow::ForgotPassWordWindow(QWidget *parent): QWidget(parent) {
    control = new LoginController();
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        this->setStyleSheet(style); 
    }
    setFixedWidth(700);
    setWindowTitle("Login");

    QLabel *emailLabel = new QLabel("Email Recovery", this);
    QLabel *otpLabel = new QLabel("Enter your OTP:", this);

    emailLineEdit = new QLineEdit();
    emailLineEdit->setPlaceholderText("Enter your email...");
    otpLineEdit = new QLineEdit();
    otpLineEdit->setPlaceholderText("OTP");
    sendButton = new QPushButton("Send Request", this);
    confirmButton = new QPushButton("Confirm OTP", this);
    backtologinButton = new QPushButton("Back to Login", this);


    QHBoxLayout *recoverLayout = new QHBoxLayout;
    recoverLayout->addWidget(emailLabel);
    recoverLayout->addWidget(emailLineEdit);
    recoverLayout->addWidget(sendButton);
    recoverLayout->setContentsMargins(30, 10, 30, 10);
    
    QHBoxLayout *sendOTPLayout = new QHBoxLayout;
    sendOTPLayout->addWidget(otpLabel);
    sendOTPLayout->addWidget(otpLineEdit);
    sendOTPLayout->addWidget(confirmButton);
    sendOTPLayout->setContentsMargins(30, 10, 30, 10);
    
    emailLabel->setObjectName("inputTitle");
    emailLineEdit->setObjectName("inputArea");
    otpLabel->setObjectName("inputTitle");
    otpLineEdit->setObjectName("inputArea");
    confirmButton->setObjectName("confirmButton");
    sendButton->setObjectName("confirmButton");
    backtologinButton->setObjectName("cancelButton");
    confirmButton->setVisible(false);
    otpLineEdit->setVisible(false);

    QGroupBox *recoverBox = new QGroupBox();
    recoverBox->setLayout(recoverLayout);

    QGroupBox *sendOTPBox = new QGroupBox();
    sendOTPBox->setLayout(sendOTPLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    
    buttonLayout->addWidget(backtologinButton);
    buttonLayout->setContentsMargins(30, 10, 30, 10);

    QGroupBox *buttonBox = new QGroupBox();
    buttonBox->setLayout(buttonLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(recoverBox);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(sendOTPBox);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    connect(sendButton, &QPushButton::clicked, this, &ForgotPassWordWindow::sendOTPRequest);
    connect(backtologinButton, &QPushButton::clicked, this, &ForgotPassWordWindow::backtoLogin);
    connect(confirmButton, &QPushButton::clicked, this, &ForgotPassWordWindow::confirmOTP);
}

void ForgotPassWordWindow:: sendOTPRequest(){
    QString email = emailLineEdit->text().trimmed();
    if (email.isEmpty() ) {
        QMessageBox::warning(this, "Input Error", "Please enter your email.");
        return;
    }
    if (control == nullptr) {
    QMessageBox::critical(this, "Error", "Control is not initialized.");
    return;
    }
    if(control->sendRequestRecover(email.toStdString())){
        QMessageBox::information(this, "Request Sent", 
        "Password recovery request sent to " + email );
        confirmButton->setVisible(true);
        otpLineEdit->setVisible(true);
        sendButton->setVisible(false);
    }
    else {
        QMessageBox::warning(this, "Invalid Email", "Please enter the correct email.");
        return;
    }    
}

void ForgotPassWordWindow::confirmOTP(){
    QString otpEntered = otpLineEdit->text().trimmed();
    if (otpEntered.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter the OTP.");
        return;
    }
    if(control->authenticationRequest(otpEntered.toStdString())){
        QMessageBox::information(this, "Success", "OTP is valid. You can now reset your password");
        ChangePasswordWindow *changpasswordWindow = new ChangePasswordWindow(this,otpEntered.toStdString());
        changpasswordWindow->setWindowFlag(Qt::Window);
        changpasswordWindow->show();
        this->hide();
    }
    else {
        QMessageBox::warning(this, "Invalid OTP", "The OTP you entered is invalid. Please try again.");
    }
}
void ForgotPassWordWindow::backtoLogin(){
    LoginWindow *loginWindow  = new LoginWindow();
    loginWindow->show();
    this->hide();
}
