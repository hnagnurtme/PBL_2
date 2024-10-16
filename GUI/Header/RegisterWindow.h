#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
#include "Controller/RegisterFormController.h"
#include "GUI/Header/RegisterForm.h"
#include "GUI/Header/LoginWindow.h"
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

class RegisterWindow : public QWidget {
    Q_OBJECT

public:
    RegisterFormController *control;
    RegisterWindow(QWidget *parent = nullptr);
signals:
    void closed();
private slots:
    void onRegisterButtonClicked();
    void onAlreadyHaveAccountClicked();

private:
    QLineEdit *nameEdit;
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmPasswordEdit;
    QPushButton *alreadyHaveAccountButton;
    QPushButton *registerButton;
};

#endif 
