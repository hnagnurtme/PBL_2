#include "GUI/Header/HomePageAdmin.h"
#include "GUI/Header/LoginWindow.h"
#include "Controller/RegisterFormController.h"
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
#include <QAnimationDriver> 


LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    control = new LoginController();
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        this->setStyleSheet(style); 
    }

    setFixedSize(600,400);
    setWindowTitle("Login");

    QLabel *emailLabel = new QLabel("Email Address:");
    QLabel *passwordLabel = new QLabel("Password:");

    emailEdit = new QLineEdit();
    emailEdit->setPlaceholderText("Enter your email...");
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Enter your password...");
    confirmButton = new QPushButton("Log in");
    registerButton = new QPushButton("Register");
    forgotPasswordButton = new QPushButton("Forgot Password?");

    QVBoxLayout *loginLayout = new QVBoxLayout;
    loginLayout->addWidget(emailLabel);
    loginLayout->addWidget(emailEdit);
    loginLayout->addWidget(passwordLabel);
    loginLayout->addWidget(passwordEdit);
    loginLayout->setContentsMargins(30, 10, 30, 10);

    emailLabel->setObjectName("inputTitle");
    emailEdit->setObjectName("inputArea");
    passwordLabel->setObjectName("inputTitle");
    passwordEdit->setObjectName("inputArea");
    confirmButton->setObjectName("confirmButton");
    registerButton->setObjectName("confirmButton");
    forgotPasswordButton->setObjectName("cancelButton");

    QGroupBox *loginBox = new QGroupBox();
    loginBox->setLayout(loginLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(forgotPasswordButton);
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(registerButton);
    buttonLayout->setContentsMargins(30, 10, 30, 10);

    QGroupBox *buttonBox = new QGroupBox();
    buttonBox->setLayout(buttonLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addSpacing(10);
    mainLayout->addWidget(loginBox);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(buttonBox);
    

    setLayout(mainLayout);

    connect(confirmButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterButtonClicked);
    connect(forgotPasswordButton, &QPushButton::clicked, this, &LoginWindow::onForgotPasswordButtonClicked);
    
}

void LoginWindow::onLoginButtonClicked() {
    QString email = emailEdit->text().trimmed();;
    QString password = passwordEdit->text().trimmed();;
    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both email and password.");
        return;
    }
    if (control) {
    if(control->authenLogin(email.toStdString(),password.toStdString())){
        QMessageBox::information(this, "Login Successful......", "Welcome!");
        HomePageAdmin *homepageAdmin = new HomePageAdmin();
        homepageAdmin->show();
        this->close();
    }
    else{
        QMessageBox::warning(this, "Incorrect Password", "Please check both email and password.");
        return;
    }

    } else {
    QMessageBox::critical(this, "Error", "Controller not initialized.");
    }
    this->hide();
}

void LoginWindow::onForgotPasswordButtonClicked() {
    ForgotPassWordWindow *forgotPasswordWindow = new ForgotPassWordWindow();
    forgotPasswordWindow->show();
    this->hide();
    
}

void LoginWindow::onRegisterButtonClicked() {
    RegisterWindow *registerWindow = new RegisterWindow();
    registerWindow->show();
    this->hide();
}
