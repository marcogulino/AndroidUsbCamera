#include <QCoreApplication>
#include "androidusbcamera.h"


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    AndroidUsbCamera camera;
    return app.exec();
}
