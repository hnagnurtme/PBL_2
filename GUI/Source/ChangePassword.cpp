#include "GUI/Header/ChangePassword.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <string>
using namespace std;
ChangePasswordWindow::ChangePasswordWindow(QWidget *parent, const string &otp): QWidget(parent), otpEnter(otp) {
    control = new LoginController();
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        this->setStyleSheet(style); 
    }
    setWindowTitle("Change Password");
    setFixedWidth(700); 


    QLabel *passwordLabel = new QLabel("New Password:", this);
    passwordRecover = new QLineEdit(this);
    passwordRecover->setEchoMode(QLineEdit::Password);
    passwordRecover->setPlaceholderText("Enter new password...");
    QLabel *confirmLabel = new QLabel("Confirm Password:", this);
    passwordRecoverConfirm = new QLineEdit(this);
    passwordRecoverConfirm->setEchoMode(QLineEdit::Password);
    passwordRecoverConfirm->setPlaceholderText("Confirm new password...");
    sendButton = new QPushButton("Send", this);
    exitButton = new QPushButton("Exit",this);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(passwordLabel);
    inputLayout->addWidget(passwordRecover);
    inputLayout->addWidget(confirmLabel);
    inputLayout->addWidget(passwordRecoverConfirm);
    inputLayout->setContentsMargins(30, 10, 30, 10);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(sendButton);
    buttonLayout->addWidget(exitButton);
    buttonLayout->setContentsMargins(30, 10, 30, 10);

    passwordLabel->setObjectName("inputTitle");
    passwordRecover->setObjectName("inputArea");
    confirmLabel->setObjectName("inputTitle");
    passwordRecoverConfirm->setObjectName("inputArea");
    sendButton->setObjectName("confirmButton");
    exitButton->setObjectName("cancelButton");

    QGroupBox *inputBox = new QGroupBox();
    inputBox->setLayout(inputLayout);
    QGroupBox *buttonBox = new QGroupBox();
    buttonBox->setLayout(buttonLayout);
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputBox);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(buttonBox);
    mainLayout->addSpacing(10);;
    setLayout(mainLayout);

    connect(sendButton, &QPushButton::clicked, this, &ChangePasswordWindow::sendButtonClicked);
    connect(exitButton,&QPushButton::clicked,this,&ChangePasswordWindow::exitButtonClicked);
}

void ChangePasswordWindow::sendButtonClicked() {
    QString password = passwordRecover->text().trimmed();
    QString confirmPassword = passwordRecoverConfirm->text().trimmed();
    if (password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in both password fields.");
        return;
    }
    if (password != confirmPassword) {
        QMessageBox::warning(this, "Password Mismatch", "Passwords do not match.");
        return;
    }
    if (control->recoverPassword(password.toStdString())) {
        QMessageBox::information(this, "Success", "Password has been changed successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to recover password.");
    }
    this->close();
}


void ChangePasswordWindow::exitButtonClicked(){
    LoginWindow *loginWindow = new LoginWindow();
    loginWindow->show();
    this->closed();
}
