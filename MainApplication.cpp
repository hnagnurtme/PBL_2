#include <QApplication>
#include "GUI/Header/GiaoDienKhachHang.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GiaoDienKhachHang window;
    window.show();
    return app.exec();
}
