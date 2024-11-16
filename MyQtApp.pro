# MyQtApp.pro
TEMPLATE = app
TARGET = MyQtApp
CONFIG += c++11

# Thêm các thư mục con vào project
SOURCES += MainApplication.cpp \
           Controller/DataController.cpp \
           Controller/AppController.cpp \
           Model/Product.cpp \
           Model/Cart.cpp \
           Model/User.cpp \
           Model/Orders.cpp \
           Model/Invoice.cpp \
           Model/Customer.cpp \
           Model/Employee.cpp \
           Model/Manager.cpp \
           View/CustomerInterface.cpp \
           View/LoginSignupInterface.cpp
HEADERS +=  Controller/DataController.h \
            Controller/AppController.h \
            Datastructures/Pair.h \
            Datastructures/Vector.h \
            Model/Product.h \
            Model/Cart.h \
            Model/User.h \
            Model/Orders.h \
            Model/Invoice.h \
            Model/Customer.h \
            Model/Employee.h \
            Model/Manager.h \
            View/CustomerInterface.h \
            View/LoginSignupInterface.h
           
# Thêm thư viện cần thiết
QT += widgets
QT += charts

# Khai báo tài nguyên
RESOURCES += Resource/resources.qrc