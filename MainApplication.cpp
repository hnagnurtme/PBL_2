#include <QApplication>
#include "View/CustomerInterface.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CustomerInterface window;
    window.show();
    return app.exec();
}