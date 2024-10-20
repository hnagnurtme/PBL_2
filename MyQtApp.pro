TEMPLATE = app
TARGET = MyQtApp
CONFIG += c++11

# Thêm các thư mục con vào project
SOURCES += MainApplication.cpp \
           GUI/Source/RegisterForm.cpp \
           GUI/Source/LoginWindow.cpp \
           GUI/Source/RegisterWindow.cpp \
           Controller/RegisterFormController.cpp \
           Object/User.cpp \
           Handle/UserInformationHandle.cpp \
           Handle/LoginHandle.cpp \
           Controller/LoginController.cpp \
           GUI/Source/ForgotPasswordWindow.cpp \
           GUI/Source/ChangePassword.cpp

HEADERS += GUI/Header/RegisterForm.h  \
           GUI/Header/LoginWindow.h \
           GUI/Header/RegisterWindow.h \
           Controller/RegisterFormController.h \
           Object/User.h \
           Handle/UserInformationHandle.h \
           Handle/LoginHandle.h \
           Datastructures/Datastructures.h \
           Controller/LoginController.h \
           GUI/Header/ForgotPasswordWindow.h \
           GUI/Header/ChangePassword.h

# Thêm thư viện cần thiết
QT += widgets 

# Khai báo tài nguyên
RESOURCES += Resource/resources.qrc
