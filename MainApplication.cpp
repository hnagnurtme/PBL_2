#include <QApplication>
#include "GUI/Header/ForgotPasswordWindow.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ForgotPassWordWindow registerForm;
    registerForm.show();
    return app.exec();
}
