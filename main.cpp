#include <QApplication>
#include "keyboardform.h"
#include <QDebug>

int main(int argc,char* argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication app(argc,argv);


    KeyboardForm keyboard;

    keyboard.setFixedSize(1000,230);
    keyboard.show();
    return app.exec();
}
