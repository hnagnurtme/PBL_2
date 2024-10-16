TEMPLATE = app
TARGET = MyQtApp
CONFIG += c++11

# Thêm các thư mục con vào project
SOURCES += MainApplication.cpp \
           GUI/Source/RegisterForm.cpp \
           GUI/Source/Login.cpp \
           Controller/RegisterFormController.cpp \ 
           Object/User.cpp \
           Handle/UserInformationHandle.cpp 
HEADERS += GUI/Header/RegisterForm.h  \
           GUI/Header/Login.h \
           Controller/RegisterFormController.h \
           Object/User.h \
           Handle/UserInformationHandle.h \
           Datastructures/Datastructures.h
# Thêm thư viện cần thiết
QT += widgets

# Khai báo tài nguyên
RESOURCES += Resource/resources.qrc
