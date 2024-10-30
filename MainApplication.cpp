#include <QApplication>
#include "View/GiaoDienKhachHang.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CustomerInterface window;
    window.show();
    return app.exec();
}