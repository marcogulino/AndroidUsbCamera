#include <QCoreApplication>
#include "AndroidUsbCamera.h"


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    AndroidUsbCamera *foo = new AndroidUsbCamera();
    app.connect(&app, SIGNAL(aboutToQuit()), foo, SLOT(close()));
    foo->stream();
    return app.exec();
}
