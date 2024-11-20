#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QGroupBox>

class LoginSignupInterface : public QWidget {
    Q_OBJECT

public:
    explicit LoginSignupInterface(QWidget *parent = nullptr);
    void showMessage(QWidget *parent, bool status, const QString &message) ;
    ~LoginSignupInterface();

private slots:
    void showSignupPage();
    void showLoginPage();
    void login();
    void signup();

private:
    QLineEdit *emailInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QLabel *forgotPasswordLabel;
    QLabel *loginImage;

    QLineEdit *nameInput;
    QLineEdit *signupEmailInput;
    QLineEdit *phoneInput;
    QLineEdit *signupPasswordInput;
    QLineEdit *confirmSignupPasswordInput;
    QLineEdit *addressInput;
    QPushButton *signupButton;
    QLabel *signupImage;

    QStackedWidget *stackedWidget;

    QPushButton *switchToSignupButton;
    QPushButton *switchToLoginButton;
};
