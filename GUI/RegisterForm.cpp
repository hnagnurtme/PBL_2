#include "GUI/RegisterForm.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>

RegisterForm::RegisterForm(QWidget *parent) : QWidget(parent) {
    setFixedSize(1100, 700);
    setWindowTitle("RegisterForm");

    // Tạo các nhãn và dòng nhập cho tên
    QLabel *firstnameLabel = new QLabel("First Name:", this);
    QLabel *lastnameLabel = new QLabel("Last Name:", this);
    firstnameEdit = new QLineEdit(this);
    firstnameEdit->setPlaceholderText("Enter your firstname...");
    lastnameEdit = new QLineEdit(this);
    lastnameEdit->setPlaceholderText("Enter your lastname...");

    // Tạo layout cho tên
    QHBoxLayout *firstnameLayout = new QHBoxLayout;
    firstnameLayout->addWidget(firstnameLabel);
    firstnameLayout->addWidget(firstnameEdit);  // Sửa lại đây để thêm dòng nhập

    QGroupBox *firstnameGroup = new QGroupBox("First Name", this);
    firstnameGroup->setLayout(firstnameLayout);
    firstnameGroup->setStyleSheet("background-color: #BDDDFD; border: 1px solid #AAAAAA; border-radius: 5px; padding: 10px;");

    // Tạo layout cho họ
    QHBoxLayout *lastnameLayout = new QHBoxLayout;
    lastnameLayout->addWidget(lastnameLabel);
    lastnameLayout->addWidget(lastnameEdit);  // Sửa lại đây để thêm dòng nhập

    QGroupBox *lastnameGroup = new QGroupBox("Last Name", this);
    lastnameGroup->setLayout(lastnameLayout);
    lastnameGroup->setStyleSheet("background-color: #BDDDFD; border: 1px solid #AAAAAA; border-radius: 5px; padding: 10px;");

    // Tạo layout chính
    QVBoxLayout *fullnameLayout = new QVBoxLayout;
    fullnameLayout->addWidget(firstnameGroup);
    fullnameLayout->addWidget(lastnameGroup);

    QGroupBox *fullnameGroup = new QGroupBox("Full Name", this);
    fullnameGroup->setLayout(fullnameLayout);

    // Tạo layout chính cho cửa sổ
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fullnameGroup);

    setLayout(mainLayout);
}
