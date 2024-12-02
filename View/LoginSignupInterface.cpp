#include "View/LoginSignupInterface.h"
#include "View/CustomerInterface.h"
#include "View/ManagerInterface.h"
#include "Model/Customer.h"
#include "Model/User.h"
#include "Controller/DataController.h"
#include "Controller/AppController.h"
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>

void LoginSignupInterface::showMessage(QWidget *parent, bool status, const QString &message) {
    QMessageBox messageBox(parent);
    QString icon_path = (status) ? "Resource/ICON/ICON12.png" : "Resource/ICON/ICON11.png";
    QPixmap originalPixmap(icon_path);
    QPixmap scaledPixmap = originalPixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    messageBox.setIconPixmap(scaledPixmap);
    messageBox.setText(message);
    messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    messageBox.setFixedSize(600, 400);
    messageBox.exec();
}

LoginSignupInterface::LoginSignupInterface(QWidget *parent): QWidget(parent) {
    dataController = new DataController();
    appController = new AppController();
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        setStyleSheet(style);
    }
    setFixedWidth(1000);
    setWindowTitle("Login Signup Window");

    QLabel *loginTitle = new QLabel(this);
    QPixmap pixmap(":/welcome");
    QPixmap scaledPixmap = pixmap.scaled(pixmap.size() * 1.5, Qt::KeepAspectRatio);
    loginTitle->setPixmap(scaledPixmap);
    loginTitle->setAlignment(Qt::AlignCenter);

    QLabel *emailLabel = new QLabel("Email:");
    emailInput = new QLineEdit();
    emailInput->setPlaceholderText("Enter your email");

    QLabel *passwordLabel = new QLabel("Password:");
    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Enter your password");
    passwordInput->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("LOGIN");
    connect(loginButton, &QPushButton::clicked, this, &LoginSignupInterface::login);

    switchToSignupButton = new QPushButton("Don't have an account yet? Create one now");
    switchToSignupButton->setObjectName("cancelButton");

    QHBoxLayout *loginButtonLayout = new QHBoxLayout();
    loginButtonLayout->addWidget(switchToSignupButton); 
    loginButtonLayout->addWidget(loginButton);

    QVBoxLayout *loginLayout = new QVBoxLayout();
    loginLayout->addWidget(loginTitle);
    loginLayout->addSpacing(10);
    loginLayout->addWidget(emailLabel);
    loginLayout->addWidget(emailInput);
    loginLayout->addSpacing(10);
    loginLayout->addWidget(passwordLabel);
    loginLayout->addWidget(passwordInput);
    loginLayout->addSpacing(10);
    loginLayout->addLayout(loginButtonLayout);

    QGroupBox *loginGroup = new QGroupBox();
    loginGroup->setLayout(loginLayout);

    QLabel *signupTitle = new QLabel("SIGN UP HERE");
    signupTitle->setAlignment(Qt::AlignCenter);
    signupTitle->setObjectName("inputTitle"); 

    QLabel *nameLabel = new QLabel("Name:");
    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter your name");

    QLabel *signupEmailLabel = new QLabel("Email:");
    signupEmailInput = new QLineEdit();
    signupEmailInput->setPlaceholderText("Enter your email");

    QLabel *phoneLabel = new QLabel("Phone:");
    phoneInput = new QLineEdit();
    phoneInput->setPlaceholderText("Enter your phone number");

    QLabel *signupPasswordLabel = new QLabel("Password:");
    signupPasswordInput = new QLineEdit();
    signupPasswordInput->setPlaceholderText("Enter your password");
    signupPasswordInput->setEchoMode(QLineEdit::Password);

    QLabel *confirmPasswordLabel = new QLabel("Confirm Password:");
    confirmSignupPasswordInput = new QLineEdit();
    confirmSignupPasswordInput->setPlaceholderText("Re-enter your password");
    confirmSignupPasswordInput->setEchoMode(QLineEdit::Password);

    QLabel *addressLabel = new QLabel("Address:");
    addressInput = new QLineEdit();
    addressInput->setPlaceholderText("Enter your address");

    signupButton = new QPushButton("SIGN UP");
    connect(signupButton, &QPushButton::clicked, this, &LoginSignupInterface::signup);

    switchToLoginButton = new QPushButton("You already have an account? Login here");
    switchToLoginButton->setObjectName("cancelButton");

    QHBoxLayout *signupButtonLayout = new QHBoxLayout();
    signupButtonLayout->addWidget(switchToLoginButton);
    signupButtonLayout->addWidget(signupButton);
    
    QVBoxLayout *signupLayout = new QVBoxLayout();
    signupLayout->addWidget(signupTitle);
    signupLayout->addSpacing(10);
    signupLayout->addWidget(nameLabel);
    signupLayout->addWidget(nameInput);
    signupLayout->addSpacing(10);
    signupLayout->addWidget(signupEmailLabel);
    signupLayout->addWidget(signupEmailInput);
    signupLayout->addSpacing(10);
    signupLayout->addWidget(phoneLabel);
    signupLayout->addWidget(phoneInput);
    signupLayout->addSpacing(10);
    signupLayout->addWidget(signupPasswordLabel);
    signupLayout->addWidget(signupPasswordInput);
    signupLayout->addSpacing(10);
    signupLayout->addWidget(confirmPasswordLabel);
    signupLayout->addWidget(confirmSignupPasswordInput);
    signupLayout->addSpacing(10);
    signupLayout->addWidget(addressLabel);
    signupLayout->addWidget(addressInput);
    signupLayout->addSpacing(20);
    signupLayout->addLayout(signupButtonLayout);

    QGroupBox *signupGroup = new QGroupBox();
    signupGroup->setLayout(signupLayout);

    stackedWidget = new QStackedWidget();
    stackedWidget->addWidget(loginGroup);
    stackedWidget->addWidget(signupGroup);

    stackedWidget->setCurrentWidget(loginGroup);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);

    connect(switchToSignupButton, &QPushButton::clicked, this, &LoginSignupInterface::showSignupPage);
    connect(switchToLoginButton, &QPushButton::clicked, this, &LoginSignupInterface::showLoginPage);
}

LoginSignupInterface::~LoginSignupInterface() {
    delete appController;
    delete dataController;
}

void LoginSignupInterface::showSignupPage() {
    stackedWidget->setCurrentIndex(1); 
}

void LoginSignupInterface::showLoginPage() {
    stackedWidget->setCurrentIndex(0); 
}

void LoginSignupInterface::login() {
    QString email = emailInput->text().trimmed(); 
    QString password = passwordInput->text().trimmed();  
    if (email.isEmpty() || password.isEmpty()) {
        showMessage(this, false, "Please enter both email and password.");
        return;
    }
    if (!email.contains("@") || !email.contains(".")) {
        showMessage(this, false, "Invalid email format.");
        return;
    }
    Pair<string, string> result = appController->allLogin(email.toStdString(), password.toStdString());  
    string role = result.getFirst();
    string userId = result.getSecond();
    if (role == "Customer") {
        showMessage(this, true, "Login successful. Welcome, Customer!");
        CustomerInterface *view = new CustomerInterface(nullptr, userId);
        view->show();
        this->close(); 
    }
    else if (role == "Manager") {
        showMessage(this, true, "Login successful. Welcome, Manager!");
        ManagerInterface *view = new ManagerInterface(nullptr, userId);
        view->show(); 
        this->close();
    }
}


void LoginSignupInterface::signup() {
    QString name = nameInput->text().trimmed();
    QString email = signupEmailInput->text().trimmed();
    QString phone = phoneInput->text().trimmed();
    QString password = signupPasswordInput->text().trimmed();
    QString confirmPassword = confirmSignupPasswordInput->text().trimmed();
    QString address = addressInput->text().trimmed();
    if (name.isEmpty() || email.isEmpty() || phone.isEmpty() || password.isEmpty() || confirmPassword.isEmpty() || address.isEmpty()) {
        showMessage(this, false, "All fields must be filled in.");
        return;
    }
    if (!email.contains("@") || !email.contains(".")) {
        showMessage(this, false, "Invalid email format.");
        return;
    }
    bool isPhoneValid = true;
    for (int i = 0; i < phone.length(); ++i) {
        if (!phone[i].isDigit()) {
            isPhoneValid = false;
            break;
        }
    }
    if (!isPhoneValid || phone.length() != 10) {
        showMessage(this, false, "Invalid phone number format.");
        return;
    }
    if (password != confirmPassword) {
        showMessage(this, false, "Passwords do not match. Please try again.");
        return;
    }
    
    string role = "Customer";
    string id = appController->signin(name.toStdString(), email.toStdString(), phone.toStdString(), password.toStdString(), address.toStdString(), role);
    showMessage(this, true, "Signup successful! You can now login.");
    CustomerInterface *view = new CustomerInterface(nullptr, id);
    view->show();
    this->close();
}