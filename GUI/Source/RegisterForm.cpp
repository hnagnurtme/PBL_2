#include "GUI/Header/RegisterForm.h"
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
RegisterForm::RegisterForm(QWidget *parent) : QWidget(parent) {
    QFile file("Resource/style.qss");
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
    genderEdit = new QLineEdit(this);
    confirmButton = new QPushButton("Comfirm", this);
    gotoHomePageButton  = new QPushButton("Go to Homepage",this);
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
    infomation->addWidget(genderEdit,1,4);

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
    genderEdit->setFixedSize(380,40);


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
    genderEdit->setObjectName("inputArea");
    confirmButton->setObjectName("confirmButton");
    exitButton->setObjectName("cancelButton");
    gotoHomePageButton->setObjectName("confirmButton");

    QGroupBox *name = new QGroupBox;
    QGroupBox *infor = new QGroupBox;
    name->setLayout(fullname);
    infor->setLayout(infomation);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(exitButton);
    buttonLayout->addSpacing(100);
    buttonLayout->addWidget(gotoHomePageButton);
    buttonLayout->addSpacing(100);
    buttonLayout->addWidget(confirmButton);
    buttonLayout->setContentsMargins(30, 10, 30, 10);
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

    connect(confirmButton, &QPushButton::clicked, this, &RegisterForm :: onConfirmRegisterClicked );
    connect(exitButton,&QPushButton::clicked, this, &RegisterForm :: onExitClicked);
    connect(gotoHomePageButton,&QPushButton::clicked,this,&RegisterForm::ongotoHomepageClicked);
}

void RegisterForm :: onConfirmRegisterClicked(){
    QString firstname = firstnameEdit->text();
    QString lastname = lastnameEdit->text();
    QString birthday = birthdayEdit->text();
    QString phone = phonenumberEdit->text();
    QString address = addressEdit->text();
    QString gender = genderEdit->text();
    if(firstname.isEmpty() || lastname.isEmpty() ||birthday.isEmpty() || phone.isEmpty() || address.isEmpty() || gender.isEmpty() ) {
        QMessageBox::warning(this, "Input Error", "Please enter all of blanks.");
        return;
    }

    if (control) {
    control->SaveUserInformation(firstname.toStdString(), lastname.toStdString(),
                    address.toStdString(), phone.toStdString(),
                    birthday.toStdString(), gender.toStdString());
    } else {
    QMessageBox::critical(this, "Error", "Controller not initialized.");
    }
    QMessageBox::information(this,"Success","Create user successfull");
        this->hide();

        RegisterForm *mainWindow = new RegisterForm();
        mainWindow->resize(1000, 600);
        mainWindow->show();
}


void RegisterForm :: onExitClicked(){
    QMessageBox::warning(this, "Not Save", "Your account had not created yet");
    this->hide();
}


void RegisterForm :: ongotoHomepageClicked(){
    QMessageBox::information(this,"Success","Create user successfull");
    this->hide();
}