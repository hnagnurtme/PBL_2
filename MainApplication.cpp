#include <QApplication>
#include "View/LoginSignupInterface.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LoginSignupInterface window;
    window.show();
    return app.exec();
}

