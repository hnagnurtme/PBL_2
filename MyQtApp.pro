# MyQtApp.pro
TEMPLATE = app
TARGET = MyQtApp
CONFIG += c++11

# Thêm các thư mục con vào project
SOURCES += MainApplication.cpp \
           GUI/RegisterForm.cpp \
HEADERS += GUI/RegisterForm.h \
           
# Thêm thư viện cần thiết
QT += widgets
 