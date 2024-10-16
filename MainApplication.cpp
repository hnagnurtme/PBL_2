#include <QApplication>
#include "GUI/Header/Login.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LoginWindow registerForm;
    registerForm.show();
    return app.exec();
}
