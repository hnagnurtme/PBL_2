#include <QApplication>
#include "GUI/Header/RegisterForm.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    RegisterForm registerForm;
    registerForm.show();
    return app.exec();
}
