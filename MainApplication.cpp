#include <QApplication>
#include "GUI/Header/LoginWindow.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LoginWindow registerForm;
    registerForm.show();
    return app.exec();
}
