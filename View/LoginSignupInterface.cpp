#include "View/LoginSignupInterface.h"
#include "View/CustomerInterface.h"
#include "Model/Customer.h"
#include "Model/User.h"
#include "Controller/DataController.h"
#include "Controller/AppController.h"
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>

LoginSignupInterface::LoginSignupInterface(QWidget *parent)
    : QWidget(parent)
{
    QFile file("Resource/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        setStyleSheet(style);
    }

    setFixedSize(1000, 600);
    setWindowTitle("Login Signup Window");

    QLabel *loginTitle = new QLabel("LOGIN HERE");
    loginTitle->setAlignment(Qt::AlignCenter);

    emailInput = new QLineEdit();
    emailInput->setPlaceholderText("Email");

    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);

    forgotPasswordLabel = new QLabel("<a href='#'>Forgot password?</a>");
    forgotPasswordLabel->setTextFormat(Qt::RichText);
    forgotPasswordLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    forgotPasswordLabel->setOpenExternalLinks(true);

    loginButton = new QPushButton("LOGIN");
    connect(loginButton, &QPushButton::clicked, this, &LoginSignupInterface::login);

    switchToSignupButton = new QPushButton("Switch to Signup");

    QVBoxLayout *loginLayout = new QVBoxLayout();
    loginLayout->addWidget(loginTitle);
    loginLayout->addWidget(emailInput);
    loginLayout->addWidget(passwordInput);

    QHBoxLayout *loginOptionsLayout = new QHBoxLayout();
    loginOptionsLayout->addWidget(forgotPasswordLabel);
    loginLayout->addLayout(loginOptionsLayout);
    loginLayout->addWidget(loginButton);
    loginLayout->addWidget(switchToSignupButton);

    loginImage = new QLabel();
    QPixmap loginPixmap("Resource/ICON/BACKGROUND3.png");
    if (!loginPixmap.isNull()) {
        loginImage->setPixmap(loginPixmap.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        qDebug() << "Failed to load login background image.";
    }

    QHBoxLayout *loginGroupLayout = new QHBoxLayout();
    loginGroupLayout->addLayout(loginLayout);
    loginGroupLayout->addWidget(loginImage);
    QGroupBox *loginGroup = new QGroupBox();
    loginGroup->setLayout(loginGroupLayout);

    QLabel *signupTitle = new QLabel("SIGN UP HERE");
    signupTitle->setAlignment(Qt::AlignCenter);

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Name");

    signupEmailInput = new QLineEdit();
    signupEmailInput->setPlaceholderText("Email");

    phoneInput = new QLineEdit();
    phoneInput->setPlaceholderText("Phone");

    signupPasswordInput = new QLineEdit();
    signupPasswordInput->setPlaceholderText("Password");
    signupPasswordInput->setEchoMode(QLineEdit::Password);

    confirmSignupPasswordInput = new QLineEdit();
    confirmSignupPasswordInput->setPlaceholderText("Confirm your password");
    confirmSignupPasswordInput->setEchoMode(QLineEdit::Password);

    addressInput = new QLineEdit();
    addressInput->setPlaceholderText("Address");

    signupButton = new QPushButton("SIGN UP");
    connect(signupButton, &QPushButton::clicked, this, &LoginSignupInterface::signup);

    switchToLoginButton = new QPushButton("Switch to Login");

    QVBoxLayout *signupLayout = new QVBoxLayout();
    signupLayout->addWidget(signupTitle);

    QHBoxLayout *userIdNameLayout = new QHBoxLayout();
    userIdNameLayout->addWidget(nameInput);
    signupLayout->addLayout(userIdNameLayout);

    signupLayout->addWidget(signupEmailInput);
    signupLayout->addWidget(phoneInput);
    signupLayout->addWidget(signupPasswordInput);
    signupLayout->addWidget(confirmSignupPasswordInput);
    signupLayout->addWidget(addressInput);
    signupLayout->addWidget(signupButton);
    signupLayout->addWidget(switchToLoginButton);

    signupImage = new QLabel();
    QPixmap signupPixmap("Resource/ICON//BACKGROUND3.png");
    if (!signupPixmap.isNull()) {
        signupImage->setPixmap(signupPixmap.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        qDebug() << "Failed to load signup background image.";
    }

    QHBoxLayout *signupGroupLayout = new QHBoxLayout();
    signupGroupLayout->addWidget(signupImage);  
    signupGroupLayout->addLayout(signupLayout);    
    QGroupBox *signupGroup = new QGroupBox();
    signupGroup->setLayout(signupGroupLayout);

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

LoginSignupInterface::~LoginSignupInterface() {}

void LoginSignupInterface::showSignupPage() {
    stackedWidget->setCurrentIndex(1); 
}

void LoginSignupInterface::showLoginPage() {
    stackedWidget->setCurrentIndex(0); 
}

void LoginSignupInterface::login() {
    QString email = emailInput->text().trimmed();  // Loại bỏ khoảng trắng ở đầu và cuối email
    QString password = passwordInput->text().trimmed();  // Loại bỏ khoảng trắng ở đầu và cuối password
    
    AppController *appCon = new AppController();
    Pair<string, string> result = appCon->allLogin(email.toStdString(), password.toStdString());  // Gọi một lần và lưu kết quả trả về
    
    string role = result.getFirst();
    string userId = result.getSecond();
    
    if (role == "Customer") {
        CustomerInterface *view = new CustomerInterface(nullptr, userId);
        view->show();
        this->hide();
    }
    else if (role == "Manager") {
        // Tạo cửa sổ cho Manager nếu cần
    }
    else if (role == "Employee") {
        // Tạo cửa sổ cho Employee nếu cần
    }
    else {
        // Xử lý trường hợp đăng nhập không thành công (role == "Invalid")
        QMessageBox::warning(this, "Login Failed", "Invalid email or password.");
    }
    delete appCon;
}


void LoginSignupInterface::signup() {
    QString name = nameInput->text();
    QString email = signupEmailInput->text();
    QString phone = phoneInput->text();
    QString password = signupPasswordInput->text();
    QString confirmPassword = confirmSignupPasswordInput->text();
    QString address = addressInput->text();
    
    AppController *appCon = new AppController();
    DataController *data = new DataController();  
    if( password == confirmPassword){
        string role = "Customer";
        string id = appCon->signin(name.QString::toStdString(),email.QString::toStdString(),phone.QString::toStdString(),password.QString::toStdString(),address.QString::toStdString(),role);
        CustomerInterface *view = new CustomerInterface(nullptr, id);
        view->show();
    } 
    
    delete data;
    delete appCon;
}

