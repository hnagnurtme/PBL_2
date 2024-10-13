TEMPLATE = app
TARGET = MyQtApp
CONFIG += c++11

# Thêm các thư mục con vào project
SOURCES += MainApplication.cpp \
           GUI/Source/RegisterForm.cpp  # Sửa lại dấu \ thành dấu / cho đúng

HEADERS += GUI/Header/RegisterForm.h  # Sửa lại dấu \ thành dấu / cho đúng

# Thêm thư viện cần thiết
QT += widgets

# Khai báo tài nguyên
RESOURCES += Resource/resources.qrc
