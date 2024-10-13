#include <QApplication>
#include "GUI/RegisterForm.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    RegisterForm registerform;
    registerform.show();
    return app.exec();
}
