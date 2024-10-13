#include "GUI/Header/RegisterForm.h"
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

RegisterForm::RegisterForm(QWidget *parent) : QWidget(parent) {
    QFile file("Resource/style.css");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        this->setStyleSheet(style); 
    }
    setFixedSize(1100, 700);
    setWindowTitle("RegisterForm");
    QLabel *firstnameLabel = new QLabel("First Name", this);
    QLabel *lastnameLabel = new QLabel("Last Name", this);
    QLabel *phonenumberLabel = new QLabel("Phone");
    QLabel *addressLabel = new QLabel("Adress");
    QLabel *birthdayLabel = new QLabel("Birthday");
    QLabel *genderLabel = new QLabel("Gender");
    
    firstnameEdit = new QLineEdit(this);
    firstnameEdit->setPlaceholderText("Enter your firstname...");
    lastnameEdit = new QLineEdit(this);
    lastnameEdit->setPlaceholderText("Enter your lastname...");
    phonenumberEdit = new QLineEdit(this);
    phonenumberEdit->setPlaceholderText("Enter your phone numbers...");
    addressEdit = new QLineEdit(this);
    addressEdit->setPlaceholderText("Enter your address...");
    birthdayEdit = new QDateEdit(this);
    birthdayEdit->setCalendarPopup(true); 
    gender = new QComboBox(this);
    gender->addItem("Male");
    gender->addItem("Female");
    gender->addItem("Other");
    confirmButton = new QPushButton("Comfirm", this);
    exitButton = new QPushButton("Exit", this);
    
    QGridLayout *fullname = new QGridLayout;
    fullname->addWidget(firstnameLabel,0,0);
    fullname->addWidget(firstnameEdit,0,1);
    fullname->addItem(new QSpacerItem(30, 40, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 2); 
    fullname->addWidget(lastnameLabel,0,3);
    fullname->addWidget(lastnameEdit,0,4);

    QGridLayout *infomation = new QGridLayout;
    infomation->addWidget(phonenumberLabel,0,0);
    infomation->addWidget(phonenumberEdit,0,1);
    infomation->addItem(new QSpacerItem(30, 40, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 2); 
    infomation->addWidget(addressLabel,0,3);
    infomation->addWidget(addressEdit,0,4);
    infomation->addWidget(birthdayLabel,1,0);
    infomation->addWidget(birthdayEdit,1,1);
    infomation->addItem(new QSpacerItem(30, 40, QSizePolicy::Expanding, QSizePolicy::Minimum), 1, 2); 
    infomation->addWidget(genderLabel,1,3);
    infomation->addWidget(gender,1,4);

    firstnameLabel->setFixedSize(120,40);
    lastnameLabel->setFixedSize(120,40);
    firstnameEdit->setFixedSize(380,40);
    lastnameEdit->setFixedSize(380,40);
    phonenumberLabel->setFixedSize(120,40);
    phonenumberEdit->setFixedSize(380,40);
    addressLabel->setFixedSize(120,40);
    addressEdit->setFixedSize(380,40);
    birthdayLabel->setFixedSize(120,40);
    birthdayEdit->setFixedSize(380,40);
    genderLabel->setFixedSize(120,40);
    gender->setFixedSize(380,40);


    firstnameLabel->setObjectName("inputTitle");
    lastnameLabel->setObjectName("inputTitle");
    firstnameEdit->setObjectName("inputArea");
    lastnameEdit->setObjectName("inputArea");
    phonenumberLabel->setObjectName("inputTitle");
    addressLabel->setObjectName("inputTitle");
    birthdayLabel->setObjectName("inputTitle");
    genderLabel->setObjectName("inputTitle");
    phonenumberEdit->setObjectName("inputArea");
    addressEdit->setObjectName("inputArea");
    birthdayEdit->setObjectName("inputArea");
    gender->setObjectName("inputArea");
    confirmButton->setObjectName("confirmButton");
    exitButton->setObjectName("cancelButton");

    QGroupBox *name = new QGroupBox;
    QGroupBox *infor = new QGroupBox;
    name->setLayout(fullname);
    infor->setLayout(infomation);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addSpacing(100);
    buttonLayout->addWidget(exitButton);
    buttonLayout->setContentsMargins(30, 20, 30, 20);
    QGroupBox *button = new QGroupBox;
    button->setLayout(buttonLayout);

    QHBoxLayout *intro = new QHBoxLayout;
    QLabel *imageLabel = new QLabel();
    QPixmap pixmap("Resource\\Background.png");
    if (pixmap.isNull()) {
        imageLabel->setText("Image not found");
    } else {
        imageLabel->setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    intro->addWidget(imageLabel);

    QGroupBox *introBox = new QGroupBox();
    introBox->setLayout(intro);
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(introBox);
    mainLayout->addSpacing(10); 
    mainLayout->addWidget(name);
    mainLayout->addSpacing(10); 
    mainLayout->addWidget(infor);
    mainLayout->addSpacing(10);  
    mainLayout->addWidget(button);
    setLayout(mainLayout);
}
