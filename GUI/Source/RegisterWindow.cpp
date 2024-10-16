#include "GUI/Header/RegisterWindow.h"
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

RegisterWindow::RegisterWindow(QWidget *parent) : QWidget(parent){
    control = new RegisterFormController();
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        this->setStyleSheet(style); 
    }
    setFixedSize(1100, 700);
    setWindowTitle("RegisterForm");

    QLabel *emailLabel = new QLabel("Email Address:");
    QLabel *passwordLabel = new QLabel("Password:");
    QLabel *confirmPasswordLabel = new QLabel("Confirm Password:");

    emailEdit = new QLineEdit();
    emailEdit->setPlaceholderText("Enter your email...");
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Enter your password...");
    confirmPasswordEdit = new QLineEdit();
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit->setPlaceholderText("Confirm your password...");
    alreadyHaveAccountButton =  new QPushButton("Already have an account? Log in");
    registerButton = new QPushButton("Register"); 

    QVBoxLayout *registerLayout = new QVBoxLayout;
    registerLayout->addWidget(emailLabel);
    registerLayout->addWidget(emailEdit);
    registerLayout->addWidget(passwordLabel);
    registerLayout->addWidget(passwordEdit);
    registerLayout->addWidget(confirmPasswordLabel);
    registerLayout->addWidget(confirmPasswordEdit);
    registerLayout->setContentsMargins(30, 10, 30, 10);

    emailLabel->setObjectName("inputTitle");
    emailEdit->setObjectName("inputArea");
    passwordLabel->setObjectName("inputTitle");
    passwordEdit->setObjectName("inputArea");
    confirmPasswordLabel->setObjectName("inputTitle");
    confirmPasswordEdit->setObjectName("inputArea");

    QGroupBox *registerBox = new QGroupBox();
    registerBox->setLayout(registerLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(alreadyHaveAccountButton);
    buttonLayout->addWidget(registerButton);
    buttonLayout->setContentsMargins(30, 10, 30, 10);

    alreadyHaveAccountButton->setObjectName("cancelButton");
    registerButton->setObjectName("confirmButton");

    QGroupBox *buttonBox = new QGroupBox();
    buttonBox->setLayout(buttonLayout);

    QVBoxLayout *intro = new QVBoxLayout;
    QLabel *imageLabel = new QLabel();
    QLabel *title = new QLabel("Welcome My Book Store");
    title->setObjectName("titleLabel");
    title->setAlignment(Qt::AlignCenter);
    QPixmap pixmap("Resource\\Background.png");
    if (pixmap.isNull()) {
        imageLabel->setText("Image not found");
    } else {
        imageLabel->setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    intro->addWidget(imageLabel);
    intro->addWidget(title);
    intro->setContentsMargins(30, 10, 30, 10);

    QGroupBox *introBox = new QGroupBox();
    introBox->setLayout(intro);
    introBox->setFixedHeight(230);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(introBox);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(registerBox);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    connect(alreadyHaveAccountButton, &QPushButton::clicked, this, &RegisterWindow::onAlreadyHaveAccountClicked);
    connect(registerButton, &QPushButton::clicked, this, &RegisterWindow::onRegisterButtonClicked);
    connect(this, &QWidget::destroyed, this, &RegisterWindow::closed);
}

void RegisterWindow::onRegisterButtonClicked() {
    QString email = emailEdit->text();
    QString password = passwordEdit->text();
    QString confirmPassword = confirmPasswordEdit->text();

    if (email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Password Error", "Passwords do not match.");
        return;
    }

    QMessageBox::information(this, "Registration Successful", "Your account has been created.");
    if (control) {
        control->SaveAccount(email.toStdString(), password.toStdString());
        RegisterForm *registerForm = new RegisterForm();
        registerForm->show();
        this->hide();
    }
    emit closed();
}
void RegisterWindow::onAlreadyHaveAccountClicked(){
    LoginWindow *loginWindow = new LoginWindow;
    loginWindow->show();
    this->close();
}